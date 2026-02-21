#include "x86_regalloc.hpp"
#include "interf_graph.hpp"
#include "liveness.hpp"
#include "tac_ir.hpp"

void RegAllocator::allocate_prog(std::vector<FunctionIR>& prog){
    for (FunctionIR& func : prog){
        allocate_func(func);
    }
    write_ir(prog);
}

void RegAllocator::move_params(FunctionIR& func){
    Block* header = func.blocks[0].get();
    for (Instruction& ins : header->ins){
        
    }
}

void RegAllocator::allocate_func(FunctionIR& prog){
    move_params(prog);

    LivenessAnalyzer la = LivenessAnalyzer::instance(X86);
    while (true) {
        ig = la.gen_interference(prog);
        ig.stack_offset = spill_offset; // retain stack offset
        precolor_func(prog);
        if (is_colourable(prog)) break;
        spill_offset = ig.stack_offset;
    }
    allocate_reg(prog);


}

/*
    TODO : insert moves for div/mul and shifts
*/
void RegAllocator::precolor_func(FunctionIR& prog){

    for (auto it = prog.blocks.begin(); it != prog.blocks.end(); it++){
        Block* block = it->get();
        for (Instruction& ins : block->ins){
            IGNode& dst = ig.get_node(ins.dst);
            IGNode& src1 = ig.get_node(ins.src1);
            IGNode& src2 = ig.get_node(ins.src2);
            switch (ins.op) {
                case (Operation::LSL) :
                case (Operation::LSR) : {
                    src2.assigned = static_cast<int>(RCX); // shift amount
                    break;
                }
                default : break;
            }
        }
    }
}

/*
    Check whether any nodes are left uncoloured in the graph
*/
bool InterferenceGraph::is_uncoloured(){
    for (IGNode& node : nodes){
        if (!node.valid || node.simplified) continue;

        if (!node.assigned && !node.spill) return true;
    }
    return false;
}

IGNode* InterferenceGraph::get_low_deg(){
    for (IGNode& node : nodes){
        if (!node.valid || node.simplified) continue;
        if (node.assigned || node.spill) continue;

        int K = (node.type == IGNode::GP)? GPR_count : FPR_count;
        if (get_interf_size(node) < K) return &node;
    }
    return nullptr;
}

IGNode& InterferenceGraph::spill_node(){
    IGNode* candidate = nullptr;
    for (IGNode& node : nodes){
        if (!node.valid || node.simplified || node.assigned) continue;

        if (!candidate) candidate = &node;
        else if (node.uses > candidate->uses) candidate = &node;
    }
    stack_offset += 8;
    candidate->spill = stack_offset;
    return *candidate;
}

/*
    Agressive spill handling, on single spill rewrite IR to include spill
    with short-lived temps
*/
void RegAllocator::rewrite_func(FunctionIR& func, Operand op, int spill){
    Operand _ebp = Operand::ebp(spill);
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end(); it++){
            Instruction& ins = *it;

            if (ins.dst == op){
                Operand _t = func.get_register();
                ins.dst = _t;
                b->ins.insert(++it, {Operation::STORE, ins.type, _ebp, _t});
            }

            if (ins.src1 == op || ins.src2 == op){
                Operand _t = func.get_register();
                if (ins.src1 == op) ins.src1 = _t;
                if (ins.src2 == op) ins.src2 = _t;
                b->ins.insert(it++, {Operation::LOAD, ins.type, _t, _ebp});
            }
        }
    }
}

bool RegAllocator::is_colourable(FunctionIR& func){
    while (ig.is_uncoloured()){
        IGNode* node_ptr = ig.get_low_deg();
        if (!node_ptr){
            IGNode& spilled = ig.spill_node();
            rewrite_func(func, spilled.op, spilled.spill);
            simplify_stack.clear();
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

        int rcount = (node.type == IGNode::GP)? GPR_count : FPR_count;
        std::vector<bool> free_reg(rcount+1, true); // 1 index
        if (node.type == IGNode::GP){ 
            free_reg[14] = free_reg[3] = false; // RAX/RDX (change this hardcoded rn)
        }
        for (int inf : node.interfere){
            IGNode& temp = ig.nodes[inf];
            if (!temp.valid || temp.spill) continue;

            if (temp.assigned) free_reg[temp.assigned] = false;
        }
        for (int i = 1; i <= rcount; i++){
            if (free_reg[i]) node.assigned = i;
            break;
        }
    }
}

