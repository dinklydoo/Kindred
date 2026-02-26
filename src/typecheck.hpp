#pragma once

#include "semerror.hpp"
#include "ast.hpp"
#include "types.hpp"
#include "visitor.hpp"
#include <unordered_map>
#include <stack>
#include <vector>

namespace tc {

using scope = std::unordered_map<std::string, type_ptr>;

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
    // if variable is already defined then return -1 else return 0
    int push_var(std::string label, type_ptr type){
        auto& t = stack.back();

        if (find_var(label)) return -1;

        t.emplace(label, type);
        return 0;
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
    private:
        std::stack<type_ptr> stack;
    public:
        void prop_type(type_ptr t){ stack.push(t); }
        type_ptr unprop_type(){ 
            auto t = stack.top();
            stack.pop(); 
            return t;
        }

        type_ptr top_type(){
            if (stack.empty()) return nullptr;
            return stack.top();
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

    // type propogator object
    TypePropogator typeprop;

    // error container object
    ErrorList errors;

    void typecheck(ModuleNode& node);

    /*
    Visitor definitions, double dispatched
    */
    void visit( VarDecl& node) override;
    void visit( FuncDecl& node) override;
    void visit( EnumDecl& node) override;
    void visit( StructDecl& node) override;
    void visit( UnaryNode& node) override;
    void visit( BinaryNode& node) override;
    void visit( CallNode& node) override;
    void visit( StructNode& node) override;
    void visit( AccessNode& node) override;
    void visit( NominalNode& node) override;
    void visit( CharLit& node) override;
    void visit( IntLit& node) override;
    void visit( FloatLit& node) override;
    void visit( BoolLit& node) override;
    void visit( ListPatternLit& node) override;
    void visit( StructPatternLit& node) override;
    void visit( EnumLit& node) override;
    void visit( DefaultLit& node) override;
    void visit( ElseLit& node) override;
    void visit( NilLit& node) override;
    void visit( EmptyLit& node) override;
    void visit( ReturnNode& node) override;
    void visit( CaseNode& node) override;
    void visit( CaseBranchNode& node) override;
    void visit( GuardNode& node) override;
    void visit( GuardBranchNode& node) override;
    void visit( ListNode& node) override;
    void visit( ProgramNode& node) override;
    void visit( ModuleNode& node) override;
    void visit( ReadNode& node) override;
    void visit( PrintNode& node) override;
    
    bool push_var_safe(std::string label, type_ptr type, Source& loc);
};

}