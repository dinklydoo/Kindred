#include "constant_fold.hpp"
#include "ast.hpp"

void ConstantFolder::constant_fold(ModuleNode& node){
    node.accept(*this);
}

void ConstantFolder::visit(ModuleNode& node){
    for (auto& d : node.decl) d->accept(*this);
}

void ConstantFolder::visit(FuncDecl& node){
    node.body->accept(*this);
}

void ConstantFolder::visit(ProgramNode& node){
    for (auto& d : node.decl) d->accept(*this);
    node.body->accept(*this);
}