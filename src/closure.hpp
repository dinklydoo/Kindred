#include "ast.hpp"
#include "visitor.hpp"
#include <cstddef>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <set>

namespace cs {

using rename_map = std::unordered_map<std::string, std::string>;
using func_names = std::unordered_set<std::string>;
/*
    Rename functions to be global unique,
    this is essential for IR/codegen as function names are not abstracted
    as variable names are abstracted/redundant in final representation
    don't need to check for variable name collision
*/
struct FunctionRenamer {
    func_names defined= {"read", "print"}; // add all function names used by library
    rename_map func_rename;

    std::string declare_func(std::string fn){
        if (!defined.count(fn)){
            defined.insert(fn);
            func_rename[fn] = fn;
        }
        else {
            std::string remap = fn;
            while (defined.count(remap)) remap = '_'+remap;
            defined.insert(remap);
            func_rename[fn] = remap;
        }
        return func_rename[fn];
    }

    std::string get_func(std::string fn){
        return func_rename[fn];
    }
    
};

using owner = std::unordered_map<std::string, std::string>;
struct VariableMap {
    std::stack<std::string> own;
    std::vector<owner> ownership; // variable points to function that owns

    void enter_function(std::string fn){
        ownership.emplace_back();
        own.push(fn);
    } // enter a super-function (non nested)
    void exit_function(){
        ownership.pop_back(); 
        own.pop();
    }
    void push_scope(){ ownership.emplace_back(); }
    void pop_scope(){ ownership.pop_back(); }

    void declare_var(std::string var){
        if (!own.empty()) ownership.back().emplace(var, own.top());
    }

    bool func_owns(std::string var){
        std::string owner = get_owner(var);
        return (owner.empty() || owner == own.top());
    }

    std::string get_owner(std::string var){
        for (auto& o : ownership){
            if (o.count(var)) return o[var];
        }
        return ownership.back()[var]; // wont hit
    }
};

using var = std::pair<std::string, type_ptr>;
using varset = std::set<var>;
struct Captures {
    std::vector<varset> captures;

    void enter_function(){captures.emplace_back();}
    void exit_function(){captures.pop_back();}

    void capture_var(std::string var, type_ptr type){ 
        captures.back().insert({var, type}); 
    }
};

struct ClosureGen : Visitor {
    static ClosureGen& instance() {
        static ClosureGen cg;
        return cg;
    }
    // using shared instance of types
    TypeSystem& type_s = TypeSystem::instance();

    VariableMap var_map;
    FunctionRenamer func_rn;
    Captures func_cap;

    void generate( ModuleNode& node );

    void visit( VarDecl& node) override ;
    void visit( FuncDecl& node) override;
    void visit( EnumDecl& node) override {};
    void visit( StructDecl& node) override {};
    void visit( UnaryNode& node) override ;
    void visit( BinaryNode& node) override ;
    void visit( CallNode& node) override ;
    void visit( StructNode& node) override ;
    void visit( AccessNode& node) override ;
    void visit( NominalNode& node) override ;
    void visit( CharLit& node) override {};
    void visit( IntLit& node) override {};
    void visit( FloatLit& node) override {};
    void visit( BoolLit& node) override {};
    void visit( ListPatternLit& node) override;
    void visit( StructPatternLit& node) override;
    void visit( EnumLit& node) override {};
    void visit( DefaultLit& node) override {};
    void visit( ElseLit& node) override {};
    void visit( NilLit& node) override {};
    void visit( EmptyLit& node) override {};
    void visit( ReturnNode& node) override ;
    void visit( CaseNode& node) override;
    void visit( CaseBranchNode& node) override;
    void visit( GuardNode& node) override;
    void visit( GuardBranchNode& node) override;
    void visit( ListNode& node) override ;
    void visit( ProgramNode& node) override;
    void visit( ModuleNode& node) override;
    void visit( ReadNode& node) override {};
    void visit( PrintNode& node) override {};
};

}