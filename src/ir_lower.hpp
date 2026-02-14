#include "types.hpp"
#include "visitor.hpp"
#include "tac_ir.hpp"
#include <string>
#include <unordered_map>
#include <stack>

namespace ir {

using id_map = std::unordered_map<std::string, unsigned int>;
using struct_map = std::unordered_map<std::string, id_map>; // map struct fields and enumerables to id's
using env_map = std::unordered_map<std::string, id_map>;
using scope = std::unordered_map<std::string, std::pair<int, type_ptr>>; // map vars 
using layout_info = std::vector<std::vector<std::string>>;

/*
    Map constructors (structs/enums) to identifiers
    - Enums are enumerated from 1...n in order of declaration
    - Fields are indexed from 0 ... n-1 in order of declaration
    ( Fields are indexed as we call them by index in structs.c )
*/
struct StructMap {
    struct_map mapping;
    std::unordered_map<std::string, unsigned int> struct_id;

    void add_struct(std::string sn, std::vector<Field>& fields){
        struct_id.emplace(sn, struct_id.size());
        id_map temp = {};
        for (Field& f : fields){
            temp.emplace(f.name, temp.size());
        }
        mapping[sn] = temp;
    }
    void add_enum(std::string en, std::vector<std::string>& enums){
        id_map temp = {};
        for (std::string& e : enums){
            temp.emplace(e, temp.size() + 1);
        }
        mapping[en] = temp;
    }
    unsigned int get_enum_id(std::string en, std::string enumerable){
        return mapping[en][enumerable];
    }
    unsigned int get_field_id(std::string sn, std::string field){
        return mapping[sn][field];
    }
    unsigned int get_struct_id(std::string sn){
        return struct_id[sn];
    }
    int struct_count(){ return struct_id.size(); }
};

/*
    Environments are literally just glorified structs
*/
struct EnvMap {
    env_map mapping;
    std::unordered_map<std::string, unsigned int> env_id;

    void add_env(std::string fn, std::set<var>& vars){
        env_id.emplace(fn, env_id.size());
        id_map temp = {};
        for (var v : vars){
            temp.emplace(v.first, temp.size());
        }
        mapping[fn] = temp;
    }
    unsigned int get_env_id(std::string fn){
        return env_id[fn];
    }
    unsigned int get_var_id(std::string fn, std::string vn){
        return mapping[fn][vn];
    }
    int env_count(){ return env_id.size(); }
};

/*
    Map variables to identifiers,
    

*/
#define ENCLOSED 1
#define IDENT 0
#define NOT_FOUND -1
struct Scope {
    scope closure_id; // map variables in env to pair of {env_var_id, type}
    scope stack; // map generic variables to ids

    int contains(std::string var){
        if (closure_id.contains(var)) return ENCLOSED;
        if (stack.contains(var)) return IDENT;
        return NOT_FOUND;
    }

    std::pair<int, type_ptr>& get_enclosed(std::string var){ return closure_id[var]; }
    int get_ident(std::string var){ return stack[var].first; }

    void push_ident(std::string var, int id, type_ptr type){ stack[var] = {id, type}; }
    void push_enclosed(std::string var, int id, type_ptr type){ stack[var] = {id, type}; }
};
struct IDVarScope {
    std::vector<Scope> stack;
    unsigned int ident_count = 0;

    void get_var(std::string label); // pushes register with variable on stack

    void push_ident(std::string label, type_ptr type){ stack.back().push_ident(label, ident_count++, type); }
    void push_enclosed(std::string label, type_ptr type){ stack.back().push_enclosed(label, ident_count++, type); }

    void push_scope(){ stack.emplace_back(); }
    void pop_scope() { stack.pop_back(); }
};

struct ConsFunctionIR {
    FunctionIR function_ir;
    int function_id;
    int child_count = 0;
    int reg_count = 0;
    int block_count = 0;
    int case_count = 0;
    std::stack<Operand> op_stack;
    std::stack<std::string> label_stack;

    void push_instruction(Instruction ins){ function_ir.blocks.back().ins.push_back(ins); }
    void push_operand(Operand op){ op_stack.push(op); }
    Operand get_register(){ return Operand::reg(reg_count++); }
    Operand pop_operand(){ Operand temp = op_stack.top(); op_stack.pop(); return temp; }

    std::string pop_label(){ std::string temp = label_stack.top(); label_stack.pop(); return temp; }
    void push_block(){ function_ir.blocks.emplace_back(); block_count++; }
    Block& get_block(){ return function_ir.blocks.back(); }
};

/*
    Main function builder, for each function declaration
    we must construct its respective IR

*/
struct FunctionIRBuilder {
    int top_function_count = 0; // top level function count
    int scratch_label_count = 0;

    std::vector<ConsFunctionIR> stack;

    FunctionIR& top_function(){ return stack.back().function_ir; }
    void pop_function(){ stack.pop_back(); }
    ConsFunctionIR& top_constructor(){ return stack.back(); }
    void push_function(){
        int id = 1;
        if (!stack.empty()) id = ++top_constructor().child_count;
        else top_function_count++;
        stack.emplace_back();
        top_constructor().function_id = id;

        top_constructor().push_block();
    }
    std::string get_block_label(){ // meaningful block labels
        if (stack.empty()) return "早上好中国， 今天我要冰淇凌， 我很喜欢吃冰淇凌";
        std::string lab;
        lab +=".L_F"+std::to_string(top_function_count);
        for (int i = 0; i < stack.size(); i++){
            lab +='_'+std::to_string(stack[i].function_id);
        }
        lab +="_B"+std::to_string(top_constructor().block_count);
        return lab;
    }
    std::string get_scratch_label(){ return ".L_"+std::to_string(scratch_label_count++); }

    std::string get_case_label(){
        if (stack.empty()) return "早上好中国， 今天我要冰淇凌， 我很喜欢吃冰淇凌";
        return get_block_label()+"_case"+std::to_string(top_constructor().case_count++)+'_';
    }
};

struct IR_Lowerer : Visitor {
    static IR_Lowerer& instance() {
        static IR_Lowerer ir;
        return ir;
    }

    IDVarScope identifier;
    FunctionIRBuilder builder;

    // label functions L_F1 (for base) L_F1_1 (for nested)
    // label blocks as function scope and block id
    // L_F1_B1 (first block of top level function)
    // L_F2_3_B1 (first block of nested function)
    StructMap structInfo;
    EnvMap envInfo;

    std::vector<FunctionIR> IRprogram;
    int global_blocks = 0;
    std::unordered_map<std::string, int> JMPtable;

    void lower( ModuleNode& node );
    void generate_layout_file();
    void generate_layout(std::vector<type_ptr>, int id, int kind);
    void close_layout_file();

    void construct_env(std::string fn, type_ptr ftype, varset& enc);

    void cast_operand( Operand target, type_ptr fix, type_ptr cast );
    void op_equals( Operand ptr1, Operand ptr2, type_ptr type);
    void list_equals( Operand ptr1, Operand ptr2, type_ptr type);
    void struct_equals( Operand ptr1, Operand ptr2, type_ptr type);
    void increase_ref( Operand ptr, type_ptr type);
    void generate_node( Operand elem, type_ptr ltype, type_ptr type);

    void short_and( BinaryNode& );
    void short_or( BinaryNode& );

    void list_pattern_vars(LiteralNode& node);
    void struct_pattern_vars(LiteralNode& node);

    // visitor boilerplate
    void visit( VarDecl& node) override ;
    void visit( FuncDecl& node) override ;
    void visit( EnumDecl& node) override ;
    void visit( StructDecl& node) override ;
    void visit( UnaryNode& node) override ;
    void visit( BinaryNode& node) override ;
    void visit( CallNode& node) override ;
    void visit( StructNode& node) override ;
    void visit( AccessNode& node) override ;
    void visit( NominalNode& node) override ;
    void visit( CharLit& node) override ;
    void visit( IntLit& node) override ;
    void visit( FloatLit& node) override ;
    void visit( BoolLit& node) override ;
    void visit( EmptyLit& node) override ;
    void visit( ListPatternLit& node) override ;
    void visit( NilLit& node) override ;
    void visit( StructPatternLit& node) override ;
    void visit( EnumLit& node) override ;
    void visit( DefaultLit& node) override ;
    void visit( ElseLit& node) override ;
    void visit( ReturnNode& node) override ;
    void visit( CaseNode& node) override ;
    void visit( CaseBranchNode& node) override ;
    void visit( GuardNode& node) override ;
    void visit( GuardBranchNode& node) override ;
    void visit( ListNode& node) override ;
    void visit( ProgramNode& node) override ;
    void visit( ModuleNode& node) override;
    void visit( ReadNode& node) override {};
    void visit( PrintNode& node) override {};

    void print_ir(){
        for (FunctionIR& ir : IRprogram){
            ir.print_ir();
            std::cout << '\n';
        }
    }

    void gen_block(std::string label){
        ConsFunctionIR& cons = builder.top_constructor();
        cons.push_block();
        JMPtable[label] = ++global_blocks;
        cons.push_instruction({Operation::LABEL, DataType::EMPTY, {}, {}, {}, label});
    }
};

}