#pragma once
#include <string>
#include "tac_ir.hpp"

struct X86_CodeGen {
    static X86_CodeGen& instance(std::string path){
        static X86_CodeGen cg;
        cg.path = path;
        return cg;
    }
    std::string path;

    void write_header();
    void write_func(FunctionIR& func);
    void write_ins(Instruction& func);
    void write_gp_ins(Instruction& func);
    void write_fp_ins(Instruction& func);
};