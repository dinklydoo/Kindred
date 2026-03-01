#pragma once
#include <string>
#include "tac_ir.hpp"
#include "x86/x86_regalloc.hpp"

using regset = std::set<GPReg>;
static regset CALLEE_SAVE = {RBX, R12, R13, R14, R15};

struct X86_CodeGen {
    static X86_CodeGen& instance(std::string path){
        static X86_CodeGen cg = X86_CodeGen(path);
        return cg;
    }
    std::string path;
    std::ofstream sfile;

    Operation jump_flag;
    regset preserved;

public:
    void generate_asm(std::vector<FunctionIR>& prog);    

private:
    X86_CodeGen(std::string p){
        path = p;
        sfile.open(path, std::ios::trunc);
        sfile.close();
        sfile.open(path, std::ios::app);
    }

    std::string reg_string(Operand op, DataType type);

    void generate_prologue(FunctionIR& func);
    void generate_epilogue(FunctionIR& func);

    void write_header();
    void write_func(FunctionIR& func);
    void write_ins(Instruction& func);
    void write_gp_ins(Instruction& func);
    void write_fp_ins(Instruction& func);
};