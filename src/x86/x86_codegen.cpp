#include "x86_codegen.hpp"
#include "tac_ir.hpp"
#include <fstream>

void X86_CodeGen::write_header(){
    std::ofstream sfile(path, std::ios::trunc);
    sfile.close();
    sfile.open(path, std::ios::app);


    std::ifstream hfile("./.aux/static_data");
    sfile << hfile.rdbuf();
    hfile.close();
}

void X86_CodeGen::write_func(FunctionIR& func){
    
    
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins) write_ins(ins);
    }
    std::ofstream sfile(path, std::ios::app);
    sfile << '\n';
}

void X86_CodeGen::write_ins(Instruction& ins){
    std::ofstream sfile(path, std::ios::app);
    switch (ins.op){
        case (Operation::LABEL) : 
            sfile << ins.target; break;
        



        default : return;
    }   


}

void X86_CodeGen::write_fp_ins(Instruction& ins){
    std::ofstream sfile(path, std::ios::app);

    
}

void X86_CodeGen::write_gp_ins(Instruction& ins){
    std::ofstream sfile(path, std::ios::app);


}