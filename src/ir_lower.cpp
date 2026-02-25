#include "ir_lower.hpp"
#include "ast.hpp"
#include "tac_ir.hpp"
#include "types.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// TODO : FIX BLOCK LABELS IN BRANCHING EXPRESSIONS AND SHORT CIRCUIT

using namespace ir;

DataType type_to_dtype(Type::Kind kind){
    switch (kind){
        case (Type::Kind::List) :
        case (Type::Kind::Func) : // closure pointer
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
        case (Type::Kind::Func) :
        case (Type::Kind::Long) : return 8;
        default : return -1; // no hit
    }
}

void IR_Lowerer::op_equals(Operand ptr1, Operand ptr2, type_ptr type){
    ConsFunctionIR& cons = builder.top_constructor();
    Operand _t0 = cons.get_register();
    switch (type->kind){
        case (Type::Kind::GENERIC) : {
            cons.push_operand(TRUE);
            return;
        }
        case (Type::Kind::Struct) : {
            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, ptr1});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, ptr2});
            cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _t0, VOID, VOID, "struct_equals"});
            break;
        }
        case (Type::Kind::List) : {
            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, ptr1});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, ptr2});
            cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _t0, VOID, VOID, "list_equals"});    
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
    Operand _t = cons.get_register();

    std::string L_false = builder.get_scratch_label();
    std::string L_end = builder.get_scratch_label();

    node.l_exp->accept(*this);
    Operand _lexp = cons.pop_operand();
    Operand _not_lexp = cons.get_register();
    cons.push_instruction({Operation::NOT, DataType::BOOL, _not_lexp, _lexp});
    cons.push_instruction({Operation::JMP_IF, DataType::BOOL, VOID, _not_lexp, VOID, L_false});

    node.r_exp->accept(*this);
    Operand _rexp = cons.pop_operand();
    Operand _not_rexp = cons.get_register();
    cons.push_instruction({Operation::NOT, DataType::BOOL, _not_rexp, _rexp});
    cons.push_instruction({Operation::JMP_IF, DataType::BOOL, VOID, _not_rexp, VOID, L_false});
    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, TRUE});
    cons.push_instruction({Operation::JMP, DataType::EMPTY, VOID, VOID, VOID, L_end});

    gen_block(L_false); // L_false

    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, FALSE});

    gen_block(L_end); // L_end

    cons.push_operand(_t);
}

void IR_Lowerer::short_or( BinaryNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

    Operand _t = cons.get_register();

    std::string L_true = builder.get_scratch_label();
    std::string L_end = builder.get_scratch_label();

    node.l_exp->accept(*this);
    Operand _lexp = cons.pop_operand();
    cons.push_instruction({Operation::JMP_IF, DataType::BOOL, VOID, _lexp, VOID, L_true});

    node.r_exp->accept(*this);
    Operand _rexp = cons.pop_operand();
    cons.push_instruction({Operation::JMP_IF, DataType::BOOL, VOID, _rexp, VOID, L_true});
    
    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, FALSE});
    cons.push_instruction({Operation::JMP, DataType::EMPTY, VOID, VOID, VOID, L_end});

    gen_block(L_true) ; // L_true

    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, TRUE});
    
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
        if (snode.patterns[i].empty()) continue; // nil pattern

        identifier.push_ident(snode.patterns[i], fields[i].type);
        identifier.get_var(snode.patterns[i]);
        Operand _var = cons.pop_operand();

        cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _target});
        cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(i)});
        cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _t, VOID, VOID, "access_field"});
        cons.push_instruction({Operation::LOAD, type_to_dtype(fields[i].type->kind), _var, _t});

        increase_ref(_var, fields[i].type);
    }
}

void IR_Lowerer::list_pattern_vars( LiteralNode& node){
    ConsFunctionIR& cons = builder.top_constructor();
    Operand _target = cons.pop_operand();
    ListPatternLit& lnode = static_cast<ListPatternLit&>(node);

    auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
    Operand _t = cons.get_register();
    type_ptr etype = ltype->elem;

    for (int i = 0; i < lnode.patterns.size()-1; i++){
        identifier.push_ident(lnode.patterns[i], etype);
        identifier.get_var(lnode.patterns[i]);
        Operand _var = cons.pop_operand();

        cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _target});
        cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(i)});
        cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _t, VOID, VOID, "access_index"});
        cons.push_instruction({Operation::LOAD, type_to_dtype(etype->kind), _var, _t});
        increase_ref(_var, etype);
    }
    int n = lnode.patterns.size();
    identifier.push_ident(lnode.patterns[n-1], ltype);
    identifier.get_var(lnode.patterns[n-1]);
    Operand _var = cons.pop_operand();

    cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
    cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _target});
    cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(n-1)});
    cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _t, VOID, VOID, "access_index"});
    cons.push_instruction({Operation::MOV, type_to_dtype(etype->kind), _var, _t});
    increase_ref(_var, ltype); // increase node ref count
}

void IR_Lowerer::increase_ref( Operand _ptr, type_ptr type){
    ConsFunctionIR& cons = builder.top_constructor();
    switch (type->kind){
        case (Type::Kind::Struct) :
        case (Type::Kind::List) :
        case (Type::Kind::Func) :
            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _ptr});
            break;
        default : return;
    }
    switch (type->kind){
        case (Type::Kind::Struct) : 
            cons.push_instruction({Operation::CALL_EXT, DataType::EMPTY, VOID, VOID, VOID, "incr_struct"}); 
            break;
        case (Type::Kind::List) : 
            cons.push_instruction({Operation::CALL_EXT, DataType::EMPTY, VOID, VOID, VOID, "incr_list"});
            break;
        case (Type::Kind::Func) : 
            cons.push_instruction({Operation::CALL_EXT, DataType::EMPTY, VOID, VOID, VOID, "incr_closure"});
            break;
        default : return;
    }
}

void IR_Lowerer::decrease_ref( Operand _ptr, type_ptr type){
    ConsFunctionIR& cons = builder.top_constructor();
    switch (type->kind){
        case (Type::Kind::Struct) :
        case (Type::Kind::List) :
        case (Type::Kind::Func) :
            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _ptr});
            break;
        default : return;
    }
    switch (type->kind){
        case (Type::Kind::Struct) : 
            cons.push_instruction({Operation::CALL_EXT, DataType::EMPTY, VOID, VOID, VOID, "decr_struct"}); 
            break;
        case (Type::Kind::List) : 
            cons.push_instruction({Operation::CALL_EXT, DataType::EMPTY, VOID, VOID, VOID, "decr_list"});
            break;
        case (Type::Kind::Func) : 
            cons.push_instruction({Operation::CALL_EXT, DataType::EMPTY, VOID, VOID, VOID, "decr_closure"});
            break;
        default : return;
    }
}

void IR_Lowerer::generate_node( Operand elem, type_ptr ltype, type_ptr type){
    ConsFunctionIR& cons = builder.top_constructor();
    
    increase_ref(elem, type);

    Operand _cast = cons.get_register();
    cast_operand(elem, ltype, type);
    _cast = cons.pop_operand();

    Operand _ptr = cons.get_register();
    cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
    if (type->kind == Type::Kind::List) cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(1)});
    else if (type->kind == Type::Kind::Struct) cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(2)});
    else cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(0)});

    cons.push_instruction({Operation::PARAM, DataType::I64, VOID, Operand::imm(type_to_size(ltype->kind))});
    cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, NULL_PTR});
    cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _ptr, VOID, VOID, "cons"});

    Operand _elem = cons.get_register();
    cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _ptr});
    cons.push_instruction({Operation::PARAM, DataType::I32, VOID, NULL_PTR});
    cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _elem, VOID, VOID, "index_list"});

    cons.push_instruction({Operation::STORE, type_to_dtype(ltype->kind), _elem, _cast});
    cons.push_operand(_ptr);
}

/*
    Generate struct or env layout
        - id: of struct or environment
        - kind:
            (0) -> struct
            (1) -> env
*/
#define STRUCT_GEN 0
#define ENV_GEN 1
void IR_Lowerer::generate_layout(std::vector<type_ptr> types, int id, int kind){
    if (types.empty()) return;

    int alignment = 0;
    for (type_ptr t : types){
        alignment = std::max(alignment, type_to_size(t->kind));
    }
    int offset = 0;
    int payload_size;
    std::vector<std::vector<std::string>> layout;
    for (type_ptr t : types){
        int size = type_to_size(t->kind);
        if (offset % size) offset += size - (offset % size);

        payload_size = size + offset;
        
        std::string type;
        switch (t->kind){
            case (Type::Kind::Struct) : type = "STRUCT"; break;
            case (Type::Kind::List) : type = "LIST"; break;
            default : type = "LITERAL";
        }
        layout.push_back({type, std::to_string(offset), std::to_string(size)});
        
        offset += size;
    }
    if (payload_size % alignment) payload_size += alignment - (payload_size % alignment);

    std::string path = "./sys_lib/struct_gen.c";;
    std::string layout_name = "struct";
    std::string layout_name_c = "STRUCT";
    std::string access_name = "field";
    if (kind == ENV_GEN) { // env
        path = "./sys_lib/closure_gen.c";
        layout_name = "env";
        layout_name_c = "ENV";
        access_name = "var";
    }
    std::ofstream classfile(path, std::ios::app);
    classfile << "static "+layout_name+"_layout "+layout_name_c+'_' << id << "_LAYOUT = {\n"
    << "\t.payload_size = "<<payload_size<<",\n"
    <<"\t."+access_name+"_count = "<<types.size()<<",\n"
    <<"\t."+access_name+"s = {\n";
    for (auto& p : layout){
        classfile << "\t\t{.type="<<p[0]<<", .offset="<<p[1]<<", .size="<<p[2]<<"},\n";
    }
    classfile << "\t}\n};\n";
}

type_ptr IDVarScope::get_var(std::string var){
    ConsFunctionIR& cons = IR_Lowerer::instance().builder.top_constructor();
    for (auto it = stack.rbegin(); it != stack.rend(); it++){
        auto& sc = *it;
        if (sc.contains(var) == ENCLOSED){
            auto& p = sc.get_enclosed(var);

            Operand _env = get_env();
            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _env});
            cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(p.first)});
            Operand _ptr = cons.get_register();
            cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _ptr, VOID, VOID, "access_var"});
            Operand _var = cons.get_register();
            cons.push_instruction({Operation::LOAD, type_to_dtype(p.second->kind), _var, _ptr});
            cons.push_operand(_var);
            return p.second;
        }
        if (sc.contains(var) == IDENT){
            auto& p = sc.get_ident(var);
            cons.push_operand(Operand::var(p.first));
            return p.second;
        }
    }
    return nullptr; // never hit
}

void IDVarScope::decr_locals(){
    auto& ir_l = IR_Lowerer::instance();
    ConsFunctionIR& cons = ir_l.builder.top_constructor();
    for (auto& s : locals.back()){
        if (s == "@_ENV") continue; // lowkey hardcoded
        type_ptr t = get_var(s); // variable pointer on stack
        ir_l.decrease_ref(cons.pop_operand(), t);
    }
}

void IR_Lowerer::construct_env(std::string fn, type_ptr ftype, varset& enc){
    ConsFunctionIR& cons = builder.top_constructor();
    Operand _ptr = cons.get_register();
    Operand _func_ptr = cons.get_register();
    if (enc.empty()){
        cons.push_instruction({Operation::ADDR, DataType::PTR, _func_ptr, VOID, VOID, fn});
        cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _func_ptr});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, NULL_PTR});
    }
    else {
        Operand _env = cons.get_register();
        int env_id = envInfo.get_env_id(fn);
        cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
        cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(env_id)});
        cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _env, VOID, VOID, "allocate_env"});
    
        Operand _var = cons.get_register();
        Operand _temp = cons.get_register();
        for (var v : enc){
            identifier.get_var(v.first); // get var from parent function
            _var = cons.pop_operand();
    
            increase_ref(_var, v.second);
    
            int var_id = envInfo.get_var_id(fn, v.first);
            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _env});
            cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(var_id)});
            cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _temp, VOID, VOID, "access_var"});
            cons.push_instruction({Operation::STORE, type_to_dtype(v.second->kind), _temp, _var});
        }
        cons.push_instruction({Operation::ADDR, DataType::PTR, _func_ptr, VOID, VOID, fn});
        cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _func_ptr}); // temp fix for function ptr
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _env});
    }
    cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _ptr, VOID, VOID, "allocate_closure"});
    identifier.push_ident(fn, ftype);
    identifier.get_var(fn);
    Operand _closure = cons.pop_operand();

    cons.push_instruction({Operation::MOV, DataType::PTR, _closure, _ptr});
    // cons.push_operand(_closure);
}

/* ============================================================================================================================================================

                INTERFACE

 ============================================================================================================================================================ */

std::vector<FunctionIR> IR_Lowerer::lower(ModuleNode& node){
    generate_layout_file();
    node.accept(*this);
    close_layout_file();

    return std::move(IRprogram);
}

void IR_Lowerer::generate_layout_file(){
    std::ofstream struct_file("./sys_lib/struct_gen.c", std::ios::trunc);
    // set include paths
    struct_file << "#include \"mem.h\"\n#include \"structs.h\"\n\n";

    std::ofstream env_file("./sys_lib/closure_gen.c", std::ios::trunc);
    // set include paths
    env_file << "#include \"mem.h\"\n#include \"closure.h\"\n\n";
    return;
}

void IR_Lowerer::close_layout_file(){
    std::ofstream struct_file("./sys_lib/struct_gen.c", std::ios::app);
    struct_file << "static struct_layout STRUCT_DATA[] {\n";
    for (int i = 0; i < structInfo.struct_count(); i++){
        struct_file << "\tSTRUCT_"<<i<<"_LAYOUT,\n";
    }
    struct_file << "};\n";

    std::ofstream env_file("./sys_lib/closure_gen.c", std::ios::app);
    env_file << "static env_layout ENV_DATA[] {\n";
    for (int i = 0; i < envInfo.env_count(); i++){
        env_file << "\tENV_"<<i<<"_LAYOUT,\n";
    }
    env_file << "};\n";
}

/* ============================================================================================================================================================

                VISITOR PATTERN VISIT DECLARATIONS

 ============================================================================================================================================================ */

void IR_Lowerer::visit( ModuleNode& node){
    builder.push_function("__root");
    identifier.push_scope();
    for (auto& d : node.decl){
        d->accept(*this);
    }
    identifier.pop_scope();
    builder.pop_function();
}

void IR_Lowerer::visit( StructDecl& node){
    int alignment = 0;
    structInfo.add_struct(node.name, node.fields);

    int struct_id = structInfo.get_struct_id(node.name);
    std::vector<type_ptr> types;
    for (Field& f : node.fields){
        types.push_back(f.type);
    }
    generate_layout(types, struct_id, STRUCT_GEN);
}

void IR_Lowerer::visit( EnumDecl& node ){
    structInfo.add_enum(node.name, node.evar);
}

void IR_Lowerer::visit( FuncDecl& node){
    envInfo.add_env(node.name, node.captures);
    int env_id = envInfo.get_env_id(node.name);
    std::vector<type_ptr> types;
    for (auto& v : node.captures) types.push_back(v.second);
    generate_layout(types, env_id, ENV_GEN);
    construct_env(node.name, node.ftype, node.captures); // assigns closure ptr to variable that shares function name

    builder.push_function(node.name);
    ConsFunctionIR& cons = builder.top_constructor();
    identifier.push_scope();
    
    // ANNOTATE PARAMS WITH @_ENV AS FIRST, ENSURE NO NAME CONFLICTS
    identifier.push_ident("@_ENV", node.ftype); // type is irrelevant
    identifier.get_var("@_ENV"); // first invisible param is closure
    Operand _env = cons.pop_operand();
    identifier.enter_function(_env);
    
    for (auto& v : node.captures) identifier.push_enclosed(v.first, v.second);
    
    cons.push_instruction({Operation::LOCAL, DataType::PTR, VOID, _env});
    for (auto& p : node.params){
        identifier.push_ident(p.name, p.type);
        identifier.get_var(p.name);
        cons.push_instruction({Operation::LOCAL, type_to_dtype(p.type->kind), VOID, cons.pop_operand()});
    }

    cons.push_instruction({Operation::BEGIN_FUNC, DataType::EMPTY});
    node.body->accept(*this);

    identifier.pop_scope();
    identifier.exit_function();

    FunctionIR& ir = builder.top_function();
    IRprogram.push_back(std::move(ir));
    builder.pop_function();
}

void IR_Lowerer::visit( ProgramNode& node){
    for (auto& d : node.decl){
        d->accept(*this);
    }
    node.body->accept(*this);
}

void IR_Lowerer::visit( CaseNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

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
        cons.push_instruction({Operation::JMP_IF, DataType::BOOL, VOID, _eq, VOID, block_label});
    }
    while (!label_s.empty()){
        cons.label_stack.push(label_s.top());
        label_s.pop();
    }
    for (auto& p : node.patterns){
        if (p->pattern_type) cons.push_operand(_target);
        p->accept(*this);
    }
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
        cons.push_instruction({Operation::JMP_IF, DataType::BOOL, VOID, _cond, VOID, block_label});
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
    cons.push_operand(TRUE); // true 
}

void IR_Lowerer::visit( ElseLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(TRUE); // true
}

void IR_Lowerer::visit(VarDecl& node){
    ConsFunctionIR& cons = builder.top_constructor();
    node.r_val->accept(*this);
    Operand _rval = cons.pop_operand(); // expression register

    increase_ref(_rval, node.type);

    identifier.push_ident(node.name, node.type);
    identifier.get_var(node.name);
    Operand _var = cons.pop_operand();
    cast_operand(_rval, node.type, node.r_val->resolved_type);
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
    cast_operand(_tr, node.resolved_type, node.r_exp->resolved_type);
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
        case (BinaryOp::POW): {    
            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, dtype, VOID, _lexp});
            cons.push_instruction({Operation::PARAM, dtype, VOID, _rexp});
            switch (dtype){
                case (DataType::F32) :
                    cons.push_instruction({Operation::CALL_EXT, dtype, _t, VOID, VOID, "float_exp"});break;
                case (DataType::F64) :
                    cons.push_instruction({Operation::CALL_EXT, dtype, _t, VOID, VOID, "double_exp"});break;
                case (DataType::I8) :
                    cons.push_instruction({Operation::CALL_EXT, dtype, _t, VOID, VOID, "char_bin_exp"});break;
                case (DataType::I32) :
                    cons.push_instruction({Operation::CALL_EXT, dtype, _t, VOID, VOID, "int_bin_exp"});break;
                case (DataType::I64) :
                    cons.push_instruction({Operation::CALL_EXT, dtype, _t, VOID, VOID, "long_bin_exp"});break;
                default : break;
            } 
            break;
        }
        case (BinaryOp::FLR): {
            cons.push_instruction({Operation::DIV, dtype, _t, _lexp, _rexp});
            if (dtype == DataType::F32 || dtype == DataType::F64){
                cons.push_instruction({Operation::FLR, dtype, _t, _t});
            }
            break;
        }
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
            if (dtype != DataType::PTR){
                cons.push_instruction({Operation::CNEQ, dtype, _t, _lexp, _rexp}); break;
            }
            op_equals(_lexp, _rexp, node.resolved_type);
            Operand _eq = cons.pop_operand();
            cons.push_instruction({Operation::NOT, DataType::BOOL, _t, _eq});
            break;
        }
        case (BinaryOp::CONCAT): {
            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _lexp});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _rexp});
            cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _t, VOID, VOID, "concat_list"});
            break;
        }
        case (BinaryOp::PREPEND): {
            auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
            generate_node(_lexp, ltype->elem, node.l_exp->resolved_type);
            _lexp = cons.pop_operand();

            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _lexp});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _rexp});
            cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _t, VOID, VOID, "concat_list"});
            break;
        }
        case (BinaryOp::APPEND): {
            auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
            generate_node(_rexp, ltype->elem, node.r_exp->resolved_type);
            _rexp = cons.pop_operand();

            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _lexp});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _rexp});
            cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _t, VOID, VOID, "concat_list"});
            break;
        }
        case (BinaryOp::INDEX): {
            auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
            Operand _ptr = cons.get_register();

            cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
            cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _lexp});
            // maybe need to cast
            cons.push_instruction({Operation::PARAM, DataType::I32, VOID, _rexp});
            cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _ptr, VOID, VOID, "index_list"});

            cons.push_instruction({Operation::LOAD, type_to_dtype(ltype->elem->kind), _t, _ptr});
        }
        default : return;
    }
    cons.push_operand(_t);
}

void IR_Lowerer::visit( CallNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    Operand _hof;
    
    _hof = cons.get_register();
    node.f_exp->accept(*this);
    _hof = cons.pop_operand(); // returns a closure ptr

    Operand _env = cons.get_register();
    cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
    cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _hof});
    cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _env, VOID, VOID, "get_env"});
    
    cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
    cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _env}); // implicitly pass environment in first param of function   

    for (int i = 0; i < node.params.size(); i++){
        node.params[i]->accept(*this);
        Operand _t = cons.pop_operand();
        cast_operand(_t, node.ptypes[i], node.params[i]->resolved_type);
        Operand _cast = cons.pop_operand();

        DataType dtype = type_to_dtype(node.ptypes[i]->kind);
        cons.push_instruction({Operation::PARAM, dtype, VOID, _cast});
    }
    Operand _t = cons.get_register();
    DataType rtype = type_to_dtype(node.resolved_type->kind);

    cons.push_instruction({Operation::CALL, rtype, _t, _hof});
    cons.push_operand(_t);
};

void IR_Lowerer::visit( StructNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

    unsigned int id = structInfo.get_struct_id(node.name);
    cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
    cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(id)});
    Operand _ptr = cons.get_register();
    cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _ptr, VOID, VOID, "allocate_struct"});
    for (int i = 0; i < node.fields.size(); i++){
        node.fields[i]->accept(*this);
        Operand _t = cons.pop_operand();
        
        increase_ref(_t, node.ftypes[i]);
    
        cast_operand(_t, node.ftypes[i], node.fields[i]->resolved_type);
        _t = cons.pop_operand();
        
        DataType dtype = type_to_dtype(node.ftypes[i]->kind);
        cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, VOID, _ptr});
        cons.push_instruction({Operation::PARAM, DataType::I32, VOID, VOID, Operand::imm(i)});

        Operand _fptr = cons.get_register();
        cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _fptr, VOID, VOID, "access_field"});
        cons.push_instruction({Operation::STORE, dtype, _fptr, _t});
    }
    cons.push_operand(_ptr);
}

void IR_Lowerer::visit( AccessNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();

    node.struct_expr->accept(*this);
    Operand _ptr = cons.pop_operand();

    unsigned int field_id = structInfo.get_field_id(node.sn, node.field);
    cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
    cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, VOID, _ptr});
    cons.push_instruction({Operation::PARAM, DataType::I32, VOID, VOID, Operand::imm(field_id)});

    Operand _fptr = cons.get_register();
    cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _fptr, VOID, VOID, "access_field"});

    Operand _t = cons.get_register();
    DataType dtype = type_to_dtype(node.resolved_type->kind);
    cons.push_instruction({Operation::LOAD, dtype, _t, _fptr});

    cons.push_operand(_t);
}

void IR_Lowerer::visit( NominalNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    if (node.kind == VAR_REF){
        identifier.get_var(node.label);
        Operand _var = cons.pop_operand();
        if (builder.static_closures.contains(node.label)){
            cons.push_instruction({Operation::ADDR, DataType::PTR, _var, VOID, VOID, node.label+".local"});
        }
        cons.push_operand(_var);
    }
    if (node.kind == ENUM_VAL){ // enum lit
        auto etype = std::static_pointer_cast<NominalType>(node.resolved_type);
        cons.push_operand(Operand::imm(structInfo.get_enum_id(etype->name, node.label)));
    }
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
    if (node.resolved_type->kind == Type::Kind::Double){
        double d = node.value;
        std::memcpy(&_bitval, &d, sizeof(_bitval));
    }
    else {
        int32_t _temp;
        float f = (float)node.value;
        std::memcpy(&_temp, &f, sizeof(_temp));
        _bitval = static_cast<int64_t>(_temp);
    }
    Operand _t = Operand::imm(_bitval);
    _t.kind = 
        (node.resolved_type->kind == Type::Kind::Double)? DataType::F64 : DataType::F32;
    cons.push_operand(Operand::imm(_bitval));
}

void IR_Lowerer::visit( BoolLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(Operand::imm(node.value));
}

void IR_Lowerer::visit( EmptyLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(NULL_PTR);
}

void IR_Lowerer::visit( NilLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    cons.push_operand(NULL_PTR);
}

void IR_Lowerer::visit( ListPatternLit& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    unsigned int size = node.patterns.size() - 1;
    Operand _ptr = cons.pop_operand();

    Operand _size = cons.get_register();
    cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
    cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _ptr});
    cons.push_instruction({Operation::CALL_EXT, DataType::I32, _size, VOID, VOID, "list_size"});

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

        cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _ptr});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, Operand::imm(i)});
        cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _field, VOID, VOID, "access_field"});
        // null pointer check
        cons.push_instruction({Operation::CEQ, DataType::PTR, _neq, _field, NULL_PTR});
        cons.push_instruction({Operation::JMP_IF, DataType::BOOL, VOID, _neq, VOID, L_false});
    }
    Operand _t = cons.get_register();
    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, TRUE});
    cons.push_instruction({Operation::JMP, DataType::EMPTY, VOID, VOID, VOID, L_end});
    gen_block(L_false);
    cons.push_instruction({Operation::MOV, DataType::BOOL, _t, FALSE});
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
    cast_operand(_exp, node.resolved_type, node.rexp->resolved_type);
    Operand _t = cons.pop_operand();
    increase_ref(_t, node.resolved_type);
    identifier.decr_locals(); // clear locals before return; need to keep return local alive if possible
    cons.push_instruction({Operation::RET, type_to_dtype(node.resolved_type->kind), VOID, _t});
}

void IR_Lowerer::visit( ListNode& node ){
    ConsFunctionIR& cons = builder.top_constructor();
    auto ltype = std::static_pointer_cast<ListType>(node.resolved_type);
    type_ptr etype = ltype->elem;

    if (node.elems.empty()){ 
        cons.push_operand(NULL_PTR); // null ptr
        return;
    }
    cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
    if (etype->kind == Type::Kind::List) cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(1)});
    else if (etype->kind == Type::Kind::Struct) cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(2)});
    else cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(0)});
    
    Operand _ptr = cons.get_register();
    cons.push_instruction({Operation::PARAM, DataType::I64, VOID, Operand::imm(type_to_size(etype->kind))});
    cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(node.elems.size())});
    cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _ptr, VOID, VOID, "alloc_list"});

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
        cons.push_instruction({Operation::BEGIN_CALL, DataType::EMPTY});
        cons.push_instruction({Operation::PARAM, DataType::PTR, VOID, _ptr});
        cons.push_instruction({Operation::PARAM, DataType::I32, VOID, Operand::imm(i)});
        cons.push_instruction({Operation::CALL_EXT, DataType::PTR, _index, VOID, VOID, "index_list"});
        cons.push_instruction({Operation::STORE, type_to_dtype(etype->kind), _index, _elem});
    }
    cons.push_operand(_ptr);
}