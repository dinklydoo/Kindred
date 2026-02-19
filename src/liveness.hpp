#include "tac_ir.hpp"
#include <map>
#include <unordered_set>

enum CompileTarget {
    X86, ARM, MIPS
};

struct RegInfo {
    int gp_param; // number of gp param registers
    int fp_param; // number of fp param registers

    // directly allocate params
    int gpp_alloc = 0;
    int fpp_alloc = 0;
    RegInfo(CompileTarget target) {
        switch (target) {
            case (X86) : {
                gp_param = 6; // rdi, rsi, rdx, rcx, r8, r9
                fp_param = 8; // xmm0-7
            }
            default : {}// :-)
        }
    }
};


struct IGNode {
    enum RType { GP, FP };
    Operand op;
    RType type;
    std::unordered_set<int> interfere;
    int assigned;
    bool spill = false;
};

struct InterferenceGraph {
    std::unordered_map<Operand, int, Operand::OperandHash> virtual_map;
    std::vector<IGNode> nodes;

    IGNode& get_node(Operand op, DataType type){
        if (!virtual_map.contains(op)){
            IGNode::RType rtype = ((type == DataType::F32 || type == DataType::F64)? 
                IGNode::RType::FP : IGNode::RType::GP
            );
            nodes.push_back({op, rtype});
            virtual_map[op] = nodes.size() - 1;
        }
        return nodes[virtual_map[op]];
    }
    void add_edge(Operand v1, Operand v2){
        int i = virtual_map[v1];
        int j = virtual_map[v2];
        if (i == j) return;
        nodes[i].interfere.insert(j);
        nodes[j].interfere.insert(i);
    }
};

struct LivenessAnalyzer {
    private: 
        LivenessAnalyzer(CompileTarget target) : regInfo(target) {}

    public:
        static LivenessAnalyzer& instance(CompileTarget target){
            static LivenessAnalyzer lan(target);
            return lan;
        }
        InterferenceGraph ig;
        RegInfo regInfo;

        void liveness_opt(std::vector<FunctionIR>& prog);
        void analyze(std::vector<FunctionIR>& prog);
        void live_func(FunctionIR& prog);

        InterferenceGraph gen_interference(FunctionIR& prog);
};