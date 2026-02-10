#include "ir_lower.hpp"
#include "ast.hpp"
#include "types.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

// TODO : FIX BLOCK LABELS IN BRANCHING EXPRESSIONS AND SHORT CIRCUIT

using namespace ir;

DataType type_to_dtype(Type::Kind kind){
    switch (kind){
        case (Type::Kind::List) :
        case (Type::Kind::Struct) : return DataType::PTR;
        case (Type::Kind::Bool) : return DataType::BOOL;
        case (Type::Kind::Char) : return DataType::I8;
        case (Type::Kind::Enum) : 
        case (Type::Kind::Int) : return DataType::I32;
        case (Type::Kind::Long) : return DataType::I64;
        case (Type::Kind::Float) : return DataType::F32;
        case (Type::Kind::Double) : return DataType::F64;
        default : return DataType::EMPTY;
    }
}

int type_to_size(Type::Kind kind){
    switch (kind){
        case (Type::Kind::Bool) :
        case (Type::Kind::Char) : return 1;
        case (Type::Kind::Float) :
        case (Type::Kind::Enum) : // default enum to uint conversion
        case (Type::Kind::Int) : return 4;
        case (Type::Kind::Double) :
        case (Type::Kind::Struct) :
        case (Type::Kind::List) :
        case (Type::Kind::Long) : return 8;
        default : return -1; // no hit
    }
}

void IR_Lowerer::op_equals(Operand ptr1, Operand ptr2, type_ptr type){
    ConsFunctionIR& cons = builder.top_constructor();
    Operand _t0 = cons.get_register();
    switch (type->kind){
        case (Type::Kind::GENERIC) : {
            cons.push_operand(Operand::imm(1));
            return;
        }
        case (Type::Kind::Struct) : {
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, ptr1});
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, ptr2});
            cons.push_instruction({Operation::CALL, DataType::PTR, _t0, {}, {}, "struct_equals"});
            break;
        }
        case (Type::Kind::List) : {
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, ptr1});
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, ptr2});
            cons.push_instruction({Operation::CALL, DataType::PTR, _t0, {}, {}, "list_equals"});    
            break;
        }
        default : cons.push_instruction({Operation::CEQ, type_to_dtype(type->kind), _t0, ptr1, ptr2});
    }
    cons.push_operand(_t0);
}

void IR_Lowerer::cast_operand(Operand target, type_ptr fix, type_ptr cast){
    ConsFunctionIR& cons = builder.top_constructor();
    if (fix->kind == cast->kind){
        cons.push_operand(target); return;
    }
    Operand _casted = cons.get_register();
    switch (fix->kind){
        case (Type::Kind::Int) : 
            cons.push_instruction({Operation::CST_I32, type_to_dtype(cast->kind), _casted, target}); break;
        case (Type::Kind::Long) : 
            cons.push_instruction({Operation::CST_I64, type_to_dtype(cast->kind), _casted, target}); break;
        case (Type::Kind::Float) : 
            cons.push_instruction({Operation::CST_F32, type_to_dtype(cast->kind), _casted, target}); break;
        case (Type::Kind::Double) : 
            cons.push_instruction({Operation::CST_F64, type_to_dtype(cast->kind), _casted, target}); break;
        default : cons.push_operand(target); return;
    }
    cons.push_operand(_casted);
}

void IR_Lowerer::short_and( BinaryNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

    Operand _true = Operand::imm(0);
    Operand _false = Operand::imm(0);
    Operand _t = cons.get_register();

    std::string L_false = builder.get_scratch_label();
    std::string L_end = builder.get_scratch_label();

    node.l_exp->accept(*this);
    Operand _lexp = cons.pop_operand();
    Operand _not_lexp = cons.get_register();
    cons.push_instruction({Operation::NOT, DataType::BOOL, _not_lexp, _lexp});
    cons.push_instruction({Operation::JMP_IF, DataType::BOOL, {}, _not_lexp, {}, L_false});

    node.r_exp->accept(*this);
    Operand _rexp = cons.pop_operand();
    Operand _not_rexp = cons.get_register();
    cons.push_instruction({Operation::NOT, DataType::BOOL, _not_rexp, _rexp});
    cons.push_instruction({Operation::JMP_IF, DataType::BOOL, {}, _not_rexp, {}, L_false});
    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, _true});
    cons.push_instruction({Operation::JMP, DataType::EMPTY, {}, {}, {}, L_end});

    gen_block(L_false); // L_false

    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, _false});

    gen_block(L_end); // L_end

    cons.push_operand(_t);
}

void IR_Lowerer::short_or( BinaryNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

    Operand _true = Operand::imm(0);
    Operand _false = Operand::imm(0);
    Operand _t = cons.get_register();

    std::string L_true = builder.get_scratch_label();
    std::string L_end = builder.get_scratch_label();

    node.l_exp->accept(*this);
    Operand _lexp = cons.pop_operand();
    cons.push_instruction({Operation::JMP_IF, DataType::BOOL, {}, _lexp, {}, L_true});

    node.r_exp->accept(*this);
    Operand _rexp = cons.pop_operand();
    cons.push_instruction({Operation::JMP_IF, DataType::BOOL, {}, _rexp, {}, L_true});
    
    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, _false});
    cons.push_instruction({Operation::JMP, DataType::EMPTY, {}, {}, {}, L_end});

    gen_block(L_true) ; // L_true

    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, _true});
    
    gen_block(L_end); // L_end

    cons.push_operand(_t);
}

void IR_Lowerer::struct_pattern_vars( LiteralNode& node){
    ConsFunctionIR& cons = builder.top_constructor();
    Operand _target = cons.pop_operand();
    StructPatternLit& snode = static_cast<StructPatternLit&>(node);

    nominal_ptr sptr = std::static_pointer_cast<NominalType>(node.resolved_type);
    Operand _t = cons.get_register();
    auto& fields = sptr->get_fields();
    for (int i = 0; i < fields.size(); i++){
        if (snode.patterns[i].empty()) continue;

        unsigned int id = identifier.get_ident(snode.patterns[i]);

        cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _target});
        cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(i)});
        cons.push_instruction({Operation::CALL, DataType::PTR, _t, {}, {}, "access_field"});
        cons.push_instruction({Operation::LOAD, type_to_dtype(fields[i].type->kind), Operand::var(id), _t});
    }
}

void IR_Lowerer::list_pattern_vars( LiteralNode& node){
    ConsFunctionIR& cons = builder.top_constructor();
    Operand _target = cons.pop_operand();
    ListPatternLit& lnode = static_cast<ListPatternLit&>(node);

    auto lptr = std::static_pointer_cast<ListType>(node.resolved_type);
    Operand _t = cons.get_register();
    type_ptr etype = lptr->elem;

    for (int i = 0; i < lnode.patterns.size()-1; i++){
        unsigned int id = identifier.get_ident(lnode.patterns[i]);

        cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _target});
        cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(i)});
        cons.push_instruction({Operation::CALL, DataType::PTR, _t, {}, {}, "access_index"});
        cons.push_instruction({Operation::LOAD, type_to_dtype(lptr->elem->kind), Operand::var(id), _t});
    }
}

void IR_Lowerer::increase_ref( Operand ptr, type_ptr type){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_instruction({Operation::PARAM, DataType::PTR, {}, ptr});
    if (type->kind == Type::Kind::Struct)
        cons.push_instruction({Operation::CALL, DataType::EMPTY, {}, {}, {}, "incr_struct"});
    else
        cons.push_instruction({Operation::CALL, DataType::EMPTY, {}, {}, {}, "incr_list"});
}

void IR_Lowerer::generate_node( Operand elem, type_ptr ltype, type_ptr type){
    ConsFunctionIR& cons = builder.top_constructor();
    
    if (ltype->kind == Type::Kind::Struct || ltype->kind == Type::Kind::List)
        increase_ref(elem, type);

    Operand _cast = cons.get_register();
    cast_operand(elem, ltype, type);
    _cast = cons.pop_operand();

    Operand _ptr = cons.get_register();
    if (type->kind == Type::Kind::List) cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(1)});
    else if (type->kind == Type::Kind::Struct) cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(2)});
    else cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(0)});

    cons.push_instruction({Operation::PARAM, DataType::I64, {}, Operand::imm(type_to_size(ltype->kind))});
    cons.push_instruction({Operation::PARAM, DataType::PTR, {}, Operand::imm(0)});
    cons.push_instruction({Operation::CALL, DataType::PTR, _ptr, {}, {}, "cons"});

    Operand _elem = cons.get_register();
    cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _ptr});
    cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(0)});
    cons.push_instruction({Operation::CALL, DataType::PTR, _elem, {}, {}, "index_list"});

    cons.push_instruction({Operation::STORE, type_to_dtype(ltype->kind), _elem, _cast});
    cons.push_operand(_ptr);
}

/* ============================================================================================================================================================

                INTERFACE

 ============================================================================================================================================================ */

void IR_Lowerer::lower(ModuleNode& node){
    generate_struct_file();
    node.accept(*this);
    close_struct_file();
}

void IR_Lowerer::generate_struct_file(){
    std::ofstream classfile("./sys_lib/struct_gen.c", std::ios::trunc);
    // set include paths
    classfile << "#include \"mem.h\"\n#include \"structs.h\"\n\n";
    return;
}

void IR_Lowerer::close_struct_file(){
    std::ofstream classfile("./sys_lib/struct_gen.c", std::ios::app);
    classfile << "static struct_layout STRUCT_DATA[] {\n";
    for (int i = 0; i < structInfo.struct_count(); i++){
        classfile << "\tSTRUCT_"<<i+1<<"_LAYOUT,\n";
    }
    classfile << "};\n";
}

/* ============================================================================================================================================================

                VISITOR PATTERN VISIT DECLARATIONS

 ============================================================================================================================================================ */

void IR_Lowerer::visit( ModuleNode& node){
    identifier.push_scope();
    for (auto& d : node.decl){
        d->accept(*this);
    }
    identifier.pop_scope();
}

void IR_Lowerer::visit( StructDecl& node){
    int alignment = 0;
    structInfo.add_struct(node.name, node.fields);

    std::vector<Field>& fields = node.fields;
    for (Field& f : fields){
        alignment = std::max(alignment, type_to_size(f.type->kind));
    }
    int offset = 0;
    int payload_size;
    std::vector<std::vector<std::string>> layout;
    for (Field& f : fields){
        int size = type_to_size(f.type->kind);
        if (offset % size) offset += size - (offset % size);

        payload_size = size + offset;
        
        std::string type;
        switch (f.type->kind){
            case (Type::Kind::Struct) : type = "STRUCT"; break;
            case (Type::Kind::List) : type = "LIST"; break;
            default : type = "LITERAL";
        }
        layout.push_back({type, std::to_string(offset), std::to_string(size)});
        
        offset += size;
    }
    if (payload_size % alignment) payload_size += alignment - (payload_size % alignment);

    int struct_no = structInfo.struct_count();

    std::ofstream classfile("./sys_lib/struct_gen.c", std::ios::app);
    classfile << "static struct_layout STRUCT_" << struct_no << "_LAYOUT = {\n"
    << "\t.payload_size = "<<payload_size<<",\n"
    <<"\t.field_count = "<<fields.size()<<",\n"
    <<"\t.fields = {\n";
    for (auto& p : layout){
        classfile << "\t\t{.type="<<p[0]<<", .offset="<<p[1]<<", .size="<<p[2]<<"},\n";
    }
    classfile << "\t}\n};\n";
}

void IR_Lowerer::visit( EnumDecl& node ){
    structInfo.add_enum(node.name, node.evar);
}

void IR_Lowerer::visit( FuncDecl& node){
    identifier.push_scope();
    builder.push_function();
    node.body->accept(*this);
    FunctionIR ir = builder.top_function();
    IRprogram.push_back(ir);
    builder.pop_function();
    identifier.pop_scope();
}

void IR_Lowerer::visit( ProgramNode& node){
    for (auto& d : node.decl){
        d->accept(*this);
    }
    node.body->accept(*this);
}

void IR_Lowerer::visit( CaseNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    identifier.push_scope();

    node.target->accept(*this);
    Operand _target = cons.pop_operand();
    std::string case_label = builder.get_case_label(); 
    int i = 0;
    std::stack<std::string> label_s;
    int branches = node.patterns.size();
    for (auto& p : node.patterns){
        if (!p->reachable) continue;

        std::string block_label = case_label+std::to_string(i++);
        label_s.push(block_label);
        if (p->pattern_type){
            cons.push_operand(_target); // push target again let pattern handle
            p->pattern->accept(*this);
        }
        else {
            p->pattern->accept(*this);
            Operand _cmp = cons.pop_operand(); // pattern literal in register top
            type_ptr type = p->pattern->resolved_type;
            IR_Lowerer::op_equals(_target, _cmp, type); // pushes result register on op stack
        }
        
        Operand _eq = cons.pop_operand();
        // jump if equals - else fallthrough
        cons.push_instruction({Operation::JMP_IF, DataType::BOOL, {}, _eq, {}, block_label});
    }
    while (!label_s.empty()){
        cons.label_stack.push(label_s.top());
        label_s.pop();
    }
    for (auto& p : node.patterns){
        if (p->pattern_type) cons.push_operand(_target);
        p->accept(*this);
    }

    identifier.push_scope();
}

void IR_Lowerer::visit(CaseBranchNode& node){
    if (!node.reachable) return;
    ConsFunctionIR& cons = builder.top_constructor();

    identifier.push_scope();
    std::string lab = cons.pop_label();
    gen_block(lab); // PATTERN MATCH JMP LABEL
    if (node.pattern_type){ // generate variable names
        if (node.resolved_type->kind == Type::Kind::Struct) struct_pattern_vars(*node.pattern);
        if (node.resolved_type->kind == Type::Kind::List) list_pattern_vars(*node.pattern);
    }
    node.body->accept(*this);
    identifier.pop_scope();
}

void IR_Lowerer::visit(GuardNode& node){
    ConsFunctionIR& cons = builder.top_constructor();
    std::string case_label = builder.get_case_label();
    int i = 0;
    std::stack<std::string> label_s;
    for (auto& b : node.branches){
        if (!b->reachable) continue;

        std::string block_label = case_label+std::to_string(i++);
        label_s.push(block_label);
        b->match->accept(*this);
        Operand _cond = cons.pop_operand();
        cons.push_instruction({Operation::JMP_IF, DataType::BOOL, {}, _cond, {}, block_label});
    }
    while (!label_s.empty()){
        cons.label_stack.push(label_s.top());
        label_s.pop();
    }
    for (auto& b : node.branches) b->accept(*this);
}

void IR_Lowerer::visit(GuardBranchNode& node){
    if (!node.reachable) return;
    ConsFunctionIR& cons = builder.top_constructor();

    identifier.push_scope();
    std::string lab = cons.pop_label();
    gen_block(lab); // CASE MATCH JMP LABEL

    node.body->accept(*this);
    identifier.pop_scope();
}

void IR_Lowerer::visit( DefaultLit& node ){ 
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::imm(1)); // true 
}

void IR_Lowerer::visit( ElseLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::imm(1)); // true
}

void IR_Lowerer::visit(VarDecl& node){
    ConsFunctionIR& cons = builder.top_constructor();
    unsigned int id = identifier.get_ident(node.name);
    node.r_val->accept(*this);
    Operand _rval = cons.pop_operand(); // expression register

    cast_operand(_rval, node.type, node.r_val->resolved_type);
    Operand _var = Operand::var(id);
    cons.push_instruction({Operation::MOV, type_to_dtype(node.type->kind), _var, _rval});
}

void IR_Lowerer::visit( UnaryNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    Operand _t = cons.get_register();
    node.exp->accept(*this);
    Operand _exp = cons.pop_operand();
    switch (node.op) {
        case (UnaryOp::BNOT):
            cons.push_instruction({Operation::NOT, DataType::BOOL, _t, _exp}); 
            break;
        case (UnaryOp::LNEG):
            cons.push_instruction({Operation::NEG, type_to_dtype(node.resolved_type->kind), _t, _exp});
            break;
        case (UnaryOp::MINUS):{
            Operand _r0 = Operand::imm(0);
            cons.push_instruction({Operation::SUB, type_to_dtype(node.resolved_type->kind), _t, _r0, _exp});
        }
    }
    cons.push_operand(_t);
}

void IR_Lowerer::visit( BinaryNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    if (node.op == BinaryOp::BAND){ short_and(node); return; }
    if (node.op == BinaryOp::BOR){ short_or(node); return; }

    node.l_exp->accept(*this);
    Operand _tl = cons.pop_operand();
    node.r_exp->accept(*this);
    Operand _tr = cons.pop_operand();
    
    cast_operand(_tl, node.resolved_type, node.l_exp->resolved_type);
    Operand _lexp = cons.pop_operand();
    cast_operand(_tr, node.resolved_type, node.l_exp->resolved_type);
    Operand _rexp = cons.pop_operand();

    Operand _t = cons.get_register();
    DataType dtype = type_to_dtype(node.resolved_type->kind);
    switch (node.op){
        case (BinaryOp::ADD):
            cons.push_instruction({Operation::ADD, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::SUB):
            cons.push_instruction({Operation::SUB, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::MUL):
            cons.push_instruction({Operation::MUL, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::DIV):
            cons.push_instruction({Operation::DIV, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::MOD):
            cons.push_instruction({Operation::MOD, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::POW):
            cons.push_instruction({Operation::POW, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::FLR):
            cons.push_instruction({Operation::FLR, dtype, _t, _lexp, _rexp});break;    
        case (BinaryOp::LAND):
            cons.push_instruction({Operation::AND, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::LOR):
            cons.push_instruction({Operation::OR, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::LXOR):
            cons.push_instruction({Operation::XOR, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::LSL):
            cons.push_instruction({Operation::LSL, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::LSR):
            cons.push_instruction({Operation::LSR, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::CGT):
            cons.push_instruction({Operation::CGT, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::CLT):
            cons.push_instruction({Operation::CLT, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::CGEQ): 
            cons.push_instruction({Operation::CGEQ, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::CLEQ):
            cons.push_instruction({Operation::CLEQ, dtype, _t, _lexp, _rexp});break;
        case (BinaryOp::CEQ): op_equals(_lexp, _rexp, node.resolved_type); return;
        case (BinaryOp::CNEQ): {
            op_equals(_lexp, _rexp, node.resolved_type);
            Operand _eq = cons.pop_operand();
            cons.push_instruction({Operation::NOT, DataType::BOOL, _t, _eq});
            break;
        }
        case (BinaryOp::CONCAT): {
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _lexp});
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _rexp});
            cons.push_instruction({Operation::CALL, DataType::PTR, _t, {}, {}, "concat_list"});
            break;
        }
        case (BinaryOp::PREPEND): {
            auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
            generate_node(_lexp, ltype->elem, node.l_exp->resolved_type);
            _lexp = cons.pop_operand();

            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _lexp});
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _rexp});
            cons.push_instruction({Operation::CALL, DataType::PTR, _t, {}, {}, "concat_list"});
            break;
        }
        case (BinaryOp::APPEND): {
            auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
            generate_node(_rexp, ltype->elem, node.r_exp->resolved_type);
            _rexp = cons.pop_operand();

            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _lexp});
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _rexp});
            cons.push_instruction({Operation::CALL, DataType::PTR, _t, {}, {}, "concat_list"});
            break;
        }
        case (BinaryOp::INDEX): {
            auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
            Operand _ptr = cons.get_register();
            cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _lexp});
            // maybe need to cast
            cons.push_instruction({Operation::PARAM, DataType::I32, {}, _rexp});
            cons.push_instruction({Operation::CALL, DataType::PTR, _ptr, {}, {}, "index_list"});

            cons.push_instruction({Operation::LOAD, type_to_dtype(ltype->elem->kind), _t, _ptr});
        }
        default : return;
    }
    cons.push_operand(_t);
}

void IR_Lowerer::visit( CallNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

    for (int i = 0; i < node.params.size(); i++){
        node.params[i]->accept(*this);
        Operand _t = cons.pop_operand();
        cast_operand(_t, node.ptypes[i], node.params[i]->resolved_type);
        Operand _cast = cons.pop_operand();

        DataType dtype = type_to_dtype(node.ptypes[i]->kind);
        cons.push_instruction({Operation::PARAM, dtype, {}, _cast});
    }
    Operand _t = cons.get_register();
    DataType rtype = type_to_dtype(node.resolved_type->kind);
    cons.push_instruction({Operation::CALL, rtype, _t, {}, {}, node.label});
    cons.push_operand(_t);
};

void IR_Lowerer::visit( StructNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

    unsigned int id = structInfo.get_struct_id(node.name);
    cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(id)});
    Operand _ptr = cons.get_register();
    cons.push_instruction({Operation::CALL, DataType::PTR, _ptr, {}, {}, "allocate_struct"});
    for (int i = 0; i < node.fields.size(); i++){
        node.fields[i]->accept(*this);
        Operand _t = cons.pop_operand();

        if (node.ftypes[i]->kind == Type::Kind::Struct || node.ftypes[i]->kind == Type::Kind::List)
            increase_ref(_t, node.ftypes[i]);
        else {
            cast_operand(_t, node.ftypes[i], node.fields[i]->resolved_type);
            _t = cons.pop_operand();
        }
        DataType dtype = type_to_dtype(node.ftypes[i]->kind);
        cons.push_instruction({Operation::PARAM, DataType::PTR, {}, {}, _ptr});
        cons.push_instruction({Operation::PARAM, DataType::I32, {}, {}, Operand::imm(i)});

        Operand _fptr = cons.get_register();
        cons.push_instruction({Operation::CALL, DataType::PTR, _fptr, {}, {}, "access_field"});
        cons.push_instruction({Operation::STORE, dtype, _fptr, _t});
    }
    cons.push_operand(_ptr);
}

void IR_Lowerer::visit( AccessNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

    node.struct_expr->accept(*this);
    Operand _ptr = cons.pop_operand();

    unsigned int field_id = structInfo.get_field_id(node.sn, node.field);
    cons.push_instruction({Operation::PARAM, DataType::PTR, {}, {}, _ptr});
    cons.push_instruction({Operation::PARAM, DataType::I32, {}, {}, Operand::imm(field_id)});

    Operand _fptr = cons.get_register();
    cons.push_instruction({Operation::CALL, DataType::PTR, _fptr, {}, {}, "access_field"});

    Operand _t = cons.get_register();
    DataType dtype = type_to_dtype(node.resolved_type->kind);
    cons.push_instruction({Operation::LOAD, dtype, _t, _fptr});

    cons.push_operand(_t);
}

void IR_Lowerer::visit( NominalNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::var(identifier.get_ident(node.label))); // ??
}

void IR_Lowerer::visit( CharLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::imm(node.value));
}

void IR_Lowerer::visit( IntLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::imm(node.value));
}

void IR_Lowerer::visit( FloatLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    int64_t _bitval; 
    std::memcpy(&_bitval, &node.value, sizeof(_bitval));
    cons.push_operand(Operand::imm(node.value));
}

void IR_Lowerer::visit( BoolLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::imm(node.value));
}

void IR_Lowerer::visit( EmptyLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::imm(0)); // null ptr
}

void IR_Lowerer::visit( NilLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::imm(0)); // null ptr
}

void IR_Lowerer::visit( ListPatternLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    unsigned int size = node.patterns.size() - 1;
    Operand _ptr = cons.pop_operand();

    Operand _size = cons.get_register();
    cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _ptr});
    cons.push_instruction({Operation::CALL, DataType::I32, _size, {}, {}, "list_size"});

    Operand _t = cons.get_register();
    cons.push_instruction({Operation::CGEQ, DataType::I32, _t, _size, Operand::imm(size)});
    cons.push_operand(_t);
}

void IR_Lowerer::visit( StructPatternLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    unsigned int size = node.patterns.size() - 1;
    Operand _ptr = cons.pop_operand();

    Operand _field = cons.get_register();
    Operand _neq = cons.get_register();

    std::string L_false = builder.get_scratch_label();
    std::string L_end = builder.get_scratch_label();

    for (int i = 0; i < node.patterns.size(); i++){
        if (!node.patterns[i].empty()) continue; // non-nil

        cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _ptr});
        cons.push_instruction({Operation::PARAM, DataType::PTR, {}, Operand::imm(i)});
        cons.push_instruction({Operation::CALL, DataType::PTR, _field, {}, {}, "access_field"});
        // null pointer check
        cons.push_instruction({Operation::CEQ, DataType::PTR, _neq, _field, Operand::imm(0)});
        cons.push_instruction({Operation::JMP_IF, DataType::BOOL, {}, _neq, {}, L_false});
    }
    Operand _t = cons.get_register();
    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, Operand::imm(1)});
    cons.push_instruction({Operation::JMP, DataType::EMPTY, {}, {}, {}, L_end});
    gen_block(L_false);
    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, Operand::imm(0)});
    gen_block(L_end);
    cons.push_operand(_t);
}

void IR_Lowerer::visit( EnumLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    nominal_ptr etype = std::static_pointer_cast<NominalType>(node.resolved_type);
    std::string en = etype->name;
    cons.push_operand(Operand::imm(structInfo.get_enum_id(en, node.elem)));
}

void IR_Lowerer::visit( ReturnNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    node.rexp->accept(*this);
    Operand _exp = cons.pop_operand();
    cons.push_instruction({Operation::RET, type_to_dtype(node.resolved_type->kind), {}, _exp});
}

void IR_Lowerer::visit( ListNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
    type_ptr etype = ltype->elem;

    if (node.elems.empty()){ 
        cons.push_operand(Operand::imm(0)); // null ptr
        return;
    }
    if (etype->kind == Type::Kind::List) cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(1)});
    else if (etype->kind == Type::Kind::Struct) cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(2)});
    else cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(0)});
    
    Operand _ptr = cons.get_register();
    cons.push_instruction({Operation::PARAM, DataType::I64, {}, Operand::imm(type_to_size(etype->kind))});
    cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(node.elems.size())});
    cons.push_instruction({Operation::CALL, DataType::PTR, _ptr, {}, {}, "alloc_list"});

    Operand _index = cons.get_register();
    for (int i = 0; i < node.elems.size(); i++){
        node.elems[i]->accept(*this);
        Operand _elem = cons.pop_operand();

        // increase ref counts to objects
        if (etype->kind == Type::Kind::List || etype->kind == Type::Kind::Struct)
            increase_ref(_elem, etype);
        else {
            cast_operand(_elem, etype, node.elems[i]->resolved_type);
            _elem = cons.pop_operand();
        }
        cons.push_instruction({Operation::PARAM, DataType::PTR, {}, _ptr});
        cons.push_instruction({Operation::PARAM, DataType::I32, {}, Operand::imm(i)});
        cons.push_instruction({Operation::CALL, DataType::PTR, _index, {}, {}, "index_list"});
        cons.push_instruction({Operation::STORE, type_to_dtype(etype->kind), _index, _elem});
    }
}