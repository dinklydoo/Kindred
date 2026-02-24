#include "cfg_builder.hpp"
#include "tac_ir.hpp"

using namespace cfg;

void CFGBuilder::build_cfg(std::vector<FunctionIR>& program){
    for (FunctionIR& func : program){
        build_function_cfg(func);
    }
}

void CFGBuilder::cons_jmp_table(FunctionIR& func){
    for (int i = 0; i < func.blocks.size(); i++){
        JMP_table[func.blocks[i]->label] = func.blocks[i].get();
    }
}

void CFGBuilder::build_function_cfg(FunctionIR& func){
    enter_function();
    cons_jmp_table(func);

    for (int i = 0; i < func.blocks.size(); i++){
        for (auto& ins : func.blocks[i]->ins){
            if (ins.op == Operation::JMP || ins.op == Operation::JMP_IF){
                std::string jmp_target = ins.target;
                Block* jmp_block = JMP_table[jmp_target];
                func.blocks[i]->out_edge.insert(jmp_block);
                jmp_block->in_edge.insert(func.blocks[i].get());
            }
        }
        Instruction& end = func.blocks[i]->ins.back();
        if (end.op != Operation::RET && 
            end.op != Operation::JMP && 
            end.op != Operation::JMP_IF
        ){ // fallthrough
            Block* jmp_block = func.blocks[i+1].get();
            func.blocks[i]->out_edge.insert(jmp_block);
            jmp_block->in_edge.insert(func.blocks[i].get());
        }
    }
}