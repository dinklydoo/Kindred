#include "types.hpp"
#include "visitor.hpp"
#include <map>
#include <stack>

using scope = std::map<std::string, type_ptr>;

struct TypeVarScope{
    std::vector<scope> stack;

    // find a variable in range of all current scopes
    type_ptr find_var(std::string label){
        for (auto& sp : stack){
            if (sp.count(label)) return sp[label];
        }
        return nullptr;
    }

    //Push a new variable declaration into the CURRENT scope
    void push_var(std::string label, type_ptr type){
        auto& t = stack.back();
        if (find_var(label)){
            // throw error
            return;
        }
        t.emplace(label, type);
    }

    void push_scope(){ stack.emplace_back(); }
    void pop_scope(){ stack.pop_back(); }
};

/*
    Running top down type check requires memory of types

    - variable:  l_val type is propogated to r_val type
    - function:  return type propogated to return value expression
    - pattern expression:  must propogate to pattern branch types
    - guard expression: default pushes bool type for its children
    - list expression:  must check all children match list type

*/
struct TypePropogator{
    std::stack<type_ptr> stack;
    bool binding = true;

    void set_unbound(){ binding = false; }
    void set_bound(){ binding = true; }

    bool is_bound(){ return (binding && !stack.empty()); }

    void prop_type(type_ptr t){ stack.push(t); }
    type_ptr unprop_type(){ 
        auto t = stack.top();
        stack.pop(); 
        return t;
    }
};

struct TypeChecker : Visitor{
    static TypeChecker& instance() {
        static TypeChecker tc;
        return tc;
    }
    // using shared instance of types
    TypeSystem& type_s = TypeSystem::instance();

    // types of declarations (functions, enums, structs) in global scope
    TypeVarScope definitions;

    TypePropogator typeprop;

    /*
    Visitor definitions, double dispatched
    */
    virtual void visit( VarDecl& node) override;
    virtual void visit( FuncDecl& node) override;
    virtual void visit( EnumDecl& node) override;
    virtual void visit( StructDecl& node) override;
    virtual void visit( UnaryNode& node) override;
    virtual void visit( BinaryNode& node) override;
    virtual void visit( ParamNode& node) override;
    virtual void visit( NominalNode& node) override;
    virtual void visit( IntLit& node) override;
    virtual void visit( FloatLit& node) override;
    virtual void visit( BoolLit& node) override;
    virtual void visit( ListLit& node) override;
    virtual void visit( ListPatternLit& node) override;
    virtual void visit( EnumLit& node) override;
    virtual void visit( CaseNode& node) override;
    virtual void visit( CaseBranchNode& node) override;
    virtual void visit( GuardNode& node) override;
    virtual void visit( GuardBranchNode& node) override;
    virtual void visit( ListNode& node) override;
    virtual void visit( ProgramNode& node) override;
    virtual void visit( ModuleNode& node) override;
    virtual void visit( ReadNode& node) override;
    virtual void visit( PrintNode& node) override;

    virtual type_ptr cast_type(type_ptr a, type_ptr b);
};