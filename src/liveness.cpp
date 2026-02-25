#include "liveness.hpp"
#include "interf_graph.hpp"
#include "tac_ir.hpp"
#include <vector>

void LivenessAnalyzer::pre_liveness(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        b->use.clear(); b->def.clear();
        b->live_in.clear(); b->live_out.clear();

        for (auto& ins : b->ins){
            RType rtype = dtype_to_rtype(ins.type);

            if (ins.op == Operation::LOCAL){ 
                b->live_in.insert({ins.src1, rtype});
                continue;
            }

            if (ins.dst.is_register()) b->def.insert({ins.dst, rtype});

            if (ins.src1.is_register()){ // defined
                if (!b->def.contains({ins.src1, rtype})) b->use.insert({ins.src1, rtype});
            }
            if (ins.src2.is_register()){ // defined
                if (!b->def.contains({ins.src2, rtype})) b->use.insert({ins.src2, rtype});
            }
        }
    }
}

// calculate liveness sets for variables for each function
void LivenessAnalyzer::live_func(FunctionIR& func){
    pre_liveness(func);

    bool done = false;
    while (!done){
        done = true;
        for (auto it = func.blocks.rbegin(); it != func.blocks.rend(); ++it){
            Block* b = it->get();
            
            virtual_varset temp_in = b->use;
            virtual_varset temp_out;

            for (Block* suc : b->out_edge)
                temp_out.insert(suc->live_in.begin(), suc->live_in.end());

            for (auto& v : temp_out){
                if (!b->def.count(v)) temp_in.insert(v);
            }
            if (temp_in != b->live_in || temp_out != b->live_out)
                done = false;

            b->live_in  = std::move(temp_in);
            b->live_out = std::move(temp_out);
        }
    }
}

void LivenessAnalyzer::add_interference_edges(Instruction& ins, virtual_varset& live, InterferenceGraph& graph) {
    virtual_varset defines, uses;
    RType rtype = dtype_to_rtype(ins.type);

    if (target == X86) X86_interference(ins, defines, graph);

    if (ins.dst.is_register()) defines.insert({ins.dst, rtype});
    if (ins.src1.is_register()){ 
        uses.insert({ins.src1, rtype});
        graph.incr_uses(ins.src1, rtype);
    }
    if (ins.src2.is_register()){ 
        uses.insert({ins.src2, rtype});
        graph.incr_uses(ins.src2, rtype);
    }

    if (ins.op == Operation::CALL){
        for (int clobber_gp : regInfo.GP_CALLER_SAVE){ 
            defines.insert({Operand::gpr(clobber_gp), GP});
            IGNode& node = graph.add_node(Operand::gpr(clobber_gp), GP);
            node.assigned = clobber_gp;
        }
        for (int clobber_fp : regInfo.FP_CALLER_SAVE){ 
            defines.insert({Operand::fpr(clobber_fp), FP});
            IGNode& node = graph.add_node(Operand::fpr(clobber_fp), FP);
            node.assigned = clobber_fp;
        }
    }
    for (virtual_var def : defines) {
        graph.add_node(def.first, def.second); // ensure node exists
        for (virtual_var var : live) {
            if (var.second == def.second) {
                graph.add_node(var.first, var.second);
                graph.add_edge(var.first, def.first);
            }
        }
        live.erase(def);
    }
    for (virtual_var u : uses) live.insert(u);
}

void LivenessAnalyzer::X86_interference(Instruction& ins, virtual_varset& defines, InterferenceGraph& graph){
    RType rtype = dtype_to_rtype(ins.type);
    if (rtype == GP){
        if (ins.op == Operation::DIV || ins.op == Operation::FLR){
            defines.insert({Operand::gpr(RDX), GP});
            IGNode& node = graph.add_node(Operand::gpr(RDX), GP);
            node.assigned = RDX;
        }
    }
    else { // FP (might do this in ir lower though, ensure R11 is free during a flr ins)
        if (ins.op == Operation::FLR){
            defines.insert({Operand::gpr(R11), GP});
            IGNode& node = graph.add_node(Operand::gpr(R11), GP);
            node.assigned = R11;
        }
    }
}

void LivenessAnalyzer::process_block(Block* b, InterferenceGraph& graph, movelist& moves) {
    virtual_varset live = b->live_out;

    for (auto it = b->ins.rbegin(); it != b->ins.rend(); it++) {
        Instruction& ins = *it;
        if (ins.op == Operation::LOCAL) continue;

        if (ins.is_move() && ins.src1.is_register())
            moves.push_back({ins.dst, ins.src1});

        add_interference_edges(ins, live, graph);
    }
}

void LivenessAnalyzer::gen_interference(FunctionIR& func, InterferenceGraph& graph) {
    movelist moves;

    live_func(func); // generates live sets for blocks
    for (auto& blk_ptr : func.blocks) {
        process_block(blk_ptr.get(), graph, moves);
    }
    move_coalesce(graph, moves); // coalesce move nodes
}

void LivenessAnalyzer::move_coalesce(InterferenceGraph& ig, movelist& mlist){
    bool fix = false; // lfp
    while (!fix) {
        fix = true;
        for (auto it = mlist.begin(); it != mlist.end(); ){
            auto& m = *it;
            int idx1 = ig.virtual_map[m.first];
            int idx2 = ig.virtual_map[m.second];

            if (idx1 == idx2){ // already merged
                it = mlist.erase(it);
                continue;
            }
            
            RType rtype = ig.nodes[idx1].type; // assert: node1 and node2 are same type
            int rcount = (rtype == GP)? regInfo.gp_rcount : regInfo.fp_rcount;
            
            std::unordered_set<int> set_union = ig.smart_union(m.first, m.second);

            int merge_type = ig.merge_type(m.first, m.second);
            
            // if node is not coloured coalesce via briggs otherwise georges
            if (merge_type == BRIGG && ig.briggs_safe(set_union, rcount)){
                fix = false;
                ig.merge_nodes(m.first, m.second);
                it = mlist.erase(it);
            }
            else if (merge_type == GEORGE && ig.george_safe(idx1, idx2, rcount)){
                fix = false;
                ig.merge_nodes(m.first, m.second);
                it = mlist.erase(it);
            }
            else it++;
        }
    }
}
