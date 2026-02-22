#include "liveness.hpp"
#include "interf_graph.hpp"
#include "tac_ir.hpp"
#include <vector>


// calculate liveness sets for variables for each function
void LivenessAnalyzer::live_func(FunctionIR& func){
    bool done = false;
    while (!done){
        done = true;
        for (auto b_it = func.blocks.rbegin(); b_it != func.blocks.rend(); b_it++){
            Block* b = b_it->get();
            virtual_varset temp_in = b->live_in;
            virtual_varset temp_out = b->live_out;

            for (virtual_var v : b->use) b->live_in.insert(v);
            for (virtual_var v : b->live_out){
                if (!b->def.count(v)) b->live_in.insert(v);
            }
            for (Block* suc : b->out_edge){
                for (virtual_var v : suc->live_in) b->live_out.insert(v);
            }
            if (temp_in != b->live_in || temp_out != b->live_out) done = false;
        }
    }
}

void LivenessAnalyzer::add_interference_edges(Instruction& ins, virtual_varset& live, InterferenceGraph& graph) {
    virtual_varset defines, uses;
    if (ins.dst.is_register()) defines.insert({ins.dst, ins.type});
    if (ins.src1.is_register()){ 
        uses.insert({ins.src1, ins.type});
        graph.incr_uses(ins.src1, ins.type);
    }
    if (ins.src2.is_register()){ 
        uses.insert({ins.src2, ins.type});
        graph.incr_uses(ins.src2, ins.type);
    }

    if (ins.op == Operation::CALL){
        for (int clobber_gp : regInfo.GP_CALLER_SAVE){ 
            defines.insert({Operand::gpr(clobber_gp), DataType::I64});
            IGNode& node = graph.add_node(Operand::gpr(clobber_gp), DataType::I64);
            node.assigned = clobber_gp;
        }
        for (int clobber_fp : regInfo.FP_CALLER_SAVE){ 
            defines.insert({Operand::fpr(clobber_fp), DataType::F64});
            IGNode& node = graph.add_node(Operand::fpr(clobber_fp), DataType::F64);
            node.assigned = clobber_fp;
        }
    }
    for (virtual_var def : defines) {
        graph.add_node(def.first, def.second); // ensure node exists
        for (virtual_var var : live) {
            if (is_fp(var.second) == is_fp(def.second)) {
                graph.add_node(var.first, var.second);
                graph.add_edge(var.first, def.first);
            }
        }
        live.erase(def);
    }
    for (virtual_var u : uses) live.insert(u);
}

void LivenessAnalyzer::process_block(Block* b, InterferenceGraph& graph, movelist& moves) {
    virtual_varset live = b->live_out;

    for (auto it = b->ins.rbegin(); it != b->ins.rend(); it++) {
        Instruction& ins = *it;

        if (ins.is_move() && ins.src1.is_register())
            moves.push_back({ins.dst, ins.src1});

        add_interference_edges(ins, live, graph);
    }
}

void LivenessAnalyzer::gen_interference(FunctionIR& func, InterferenceGraph& graph) {
    func_ref = &func;
    movelist moves;
    live_func(func);
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

            if (idx1 == idx2){
                it = mlist.erase(it);
                continue;
            }
            
            IGNode::RType rtype = ig.nodes[idx1].type; // assert: node1 and node2 are same type
            int rcount = (rtype == IGNode::GP)? regInfo.gp_rcount : regInfo.fp_rcount;
            
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
