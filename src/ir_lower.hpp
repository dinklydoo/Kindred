#include "types.hpp"
#include "visitor.hpp"
#include "tac_ir.hpp"
#include <unordered_map>
#include <stack>
namespace ir {

using scope = std::unordered_map<std::string, unsigned int>;
using function_map = std::unordered_map<std::string, std::vector<int>>;
using struct_map = std::unordered_map<std::string, scope>;

struct FunctionMap {
    function_map mapping;
};

struct StructMap {
    struct_map mapping;

    void add_struct(std::string sn, std::vector<Field>& fields){
        scope temp = {};
        for (Field& f : fields){
            temp.emplace(f.name, temp.size());
        }
        mapping[sn] = temp;
    }
    void add_enum(std::string en, std::vector<std::string>& enums){
        scope temp = {};
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
    int struct_count(){ return mapping.size(); }
};

struct IDVarScope {
    std::vector<scope> stack;
    static unsigned int ident_count;

    unsigned int get_ident(std::string label){
        for (scope& s : stack){
            if (s.contains(label)) return s[label];
        }
        scope& top = stack.back();
        top[label] = ident_count++;
        return top[label];
    }

    void push_scope(){ stack.emplace_back(); }
    void pop_scope() { stack.pop_back(); }
};

struct Closure {
    // track which parameters must be heap allocated for higher order functionality
};

struct FunctionIRBuilder {
    static int function_count;
    int block_count;

    FunctionIR function_ir;
    std::stack<Operand> op_stack;
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
    FunctionMap functionID;
    StructMap structInfo;

    std::vector<FunctionIR> IRprogram;

    void lower( ModuleNode& node );
    void generate_struct_file();
    void close_struct_file();

    void visit( VarDecl& node) override {};
    void visit( FuncDecl& node) override ;
    void visit( EnumDecl& node) override ;
    void visit( StructDecl& node) override ;
    void visit( UnaryNode& node) override {};
    void visit( BinaryNode& node) override {};
    void visit( CallNode& node) override {};
    void visit( StructNode& node) override {};
    void visit( AccessNode& node) override {};
    void visit( NominalNode& node) override {};
    void visit( CharLit& node) override {};
    void visit( IntLit& node) override {};
    void visit( FloatLit& node) override {};
    void visit( BoolLit& node) override {};
    void visit( ListPatternLit& node) override {};
    void visit( StructPatternLit& node) override {};
    void visit( EnumLit& node) override {};
    void visit( DefaultLit& node) override {};
    void visit( ElseLit& node) override {};
    void visit( NilLit& node) override{};
    void visit( EmptyLit& node) override{};
    void visit( ReturnNode& node) override {};
    void visit( CaseNode& node) override{};
    void visit( CaseBranchNode& node) override{};
    void visit( GuardNode& node) override{};
    void visit( GuardBranchNode& node) override{};
    void visit( ListNode& node) override {};
    void visit( ProgramNode& node) override{};
    void visit( ModuleNode& node) override;
    void visit( ReadNode& node) override {};
    void visit( PrintNode& node) override {};
};

}