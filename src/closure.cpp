#include "closure.hpp"
#include "ast.hpp"

using namespace cs;

void ClosureGen::generate( ModuleNode& node ){
    node.accept(*this);
}

void ClosureGen::visit( ModuleNode& node ){
    for (auto& d : node.decl) d->accept(*this);
}

void ClosureGen::visit( FuncDecl& node ){
    node.name = func_rn.declare_func(node.name);
    var_map.declare_var(node.name); // if nested
    func_cap.enter_function();
    var_map.enter_function(node.name);
    for (auto& p : node.params){
        var_map.declare_var(p.name);
    }
    node.body->accept(*this);

    // set captured variables
    node.captures = func_cap.captures.back();

    func_cap.exit_function();
    var_map.exit_function();
}

void ClosureGen::visit( ProgramNode& node ){
    for (auto& d : node.decl) d->accept(*this);
    node.body->accept(*this);
}

void ClosureGen::visit( VarDecl& node ){
    var_map.declare_var(node.name);
    node.r_val->accept(*this);
}

void ClosureGen::visit( NominalNode& node ){
    if (node.kind == NominalKind::VAR_REF){
        if (!var_map.func_owns(node.label)){
            func_cap.capture_var(node.label, node.resolved_type);
        }
    }
}

void ClosureGen::visit( UnaryNode& node ){
    node.exp->accept(*this);
}

void ClosureGen::visit( BinaryNode& node ){
    node.l_exp->accept(*this);
    node.r_exp->accept(*this);
}

void ClosureGen::visit( AccessNode& node ){
    node.struct_expr->accept(*this);
}

void ClosureGen::visit( ListPatternLit& node ){
    for (auto p : node.patterns) var_map.declare_var(p);
}

void ClosureGen::visit( StructPatternLit& node ){
    for (auto p : node.patterns) var_map.declare_var(p);
}

void ClosureGen::visit( ReturnNode& node ){
    node.rexp->accept(*this);
}

void ClosureGen::visit( CaseNode& node) {
    node.target->accept(*this);
    for (auto& c : node.patterns) c->accept(*this);
};

void ClosureGen::visit( CaseBranchNode& node ) {
    if (!node.reachable) return;
    var_map.push_scope();
    node.pattern->accept(*this);
    node.body->accept(*this);
    var_map.pop_scope();
}

void ClosureGen::visit( GuardNode& node ) {
    for (auto& b : node.branches) b->accept(*this);
}

void ClosureGen::visit( GuardBranchNode& node ) {
    if (!node.reachable) return;
    var_map.push_scope();
    node.match->accept(*this);
    node.body->accept(*this);
    var_map.pop_scope();
}

void ClosureGen::visit( ListNode& node ) {
    for (auto& e : node.elems) e->accept(*this);
}

void ClosureGen::visit( StructNode& node ) {
    for (auto& f : node.fields) f->accept(*this);
}

void ClosureGen::visit( CallNode& node ) {
    node.f_exp->accept(*this);
    for (auto& p : node.params) p->accept(*this);
}