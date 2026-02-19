#include "ast.hpp"
#include "tac_ir.hpp"
#include <unordered_map>

enum class GPRReg {
    RAX, RBX,
    RCX, RDX,
    RSI, RDI,
    R10, R11,
    R12, R13,
    R14, R15,
};
enum class FPReg {
    XMM0, XMM1, 
    XMM2, XMM3, 
    XMM4, XMM5,
    XMM6, XMM7, 
    XMM8, XMM9, 
    XMM10, XMM11,
    XMM12, XMM13, 
    XMM14, XMM15
};

struct GPRRegInfo {
    enum Status {
        CALLER_SAVE, CALLEE_SAVE, RESERVE
    };
    GPRReg reg;
    Status status;
};

struct FPRegInfo {
    FPReg reg;
    bool reserved;
};

struct RegInfo {
    std::vector<GPRReg> free_GPR;
    std::vector<FPReg> free_FP;

    std::unordered_map<int, GPRReg> vr_phys_gpr;
    std::unordered_map<int, FPReg> vr_phys_fpr;

    std::unordered_map<int, int> vreg_to_stack; // spillover

    int stack_offset;
};

struct RegAllocator {
    static RegAllocator& instance(){
        static RegAllocator ra;
        return ra;
    }

    RegInfo reg_info;

    void allocate_prog(std::vector<FunctionIR>& prog);
    void allocate_func(FunctionIR& prog);
};
