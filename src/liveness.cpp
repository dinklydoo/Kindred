#include "liveness.hpp"
#include "tac_ir.hpp"

void LivenessAnalyzer::liveness_opt(std::vector<FunctionIR>& prog){
    analyze(prog);
}

void LivenessAnalyzer::analyze(std::vector<FunctionIR>& prog){
    for (FunctionIR& func : prog){
        live_func(func);
    }
}

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

bool valid_operand(Operand op, opset& params){
    return (op.type != Operand::IMM && op.value > -1 && !params.contains(op));
}

InterferenceGraph LivenessAnalyzer::gen_interference(FunctionIR& func){
    InterferenceGraph graph;

    opset params;
    Block* header = func.blocks[0].get(); // contains parameter info
    for (Instruction& ins : header->ins){ // directly allocate parameters
        if (ins.op == Operation::LOCAL){
            IGNode& node = graph.get_node(ins.src1, ins.type);
            if (is_fp(ins.type)){
                if (regInfo.fpp_alloc < regInfo.fp_param)
                    node.assigned = ++regInfo.fpp_alloc;
                else node.spill = true;
            }
            else {
                if (regInfo.gpp_alloc < regInfo.gp_param)
                    node.assigned = ++regInfo.gpp_alloc;
                else node.spill = true;
            }
            params.insert(ins.src1);
        }
    }
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        virtual_varset live = b->live_out;
        for (auto it = live.begin(); it != live.end(); ){
            if (params.contains(it->first)) it = live.erase(it);
            else ++it;
        }
        for (auto it = b->ins.rbegin(); it != b->ins.rend(); it++){
            Instruction& ins = *it;
            virtual_varset defines;
            virtual_varset uses;

            // params will never be mov
            if (valid_operand(ins.dst, params)) defines.insert({ins.dst, ins.type});
            if (valid_operand(ins.src1, params)) uses.insert({ins.src1, ins.type});
            if (valid_operand(ins.src2, params)) uses.insert({ins.src2, ins.type});

            for (virtual_var def : defines){
                graph.get_node(def.first, def.second); // create node if doesn't exist
                for (virtual_var var : live){
                    if (is_fp(var.second) == is_fp(def.second)){
                        graph.get_node(var.first, var.second);
                        graph.add_edge(var.first, def.first);
                    }
                }
                if (live.contains(def)) live.erase(def);
            }
            for (virtual_var u : uses) live.insert(u);
        }
    }
    return graph;
}