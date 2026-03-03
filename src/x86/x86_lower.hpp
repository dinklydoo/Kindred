#pragma once

#include "compile_flags.hpp"
#include "interf_graph.hpp"
#include "tac_ir.hpp"
#include "x86_regalloc.hpp"
#include <unordered_map>
#include <unordered_set>

// param registers
static std::vector<GPReg> gp_params = {RDI, RSI, RDX, RCX, R8, R9};
static std::vector<FPReg> fp_params = {XMM0, XMM1, XMM2, XMM3, XMM4, XMM5};

// define a set of three scratch registers, optimal as an instruction can have at most 3 spilled registers
static std::vector<GPReg> gp_scratch = {R9, R10, R11};
static std::vector<FPReg> fp_scratch = {XMM10, XMM11, XMM12};

struct StaticData {
    std::unordered_set<std::string> closures;
    std::unordered_set<std::string> externs;

    std::unordered_map<Operand, std::string, Operand::OperandHash> float_imms;
};

struct X86_Lowerer {
    static X86_Lowerer& instance(ObjectFormat OBJECT_FORMAT){
        static X86_Lowerer xl;
        xl.OBJECT_FORMAT = OBJECT_FORMAT;
        return xl;
    }
    ObjectFormat OBJECT_FORMAT;
    InterferenceGraph lower_x86(FunctionIR& func);
    void write_statics();

private:
    StaticData statics;
    InterferenceGraph ig;

    void shift_params(FunctionIR& func);
    void lower_ins(FunctionIR& func);
    void assign_statics(FunctionIR& func);
    void fix_jumps(FunctionIR& func);

};
