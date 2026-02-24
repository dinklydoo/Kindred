#pragma once

#include "tac_ir.hpp"
#include "interf_graph.hpp"
#include <unordered_map>

enum GPReg {
    RDI, RSI, RDX, RCX, R8, R9,
    RBX, R10, R11, R12, R13, R14, R15,
    RAX

};
enum FPReg {
    XMM0, XMM1, 
    XMM2, XMM3, 
    XMM4, XMM5,
    XMM6, XMM7, 
    XMM8, XMM9, 
    XMM10, XMM11,
    XMM12, XMM13, 
    XMM14, XMM15
};

/*
    As param registers are 1-indexed in our interf graph,
    we can create a mapping from these forms to the actual register names
*/

static int GPR_count = 12;
static int FPR_count = 16;

struct GPRegInfo {
    enum Status {
        CALLER_SAVE, CALLEE_SAVE, RESERVE
    };
    GPReg reg;
    Status status;
};

struct FPRegInfo {
    FPReg reg;
    bool reserved;
};

struct RegInfo {
    std::unordered_map<Operand, GPReg, Operand::OperandHash> vr_phys_gpr;
    std::unordered_map<Operand, FPReg, Operand::OperandHash> vr_phys_fpr;

    void add_mapping(Operand op, GPReg reg){ vr_phys_gpr[op] = reg;}
    void add_mapping(Operand op, FPReg reg){ vr_phys_fpr[op] = reg;}
};

struct RegAllocator {
    static RegAllocator& instance(){
        static RegAllocator ra;
        return ra;
    }

    std::vector<IGNode*> simplify_stack;
    std::vector<bool> active; // active nodes
    int spill_offset = 0;
    int node_neighbours(); // get neighbour count during simplify phase

    InterferenceGraph ig;

    RegInfo reg_info;

    void move_params(FunctionIR& func); // move params to virtuals (prevents rdx/rcx conflict)

    void allocate_prog(std::vector<FunctionIR>& prog);
    void allocate_func(FunctionIR& func);
    void precolor_func(FunctionIR& func);

    void rewrite_coalesce(FunctionIR&);
    void rewrite_spill(FunctionIR&, Operand, int);
    bool is_colourable(FunctionIR&);
    void allocate_reg(FunctionIR&);

    Operand get_phys_reg(Operand);
    void convert_reg(FunctionIR&);
};
