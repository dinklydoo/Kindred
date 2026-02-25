#pragma once

#include "tac_ir.hpp"
#include "interf_graph.hpp"
#include "x86/x86_regalloc.hpp"

enum CompileTarget {
    X86, ARM, MIPS // idk why mips is here
};

struct RegCount {
    int gp_rcount; // number of gp registers
    int fp_rcount; // number of fp registers

    std::vector<int> GP_CALLER_SAVE;
    std::vector<int> FP_CALLER_SAVE;

    RegCount(CompileTarget target) {
        switch (target) {
            case (X86) : {
                gp_rcount = 14; 
                fp_rcount = 16;

                GP_CALLER_SAVE = { RAX, RCX, RDX, RSI, RDI, R8, R9, R10, R11 };
                FP_CALLER_SAVE = 
                {
                    XMM0, XMM1, 
                    XMM2, XMM3, 
                    XMM4, XMM5,
                    XMM6, XMM7, 
                    XMM8, XMM9, 
                    XMM10, XMM11,
                    XMM12, XMM13, 
                    XMM14, XMM15
                };
            }
            default : {}// :-)
        }
    }
};

struct LivenessAnalyzer {
    private: 
        LivenessAnalyzer(CompileTarget target) : regInfo(target), target(target) {}
        void pre_liveness(FunctionIR&);
        void live_func(FunctionIR&);
        
        void add_interference_edges(Instruction& ins, virtual_varset& live, InterferenceGraph& graph);
        void process_block(Block* b, InterferenceGraph& graph, movelist& moves);
        void move_coalesce(InterferenceGraph& ig, movelist& moves);

        void X86_interference(Instruction& ins, virtual_varset& defines, InterferenceGraph& graph);
    public:
        static LivenessAnalyzer& instance(CompileTarget target){
            static LivenessAnalyzer lan(target);
            return lan;
        }
        CompileTarget target;
        RegCount regInfo;
        void gen_interference(FunctionIR& func, InterferenceGraph& graph);
};