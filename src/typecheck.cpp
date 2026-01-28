#include "typecheck.hpp"
#include "types.hpp"
#include <cstddef>
#include <memory>
#include <string>

bool is_arith_whole(Type::Kind kind){
    switch (kind) {
        case Type::Kind::Char :
        case Type::Kind::Int :
        case Type::Kind::Long : return true;
        default: return false;
    }
}

bool is_arith(Type::Kind kind){
    switch (kind) {
        case Type::Kind::Char :
        case Type::Kind::Int :
        case Type::Kind::Long :
        case Type::Kind::Float :
        case Type::Kind::Double : return true;
        default: return false;
    }
}

bool is_error(type_ptr type){
    return (type->kind == Type::Kind::ERROR);
}

/* ============================================================================================================================================================

                ERROR HANDLING LOGIC

 ============================================================================================================================================================ */

void TypeChecker::push_error(std::string msg, SemanticError::Kind kind, Source& loc){
    errors.push_back(SemanticError{kind, loc, msg});
}

std::string kind_to_string(Type::Kind kind){
    switch(kind){
        case Type::Kind::Enum : { return "enum"; }
        case Type::Kind::Struct : { return "struct"; }
        case Type::Kind::Func : { return "function"; }
        default : return "variable";
    }
}

std::string type_to_string(type_ptr type){
    switch (type->kind){
        case Type::Kind::Struct :
        case Type::Kind::Enum : {
            auto temp = std::static_pointer_cast<NominalType>(type);
            return temp->name;
        };
        case Type::Kind::Func : {
            auto temp = std::static_pointer_cast<FuncType>(type);
            std::string ftype = "(";
            for (type_ptr atype : temp->args){
                ftype += type_to_string(atype) + ',';
            }
            ftype += ")->" + type_to_string(temp->ret);
            return ftype;
        }
        case Type::Kind::List : {
            auto temp = std::static_pointer_cast<ListType>(type);
            std::string ltype = "[";
            ltype += type_to_string(temp->elem);
            ltype += ']';
            return ltype;
        }
        case Type::Kind::Bool : return "bool";
        case Type::Kind::Char : return "char";
        case Type::Kind::Int : return "int";
        case Type::Kind::Long : return "long";
        case Type::Kind::Float : return "float";
        case Type::Kind::Double : return "double";
        default : return "";
    }
}

void TypeChecker::redef_error(std::string label, Source& loc){
    type_ptr defined = definitions.find_var(label);
    std::string defined_type = kind_to_string(defined->kind);
    push_error(
        "Redefinition of " + label + " conflicts with prior " + defined_type + "definition",
        SemanticError::Kind::REDEF, loc
    );
}

void TypeChecker::type_error(std::string message, ExpNode& node){
    push_error(message, SemanticError::Kind::TYPE, node.location);
    node.resolved_type = type_s.error_type();
}

void TypeChecker::access_error(std::string message, ExpNode& node){
    push_error(message, SemanticError::Kind::ACCESS, node.location);
    node.resolved_type = type_s.error_type();
}

void TypeChecker::arg_error(std::string message, ExpNode& node){
    push_error(message, SemanticError::Kind::ARG, node.location);
    node.resolved_type = type_s.error_type();
}

void TypeChecker::undef_error(std::string message, ExpNode& node){
    push_error(message, SemanticError::Kind::UNDEF, node.location);
    node.resolved_type = type_s.error_type();
}

void TypeChecker::reference_error(std::string label, ExpNode& node){
    Type::Kind defined = definitions.find_var(label)->kind;
    std::string def_str = kind_to_string(defined);

    Type::Kind referenced = node.resolved_type->kind;
    std::string ref_str = kind_to_string(referenced);
    push_error(
        "Reference to '" + label + "' as '" + ref_str + "' conflicts with prior definition as '" + def_str + "'",
        SemanticError::Kind::REF, node.location
    );
    node.resolved_type = type_s.error_type();
}

/* ============================================================================================================================================================

                TYPE CASTING LOGIC

 ============================================================================================================================================================ */

// Binding strengths for castable numeric values
int binding_strength(type_ptr tp){
    Type::Kind kind = tp->kind;
    switch (kind) {
        case Type::Kind::GENERIC : return 0;
        case Type::Kind::Char : return 1;
        case Type::Kind::Int : return 2;
        case Type::Kind::Long : return 3;
        case Type::Kind::Float : return 4;
        case Type::Kind::Double : return 5;
        default : return -1;
    }
}


// Casts a type to the strongest binding if castable

// struct types by definition are only equivalent to each other
// list types can be cast if underlying values are castable
// enum types are never castable

// If a cast is impossible returns nullptr
type_ptr TypeChecker::cast_strongest(type_ptr a, type_ptr b){
    // recursively cast for list types
    if (a->kind == Type::Kind::List && b->kind == Type::Kind::List){
        auto al = std::static_pointer_cast<ListType>(a);
        auto bl = std::static_pointer_cast<ListType>(b);
        return 
            type_s.list_type(
                cast_strongest(al->elem, bl->elem)
            );
    }
    int bind_a = binding_strength(a);
    int bind_b = binding_strength(b);

    // generic types
    if (bind_a == 0) return b;
    if (bind_b == 0) return a;

    // non comparable types
    if (bind_a < 0 || bind_b < 0) return nullptr;
    if (bind_a > bind_b) return a;
    return b;
}

// Returns fixed type if type_ptr castable is castable to fixed type
// otherwise returns nullptr
type_ptr TypeChecker::cast_fixed(type_ptr fix, type_ptr castable){
    if (fix == cast_strongest(fix, castable)) return fix;
    return nullptr;
}

/* ============================================================================================================================================================

                VISITOR PATTERN VISIT DECLARATIONS

 ============================================================================================================================================================ */


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
    if (definitions.push_var(node.name, ftype) < 0){
        redef_error(node.name, node.location);
        return;
    }

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
    // error check definition name
    type_ptr etype = type_s.declare_enum(node.name);
    for (auto& ev : node.evar){
        if (definitions.push_var(ev, etype) < 0){
            redef_error(node.name, node.location);
        }
    }
}

void TypeChecker::visit( StructDecl& node){
    // define structure type only
    type_ptr stype = type_s.declare_struct(node.name, node.fields);
}

void TypeChecker::visit( VarDecl& node){
    if (definitions.push_var(node.name, node.type) < 0){
        redef_error(node.name, node.location);
    }
    node.r_val->accept(*this);
    if (is_error(node.r_val->resolved_type)) return;

    if (!cast_fixed(node.type, node.r_val->resolved_type)){
        type_error(
            "Variable " + node.name + " expects expression of type " + 
            type_to_string(node.type) + " but got expression of type " + 
            type_to_string(node.r_val->resolved_type) + " instead",*node.r_val
        );
    }
}

void TypeChecker::visit( ProgramNode& node){
    for (auto& d : node.decl){
        d->accept(*this);
    }
    node.body->accept(*this);
}

void TypeChecker::visit( ReturnNode& node){
    node.rexp->accept(*this);
    if (is_error(node.rexp->resolved_type)) return;

    type_ptr rtype = typeprop.top_type();
    if (!cast_fixed(rtype, node.rexp->resolved_type)){
        type_error(
            "Function return type expects return expression of type "
            +type_to_string(rtype)+" instead got "+
            type_to_string(node.rexp->resolved_type), node);
        return;
    }
}

void TypeChecker::visit( CaseNode& node){
    node.target->accept(*this); // resolve pattern type

    typeprop.prop_type(node.target->resolved_type);
    for (auto& b : node.patterns){
        b->accept(*this);
    }
    typeprop.unprop_type();
}


void TypeChecker::visit(CaseBranchNode& node){
    definitions.push_scope();
    type_ptr exp = typeprop.top_type();
    node.pattern->accept(*this);

    if (is_error(node.pattern->resolved_type)){ /*do nothing*/}

    else if (!cast_fixed(exp, node.pattern->resolved_type)){
        type_error("Pattern matching requires pattern to share a type with match value", *node.pattern);
    }
    else {
        // pop pattern type to reveal return type for return expr
        type_ptr pat_type = typeprop.unprop_type();
        node.body->accept(*this);
        typeprop.prop_type(pat_type);
    }
    definitions.pop_scope();
}

void TypeChecker::visit( GuardNode& node){
    for (auto& b : node.branches){
        b->accept(*this);
    }
}

void TypeChecker::visit(GuardBranchNode& node){
    definitions.push_scope();
    node.match->accept(*this);
    Type::Kind kind = node.match->resolved_type->kind;

    if (is_error(node.match->resolved_type)){ /*do nothing*/ }

    else if (kind != Type::Kind::Bool){
        type_error("Guard Expression branch must be a boolean value", *node.match);
    }
    else {
        node.body->accept(*this);
    }
    definitions.pop_scope();
}

void TypeChecker::visit(UnaryNode& node){
    node.exp->accept(*this);
    Type::Kind kind = 
        (node.resolved_type = node.exp->resolved_type)->kind;

    if (is_error(node.exp->resolved_type)) return;

    switch (node.op){
        case UnaryOp::BNOT : {
            if (kind != Type::Kind::Bool){
                type_error("Logical Negation Operator '!' requires a bool operand", node);
            }
            return;
        }
        case UnaryOp::LNEG : {
            if (!is_arith_whole(kind)){
                type_error("Bitwise Negation Operator '~' requires a char, int, long operand", node);
            }
            return;
        }
        case UnaryOp::MINUS : {
            if (!is_arith(kind)){
                type_error("Unary Minus Operator '-' requires numeric operand", node);
            }
            return;
        }
    }
}

void TypeChecker::visit(BinaryNode& node){
    node.l_exp->accept(*this);
    node.r_exp->accept(*this);
    Type::Kind l_kind = node.l_exp->resolved_type->kind;
    Type::Kind r_kind = node.r_exp->resolved_type->kind;
    if (
        is_error(node.l_exp->resolved_type) || 
        is_error(node.r_exp->resolved_type)
    ){
        node.resolved_type = type_s.error_type();
        return;
    }

    std::string op_token = "";
    switch (node.op){
        case BinaryOp::ADD : if (op_token.empty()) op_token = '+';
        case BinaryOp::SUB : if (op_token.empty()) op_token = '-';
        case BinaryOp::MUL : if (op_token.empty()) op_token = '*';
        case BinaryOp::POW : if (op_token.empty()) op_token = "**";
        case BinaryOp::FLR : if (op_token.empty()) op_token = "//";
        case BinaryOp::DIV : {
            if (op_token.empty()) op_token = '/';
            if (!is_arith(l_kind) || !is_arith(r_kind)){
                type_error(std::string("Arithmetic operator '") + op_token + "' requires numeric operands", node);
            }
            else node.resolved_type = cast_strongest(node.l_exp->resolved_type, node.r_exp->resolved_type);
            return;
        }
        case BinaryOp::LAND : if (op_token.empty()) op_token = '&';
        case BinaryOp::LOR : if (op_token.empty()) op_token = '|';
        case BinaryOp::LXOR : if (op_token.empty()) op_token = '^';
        case BinaryOp::LSR : if (op_token.empty()) op_token = ">>";
        case BinaryOp::LSL :  if (op_token.empty()) op_token = "<<";
        case BinaryOp::MOD : {
            if (op_token.empty()) op_token = '%';
            if (!is_arith_whole(l_kind) || !is_arith_whole(r_kind)){
                type_error(std::string("Arithmetic operator '") + op_token + "' requires whole numeric operands", node);
            }
            else node.resolved_type = cast_strongest(node.l_exp->resolved_type, node.r_exp->resolved_type);
            return;
        }
        case BinaryOp::CGT : if (op_token.empty()) op_token = '>';
        case BinaryOp::CLT : if (op_token.empty()) op_token = '<';
        case BinaryOp::CGEQ : if (op_token.empty()) op_token = ">=";
        case BinaryOp::CLEQ : {
            if (op_token.empty()) op_token = "<=";
            if (!is_arith_whole(l_kind) || !is_arith_whole(r_kind)){
                type_error(std::string("Comparative operator '") + op_token + "' requires numeric operands", node);
            }
            else node.resolved_type = type_s.bool_type();
            return;
        }
        case BinaryOp::CEQ : if (op_token.empty()) op_token = "==";
        case BinaryOp::CNEQ : {
            if (op_token.empty()) op_token = "!=";
            type_ptr casted;
            if (!(casted = cast_strongest(node.l_exp->resolved_type, node.r_exp->resolved_type))){
                type_error(std::string("Equality operator '") + op_token + "' requires operands of same type (or castable)", node);
            }
            else node.resolved_type = type_s.bool_type();
            return;
        }
        case BinaryOp::BAND : if (op_token.empty()) op_token = "&&";
        case BinaryOp::BOR : {
            if (op_token.empty()) op_token = "||";
            if (l_kind != Type::Kind::Bool || r_kind != l_kind){
                type_error(std::string("Boolean operator '") + op_token + "' requires bool operands", node);
            }
            else node.resolved_type = type_s.bool_type();
            return;
        }
        case BinaryOp::CONCAT : {
            if (l_kind != Type::Kind::List && r_kind != Type::Kind::List){
                type_error("List concatenation requires at least one list operand", node);
            }
            else {
                if (node.l_exp->resolved_type == node.r_exp->resolved_type){
                    node.resolved_type = node.l_exp->resolved_type;
                    return;
                }
                type_ptr internal = nullptr;
                type_ptr casted = nullptr;
                if (l_kind == Type::Kind::List){
                    internal = 
                        std::static_pointer_cast<ListType>(node.l_exp->resolved_type)->elem;
                    if (!(casted = cast_strongest(internal, node.r_exp->resolved_type))){
                        type_error("List concatenation requires operands of the same element type", node);
                        return;
                    }
                    node.resolved_type = node.l_exp->resolved_type;
                }
                if (r_kind == Type::Kind::List){
                    internal =
                        std::static_pointer_cast<ListType>(node.r_exp->resolved_type)->elem;
                    if (!(casted = cast_strongest(internal, node.l_exp->resolved_type))){
                        type_error("List concatenation requires operands of the same element type", node);
                        return;
                    }
                    node.resolved_type = node.r_exp->resolved_type;
                }
            }
            return;
        }
        case BinaryOp::INDEX : {
            if (l_kind != Type::Kind::List){
                type_error("List indexing requires left operand to be a list", node);
                return;
            }          
            if (!is_arith_whole(r_kind)){
                type_error("List concatenation requires numeric right operand (index)", node);
                return;
            }
            auto internal = 
                std::static_pointer_cast<ListType>(node.l_exp->resolved_type)->elem;
            node.resolved_type = internal;
            return;
        }
    }
}

void TypeChecker::visit(ListNode& node){
    // start as generic
    type_ptr type = type_s.list_type(type_s.generic_type());
    for (int i = 0; i < node.elems.size(); i++){
        auto& elem = node.elems[i];
        elem->accept(*this);
        if (is_error(elem->resolved_type)){
            node.resolved_type = type_s.error_type();
            return;
        }
        if (!(type = cast_strongest(type, elem->resolved_type))){
            type_error(
                "List constructor element has conflicting type\
                 with container at index " + std::to_string(i),node
            );
            return;
        }
    }
    node.resolved_type = type;
}

void TypeChecker::visit(StructNode& node){
    type_ptr defn = definitions.find_var(node.name);
    if (!defn){
        undef_error("Reference to struct " + node.name + " is undefined", node);
        return;
    }
    if (defn->kind != Type::Kind::Struct){
        reference_error(node.name, node);
        return;
    }
    auto struct_defn = std::static_pointer_cast<NominalType>(defn);

    if (node.fields.size() != struct_defn->fields.size()){
        access_error(
            "struct '" + node.name + "' expects "+ 
            std::to_string(struct_defn->fields.size())+ 
            " fields, instead got "+
            std::to_string(node.fields.size()), node
        );
        return;
    }
    for (int i = 0; i < node.fields.size(); i++){
        auto& fval = node.fields[i];
        fval->accept(*this);

        // error propogation
        if (is_error(fval->resolved_type)){
            node.resolved_type = type_s.error_type();
            return;
        }

        auto correspondent = struct_defn->fields[i];
        if (!cast_fixed(correspondent.type, fval->resolved_type)){
            type_error(
                "struct "+node.name+" with field "+correspondent.name
                +"expects type "+type_to_string(correspondent.type)+" but got "
                + type_to_string(fval->resolved_type), node
            );
            return;
        }
    }
    node.resolved_type = defn;
}

void TypeChecker::visit(CallNode& node){
    type_ptr defn = definitions.find_var(node.label);
    if (!defn){
        undef_error("Reference to function " + node.label + " is undefined", node);
        return;
    }
    if (defn->kind != Type::Kind::Func){
        reference_error(node.label, node);
        return;
    }
    auto func_defn = std::static_pointer_cast<FuncType>(defn);
    if (node.params.size() != func_defn->args.size()){
        arg_error(
            "function "+node.label+" expects "+
            std::to_string(func_defn->args.size())+" arguments but got "+
            std::to_string(node.params.size())+" instead", node
        );
        return;
    }
    for (int i = 0; i < node.params.size(); i++){
        auto& arg = node.params[i];
        arg->accept(*this);

        // error propogation
        if (is_error(arg->resolved_type)){
            node.resolved_type = type_s.error_type();
            return;
        }

        auto expected = func_defn->args[i];
        if (!cast_fixed(expected, arg->resolved_type)){
            type_error(
                "function "+node.label+" expects an argument of type "
                +type_to_string(expected)+" in position "+std::to_string(i+1)
                +"but got an argument of "+type_to_string(arg->resolved_type)+" instead", node
            );
            return;
        }
    }
    node.resolved_type = func_defn->ret;
}

void TypeChecker::visit(AccessNode& node){
    node.struct_expr->accept(*this);
    if (is_error(node.struct_expr->resolved_type)){
        node.resolved_type = type_s.error_type();
        return;
    }
    type_ptr stype = node.struct_expr->resolved_type;
    if (stype->kind != Type::Kind::Struct){
        type_error(
            "struct access requires l-val to be a struct type instead got "
            +type_to_string(stype), node
        );
        return;
    }
    auto sdefn = std::static_pointer_cast<NominalType>(stype);
    type_ptr ftype = nullptr;
    for (auto field : sdefn->fields){
        if (field.name == node.field){
            ftype = field.type; break;
        }
    }
    if (!ftype){
        access_error("struct "+sdefn->name+" has no field labelled "+node.field, node);
        return;
    }
    node.resolved_type = ftype;
};

void TypeChecker::visit(NominalNode& node){
    type_ptr defn = definitions.find_var(node.label);
    if (!defn){
        undef_error("undefined reference to nominal value (variable/enum) "+node.label, node);
        return;
    }
    node.resolved_type = defn;
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
    node.msg->accept(*this);
    if (is_error(node.msg->resolved_type)) return;
    print_type = node.msg->resolved_type;
}

void TypeChecker::visit(EnumLit& node){
    type_ptr defn = definitions.find_var(node.elem);
    if (!defn){
        undef_error("undefined reference to enumerator "+node.elem, node);
        return;
    }
    node.resolved_type = defn;
}

void TypeChecker::visit(DefaultLit& node){
    node.resolved_type = type_s.generic_type();
}

void TypeChecker::visit(NilLit& node){
    node.resolved_type = type_s.generic_type();
}

void TypeChecker::visit(ListPatternLit& node){
    int n = node.patterns.size();
    type_ptr ptype = typeprop.top_type();
    if (ptype->kind != Type::Kind::List){
        // force error to be handled by branch
        node.resolved_type = type_s.list_type(type_s.generic_type());
        return;
    }
    auto ltype = std::static_pointer_cast<ListType>(ptype);
    for (int i = 0; i < n - 1; i++){
        definitions.push_var(node.patterns[i], ltype->elem);
    }
    definitions.push_var(node.patterns[n-1], ltype);
    node.resolved_type = ptype;
}

void TypeChecker::visit(ListLit& node){
    type_ptr expected = type_s.generic_type();
    for (int i = 0; i < node.elems.size(); i++){
        node.elems[i]->accept(*this);
        type_ptr temp = cast_strongest(expected, node.elems[i]->resolved_type);
        if (!temp){
            type_error(
                "List type mismatch, list literal expects type "+type_to_string(expected)+
                " up to index "+std::to_string(i)+"but got type "+
                type_to_string(node.elems[i]->resolved_type)+"instead",node
            );
        }
        else expected = temp;
    }
    node.resolved_type = type_s.list_type(expected);
}

void TypeChecker::visit(CharLit& node){
    node.resolved_type = type_s.char_type();    
}

void TypeChecker::visit(BoolLit& node){
    node.resolved_type = type_s.bool_type();
}

// float values will default to 32b float then in ir gen we can cast
void TypeChecker::visit(FloatLit& node){
    node.resolved_type = type_s.float_type();
}

// whole values can be semantically cast
void TypeChecker::visit(IntLit& node){
    if (node.value > INT_MAX || node.value < INT_MIN)
        node.resolved_type = type_s.long_type();
    else node.resolved_type = type_s.int_type();
}