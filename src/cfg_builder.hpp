#include "tac_ir.hpp"
#include <unordered_map>

namespace cfg {

struct CFGBuilder {
    static CFGBuilder& instance(){
        static CFGBuilder instance;
        return instance;
    }
    // map block names to indices
    std::unordered_map<std::string, Block*> JMP_table;
    
    void enter_function() { JMP_table.clear(); }

    void build_cfg(std::vector<FunctionIR>& program);

    void cons_jmp_table(FunctionIR& func);
    void build_function_cfg(FunctionIR& func);
};

}