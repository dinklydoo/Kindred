#pragma once

#include "interf_graph.hpp"
#include "tac_ir.hpp"
#include "x86_regalloc.hpp"
#include <unordered_map>
#include <unordered_set>

static std::vector<GPReg> gp_params = {RDI, RSI, RDX, RCX, R8, R9};
static std::vector<FPReg> fp_params = {XMM0, XMM1, XMM2, XMM3, XMM4, XMM5};

struct StaticData {
    std::vector<std::string> closures;
    std::unordered_set<std::string> externs;

    std::unordered_map<Operand, std::string, Operand::OperandHash> float_imms;
};

struct X86_Lowerer {
    static X86_Lowerer& instance(){
        static X86_Lowerer xl;
        return xl;
    }

    StaticData statics;
    InterferenceGraph ig;

    InterferenceGraph lower_x86(FunctionIR& func);
    void shift_params(FunctionIR& func);
    void lower_ins(FunctionIR& func);
    void assign_statics(FunctionIR& func);
    void fix_jumps(FunctionIR& func);

    void write_statics();
};
