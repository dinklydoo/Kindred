#include "x86_regalloc.hpp"
#include "interf_graph.hpp"
#include "liveness.hpp"
#include "cfg_builder.hpp"
#include "tac_ir.hpp"
#include "x86_lower.hpp"

void RegAllocator::allocate_prog(std::vector<FunctionIR>& prog){
    for (FunctionIR& func : prog){
        allocate_func(func);
    }
    X86_Lowerer& xl = X86_Lowerer::instance();
    xl.write_statics();
    write_ir(prog);
}

void RegAllocator::allocate_func(FunctionIR& prog){
    X86_Lowerer& xl = X86_Lowerer::instance();
    ig = xl.lower_x86(prog);
    
    LivenessAnalyzer& la = LivenessAnalyzer::instance(X86);
    spill_offset = 0;
    while (true) {
        ig = InterferenceGraph();
        la.gen_interference(prog, ig);
        rewrite_coalesce(prog);
        ig.spill_offset = spill_offset; // retain stack offset
        if (is_colourable(prog)) break;
        spill_offset = ig.spill_offset;
    }
    allocate_reg(prog);
    convert_reg(prog);
}

/*
    Check whether any nodes are left uncoloured in the graph
*/
bool InterferenceGraph::is_uncoloured(){
    for (IGNode& node : nodes){
        if (!node.valid || node.simplified) continue;

        if (!node.allocated()) return true;
    }
    return false;
}

IGNode* InterferenceGraph::get_low_deg(){
    for (IGNode& node : nodes){
        if (!node.valid || node.simplified) continue;
        if (node.allocated()) continue;

        int K = (node.type == GP)? GPR_count : FPR_count;
        if (get_interf_size(node) < K) return &node;
    }
    return nullptr;
}

IGNode& InterferenceGraph::spill_node(){
    IGNode* candidate = nullptr;
    double candidate_cost = 0;
    for (IGNode& node : nodes){
        if (!node.valid || node.simplified || node.allocated()) continue;

        int deg = get_interf_size(node);
        if (deg == 0) deg = 1;

        double cost = (double)node.uses / deg;

        if (!candidate) candidate = &node;
        else if (cost < candidate_cost){
            candidate = &node;
            candidate_cost = cost;
        }
    }
    spill_offset -= 8;
    candidate->spill = spill_offset;
    return *candidate;
}

/*
    Agressive spill handling, on single spill rewrite IR to include spill
    with short-lived temps
*/
void RegAllocator::rewrite_spill(FunctionIR& func, Operand op, int spill){
    Operand _ebp = Operand::rbp(spill);
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end(); ){
            Instruction& ins = *it;

            if (ins.dst == op){
                Operand _t = func.get_register();
                ins.dst = _t;
                it++;
                b->ins.insert(it, {Operation::STORE, ins.type, _ebp, _t});
                continue;
            }

            if (ins.src1 == op || ins.src2 == op){
                Operand _t = func.get_register();
                if (ins.src1 == op) ins.src1 = _t;
                if (ins.src2 == op) ins.src2 = _t;
                b->ins.insert(it, {Operation::LOAD, ins.type, _t, _ebp});
            }
            it++;
        }
    }
}

/*
    Rewrite for coalesced nodes, delete mov instances
    replace nodes with coalesce
*/
void RegAllocator::rewrite_coalesce(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end(); it++){
            Instruction& ins = *it;

            // two nodes are coalesced (pure move -> copy -> delete instruction)
            if (ins.op == Operation::MOV && ig.coalesced(ins.dst, ins.src1)){ 
                it = b->ins.erase(it); continue;
            }
            
            // replace registers with coalesced operand
            if (ins.dst.is_register()) ins.dst = ig.get_node(ins.dst).op;
            if (ins.src1.is_register()) ins.src1 = ig.get_node(ins.src1).op;
            if (ins.src2.is_register()) ins.src2 = ig.get_node(ins.src2).op;
        }
    }
}

bool RegAllocator::is_colourable(FunctionIR& func){
    simplify_stack.clear();
    while (ig.is_uncoloured()){
        IGNode* node_ptr = ig.get_low_deg();
        if (!node_ptr){
            IGNode& spilled = ig.spill_node();
            rewrite_spill(func, spilled.op, spilled.spill);
            //write_func(func);
            // restore state
            for (IGNode& node : ig.nodes) node.simplified = false;
            return false;
        }
        simplify_stack.push_back(node_ptr);
        IGNode& node = *node_ptr;
        node.simplified = true;
    }
    return true;
}

void RegAllocator::allocate_reg(FunctionIR& func){
    while (!simplify_stack.empty()){
        IGNode& node = *simplify_stack.back();
        simplify_stack.pop_back();

        if (node.spill) continue;

        int rcount = (node.type == GP)? GPR_count : FPR_count;
        std::vector<bool> free_reg(rcount, true);
        for (int inf : node.interfere){
            IGNode& temp = ig.nodes[inf];
            if (!temp.valid || temp.spill) continue;

            if (temp.allocated()) free_reg[temp.assigned] = false;
        }
        for (int i = 0; i < rcount; i++){
            if (free_reg[i]){ 
                node.assigned = i;
                break;
            }
        }
    }
}

Operand RegAllocator::get_phys_reg(Operand v){
    IGNode& node = ig.get_node(v);
    if (node.type == GP) return Operand::gpr(node.assigned);
    else return Operand::fpr(node.assigned);
}

void RegAllocator::convert_reg(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins){
            if (ins.dst.is_register())ins.dst = get_phys_reg(ins.dst);
            if (ins.src1.is_register())ins.src1 = get_phys_reg(ins.src1);
            if (ins.src2.is_register())ins.src2 = get_phys_reg(ins.src2);
        }
    }
}