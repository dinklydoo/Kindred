#pragma once

#include "tac_ir.hpp"
#include "interf_graph.hpp"

enum CompileTarget {
    X86, ARM, MIPS // idk why mips is here
};

struct RegCount {
    int gp_rcount; // number of gp registers
    int fp_rcount; // number of fp registers

    RegCount(CompileTarget target) {
        switch (target) {
            case (X86) : {
                gp_rcount = 12; // exlude rbp, rsp, rax, rdx
                fp_rcount = 16;
            }
            default : {}// :-)
        }
    }
};

struct LivenessAnalyzer {
    private: 
        LivenessAnalyzer(CompileTarget target) : regInfo(target) {}
        void live_func(FunctionIR& prog);
        
        void add_interference_edges(Instruction& ins, virtual_varset& live, InterferenceGraph& graph);
        void process_block(Block* b, InterferenceGraph& graph, movelist& moves);
        void move_coalesce(InterferenceGraph& ig, movelist& moves);
        
    public:
        static LivenessAnalyzer& instance(CompileTarget target){
            static LivenessAnalyzer lan(target);
            return lan;
        }
        std::vector<InterferenceGraph> ig;
        RegCount regInfo;
        void gen_interference(FunctionIR& func, InterferenceGraph& graph);
};