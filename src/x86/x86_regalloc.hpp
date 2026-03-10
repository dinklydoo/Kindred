#pragma once

#include "compile_flags.hpp"
#include "tac_ir.hpp"
#include "interf_graph.hpp"
#include <string>
#include <unordered_map>

enum GPReg {
    RAX, RBX,
    RCX, RDX,
    RDI, RSI,
    R8, R9,
    R10, R11, 
    R12, R13, 
    R14, R15
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

static std::string x86_gpr_string(GPReg gpr, DataType dtype){
    std::string str = "r";
    if (dtype == DataType::I8 || dtype == DataType::BOOL) {
        switch (gpr) {
            case (RAX) : return "al";
            case (RBX) : return "bl";
            case (RCX) : return "cl";
            case (RDX) : return "dl";
            case (RDI) : return "dil";
            case (RSI) : return "sil";
            default : return 'r'+std::to_string(static_cast<int>(gpr) + 2)+'b';
        }
    }
    else if (dtype == DataType::I32){
        str = "e";
        switch (gpr) {
            case (RAX) : str += "ax"; break;
            case (RBX) : str += "bx"; break;
            case (RCX) : str += "cx"; break;
            case (RDX) : str += "dx"; break;
            case (RDI) : str += "di"; break;
            case (RSI) : str += "si"; break;
            default : str='r'+std::to_string(static_cast<int>(gpr) + 2)+'d';
        }
    }
    else {
        switch (gpr) {
            case (RAX) : str += "ax"; break;
            case (RBX) : str += "bx"; break;
            case (RCX) : str += "cx"; break;
            case (RDX) : str += "dx"; break;
            case (RDI) : str += "di"; break;
            case (RSI) : str += "si"; break;
            default : str+=std::to_string(static_cast<int>(gpr) + 2);
        }
    }
    return str;
}

static std::string x86_fpr_string(FPReg gpr){
    return "xmm"+std::to_string(static_cast<int>(gpr));
}

static std::vector<GPReg> GPR_scratch = {R10, R11};
static std::vector<FPReg> FPR_scratch = {XMM14, XMM15};

static int GPR_count = 14 - GPR_scratch.size();
static int FPR_count = 16 - FPR_scratch.size();

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

struct X86_RegAlloc {
    static X86_RegAlloc& instance(){
        static X86_RegAlloc ra;
        return ra;
    }
    void allocate_prog(std::vector<FunctionIR>& prog, ObjectFormat OBJECT_FORMAT);

private:
    std::vector<IGNode*> simplify_stack;
    std::vector<bool> active; // active nodes
    int node_neighbours(); // get neighbour count during simplify phase
    InterferenceGraph ig;
    RegInfo reg_info;

    void allocate_func(FunctionIR& func, ObjectFormat OBJECT_FORMAT);

    void move_params(FunctionIR& func); // move params to virtuals (prevents rdx/rcx conflict)
    void add_nodes(FunctionIR& func);

    void precolor_locals(FunctionIR& func);
    void precolor_func(FunctionIR& func);
    void precolor_params(std::list<Instruction>::iterator it);

    IGNode& spill_node(FunctionIR& func);

    void rewrite_coalesce(FunctionIR&);
    void rewrite_spill(FunctionIR&, Operand, int);
    bool is_colourable(FunctionIR&);
    void allocate_reg(FunctionIR&);

    Operand get_phys_reg(Operand);
    Operand get_scratch_reg(Instruction&, RType);
    void convert_reg(FunctionIR&);
};
