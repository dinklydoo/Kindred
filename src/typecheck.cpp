#include "typecheck.hpp"
#include <map>


// Binding strengths for castable numeric values
int binding_strength(type_ptr tp){
    Type::Kind kind = tp->kind;
    switch (kind) {
        case Type::Kind::Char : return 1;
        case Type::Kind::Int : return 2;
        case Type::Kind::Long : return 3;
        case Type::Kind::Float : return 4;
        case Type::Kind::Double : return 5;
        default : return -1;
    }
}

// Casting value types to the strongest binding
// If a cast is impossible returns nullptr
type_ptr TypeChecker::cast_type(type_ptr a, type_ptr b){
    int bind_a = binding_strength(a);
    int bind_b = binding_strength(b);
    if (bind_a < 0 || bind_b < 0) return nullptr;

    if (bind_a > bind_b) return a;
    return b;
}


void TypeChecker::visit( ModuleNode& node){
    definitions.push_scope();
    for (auto& d : node.decl){
        d->accept(*this);
    }
    definitions.pop_scope();
}

void TypeChecker::visit( FuncDecl& node ){
    std::vector<type_ptr> param_types;
    for (auto& param : node.params){
        param_types.push_back(param.type);
    }
    type_ptr ftype = type_s.func_type(param_types, node.ret);

    // generate function type in global scope
    definitions.push_var(node.name, ftype);

    typeprop.prop_type(node.ret); // cache return type
    definitions.push_scope(); // enter function decl scope from global scope

    for (auto& param : node.params){
        definitions.push_var(param.name, param.type);
    }
    node.body->accept(*this);
    
    // clean up scope
    typeprop.unprop_type();
    definitions.pop_scope();
}

void TypeChecker::visit( EnumDecl& node){
    type_ptr etype = type_s.declare_enum(node.name);
    for (auto& ev : node.evar){
        definitions.push_var(ev, etype);
    }
}

void TypeChecker::visit( StructDecl& node){
    // define structure type only
    type_ptr stype = type_s.declare_struct(node.name, node.fields);
}

void TypeChecker::visit( VarDecl& node){
    definitions.push_var(node.name, node.type);
    typeprop.prop_type(node.type);

    node.r_val->accept(*this);

    typeprop.unprop_type();
}

void TypeChecker::visit( ProgramNode& node){
    for (auto& d : node.decl){
        d->accept(*this);
    }
    node.body->accept(*this);
}

void TypeChecker::visit( ReadNode& node){
    definitions.push_var(node.name, node.type);
    if (node.type ){

    } // NEED TO CHECK FOR READABLE TYPE
    typeprop.prop_type(node.type);

    typeprop.unprop_type();
}

void TypeChecker::visit( PrintNode& node){
    type_ptr print_type;
    typeprop.set_unbound();
    node.msg->accept(*this);
    typeprop.set_bound();
    
    print_type = node.msg->resolved_type;
    // need to check for printable type
}

void TypeChecker::visit( CaseNode& node){
    typeprop.set_unbound();
    node.target->accept(*this); // resolve pattern type
    typeprop.set_bound();

    typeprop.prop_type(node.target->resolved_type);
    for (auto& b : node.patterns){
        b->accept(*this);
    }
    typeprop.unprop_type();
}

void TypeChecker::visit( GuardNode& node){
    typeprop.prop_type(type_s.bool_type());
    for (auto& b : node.branches){
        b->accept(*this);
    }
    typeprop.unprop_type();
}

void TypeChecker::visit(CaseBranchNode& node){
    definitions.push_scope();
    node.pattern->accept(*this);

    // pop pattern type to reveal return type for return expr
    type_ptr pat_type = typeprop.unprop_type();
    node.body->accept(*this);
    typeprop.prop_type(pat_type);

    definitions.pop_scope();
}

void TypeChecker::visit(GuardBranchNode& node){
    definitions.push_scope();
    node.match->accept(*this);

    typeprop.unprop_type();
    node.body->accept(*this);
    typeprop.prop_type(type_s.bool_type());

    definitions.pop_scope();
}

void TypeChecker::visit(UnaryNode& node){
    if (typeprop.is_bound()){ // expected type
        



    }
    else { // type inference
        


    }
}