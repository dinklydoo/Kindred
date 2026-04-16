#include "flowcheck.hpp"
#include "ast.hpp"
#include "types.hpp"
#include <cstdint>
#include <memory>

using namespace fc;

void FlowChecker::flowcheck( ModuleNode& node){
    node.accept(*this);
    warnings.report_warnings();
    errors.report_errors();
}


void FlowChecker::visit( ModuleNode& node){
    for (auto& d : node.decl){
        d->accept(*this);
    }
    if (!main_defined)errors.main_error(node.location);
}

void FlowChecker::visit( FuncDecl& node){
    if (main_defined) 
        warnings.postdecl_warning(node.name, Type::Kind::Func,node);

    if (node.name == "main") main_defined = true;
    node.body->accept(*this);
}

void FlowChecker::visit( EnumDecl& node ){
    if (main_defined) 
        warnings.postdecl_warning(node.name, Type::Kind::Func,node);
}

void FlowChecker::visit( StructDecl& node ){
    if (main_defined) 
        warnings.postdecl_warning(node.name, Type::Kind::Func,node);
}

void FlowChecker::visit( ProgramNode& node ){
    for (auto& d : node.decl){
        d->accept(*this);
    }
    node.body->accept(*this);
}

void FlowChecker::visit( CaseNode& node ){
    type_ptr ptype = node.target->resolved_type;
    exb_ptr bptr;
    switch (ptype->kind){
        case (Type::Kind::Enum):{
            std::unique_ptr<EnumExBlock> temp = std::make_unique<EnumExBlock>();
            nominal_ptr etype = std::static_pointer_cast<NominalType>(ptype);
            std::vector<Enumerable>& enums = etype->get_enums();

            for (auto& e : enums)
                temp->rem.insert(e.label);
            bptr = std::move(temp);
            break;
        }
        // probs should template this but whatever
        case (Type::Kind::Bool): bptr = std::make_unique<BoolExBlock>(); break;
        case (Type::Kind::Struct): bptr = std::make_unique<StructExBlock>(); break;
        case (Type::Kind::List): bptr = std::make_unique<ListExBlock>(); break;
        case (Type::Kind::Char): bptr = std::make_unique<ValExBlock<char>>(); break;
        case (Type::Kind::Int): bptr = std::make_unique<ValExBlock<int32_t>>(); break;
        case (Type::Kind::Long): bptr = std::make_unique<ValExBlock<int64_t>>(); break;
        case (Type::Kind::Float): bptr = std::make_unique<ValExBlock<float>>(); break;
        case (Type::Kind::Double): bptr = std::make_unique<ValExBlock<double>>(); break;
        default: break;
    }
    blocks.enter_branch(std::move(bptr));
    exb_ptr& exb = blocks.get_top();
    for (int i = 0; i < node.patterns.size(); i++){
        if (exb->exhausted()){
            warnings.unreach_warning(
                "Pattern matches exhausted following "
                "branches are unreachable", node.patterns[i]->location
            );
            for (; i < node.patterns.size(); i++) node.patterns[i]->reachable = false;
        }
        else node.patterns[i]->accept(*this);
    }
    if (!exb->exhausted()){
        errors.inexh_error(
            "Pattern match is inexhaustive, program "
            "behaviour undefined in some conditions",node
        );
    }
    blocks.exit_branch();
}

void FlowChecker::visit(CaseBranchNode& node){
    exb_ptr& exb = blocks.get_top();
    node.pattern->accept(*this);

    if (exb->contained){
        node.reachable = false;
        warnings.unreach_warning(
            "Pattern match has been covered by a prior "
            "pattern, branch is unreachable", node.pattern->location
        );
        exb->contained = false;
    }
    else node.body->accept(*this);
}

void FlowChecker::visit(GuardNode& node){
    blocks.enter_branch(std::make_unique<ExBlock>());
    exb_ptr& exb = blocks.get_top();
    for (int i = 0; i < node.branches.size(); i++){
        if (exb->exhausted()){
            warnings.unreach_warning(
                "Pattern matches exhausted following "
                "branches are unreachable", node.branches[i]->location
            );
            for (; i < node.branches.size(); i++) node.branches[i]->reachable = false;
        }
        else node.branches[i]->accept(*this);
    }
    if (!exb->exhausted()){
        errors.inexh_error(
            "Pattern match is inexhaustive, program "
            "behaviour undefined in some conditions",node
        );
    }
    blocks.exit_branch();
}

void FlowChecker::visit(GuardBranchNode& node){
    exb_ptr& exb = blocks.get_top();
    node.match->accept(*this);
    node.body->accept(*this);
}

void FlowChecker::visit(EnumLit& node){
    EnumExBlock& enum_block = static_cast<EnumExBlock&>(*blocks.get_top());
    if (enum_block.rem.count(node.elem)) enum_block.rem.erase(node.elem);
    else enum_block.contained = true;
}

void FlowChecker::visit(BoolLit& node){
    BoolExBlock& bool_block = static_cast<BoolExBlock&>(*blocks.get_top());
    
    if (node.value){
        if (bool_block.t_case) bool_block.contained = true;
        else bool_block.t_case = true;
    }
    else {
        if (bool_block.f_case) bool_block.contained = true;
        else bool_block.f_case = true;
    }
}

void FlowChecker::visit(EmptyLit& node){
    ListExBlock& list_block = static_cast<ListExBlock&>(*blocks.get_top());

    if (list_block.e_case) list_block.contained = true;
    else list_block.e_case = true;
}

void FlowChecker::visit(ListPatternLit& node){
    ListExBlock& list_block = static_cast<ListExBlock&>(*blocks.get_top());

    int size = node.patterns.size() - 1;
    if (list_block.subsumes < 0){ list_block.subsumes = size; }
    else if (size >= list_block.subsumes) list_block.contained = true;
    else list_block.subsumes = std::min(size, list_block.subsumes);

    if (size == 1) list_block.s_case = true;
}

void FlowChecker::visit(NilLit& node){
    StructExBlock& struct_block = static_cast<StructExBlock&>(*blocks.get_top());

    if (struct_block.nil_case) struct_block.contained = true;
    else struct_block.nil_case = true;
}

void FlowChecker::visit(StructPatternLit& node){
    StructExBlock& struct_block = static_cast<StructExBlock&>(*blocks.get_top());

    std::vector<bool> pattern;
    bool full = true;
    for (auto& p : node.patterns){
        if (p == "@nil"){
            pattern.push_back(false); // false indicates a nil value required
            full = false;
        }
        else pattern.push_back(true);
    }
    if (full){ // if no nil values -> default
        if (struct_block.full_case) struct_block.contained = true;
        else struct_block.full_case = true;
    }
    else {
        for (auto& s : struct_block.seen){
            bool subsumes = true;
            for (int i = 0; i < pattern.size(); i++){
                if (pattern[i] && !s[i]){ subsumes = false; break; }
            }
            if (subsumes){
                struct_block.contained = true;
                return;
            }
        }
    }
}

void FlowChecker::visit(DefaultLit& node){
    exb_ptr& exb = blocks.get_top();
    exb->ex = true;
}

void FlowChecker::visit(ElseLit& node){
    exb_ptr& exb = blocks.get_top();
    exb->ex = true;
}

template <typename T>
T get_var(const pattern_lit& var) {
    static_assert(std::is_arithmetic_v<T>);
    return std::visit(
        [](const auto& v)->T
        {return static_cast<T>(v);}
        ,var 
    );
}

template<typename T>
void cast_pattern(ExBlock& exb, pattern_lit val){
    ValExBlock<T>& v_block = static_cast<ValExBlock<T>&>(exb);
    T v_val = get_var<T>(val);
    if (v_block.seen.count(v_val)) exb.contained = true;
    else v_block.seen.insert(v_val);
}

void FlowChecker::add_pattern(ExBlock& exb, type_ptr exp, pattern_lit val){
    Type::Kind exp_kind = exp->kind;
    switch (exp_kind){
        case (Type::Kind::Char):{
            cast_pattern<char>(exb, val);
            return;
        }
        case (Type::Kind::Int):{
            cast_pattern<int32_t>(exb, val);
            return;
        }
        case (Type::Kind::Long):{
            cast_pattern<int64_t>(exb, val);
            return;
        }
        case (Type::Kind::Float):{
            cast_pattern<float>(exb, val);
            return;
        }
        case (Type::Kind::Double):{
            cast_pattern<double>(exb, val);
            return;
        }
        default : return;
    }
}

void FlowChecker::visit(CharLit& node){
    type_ptr exp = node.resolved_type;
    add_pattern(*blocks.get_top(), exp, node.value);
}

void FlowChecker::visit(IntLit& node){
    type_ptr exp = node.resolved_type;
    add_pattern(*blocks.get_top(), exp, node.value);
}

void FlowChecker::visit(FloatLit& node){
    type_ptr exp = node.resolved_type;
    add_pattern(*blocks.get_top(), exp, node.value);
}