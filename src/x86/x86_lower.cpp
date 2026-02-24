#include "tac_ir.hpp"
#include "interf_graph.hpp"
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include "x86_lower.hpp"

/*
    Instruction Selection for X86 aware IR
    from target-independent IR
*/
InterferenceGraph X86_Lowerer::lower_x86(FunctionIR& func){
    ig = InterferenceGraph();
    assign_statics(func);
    fix_jumps(func);
    add_nodes(func);
    shift_params(func);
    precolour_ins(func);
    //write_func(func);
    return ig;
}

void X86_Lowerer::add_nodes(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins){ // initialise all nodes
            RType rtype = dtype_to_rtype(ins.type);

            if (ins.dst.is_register()) ig.add_node(ins.dst, rtype);
            if (ins.src1.is_register()) ig.add_node(ins.src1, rtype);
            if (ins.src2.is_register()) ig.add_node(ins.src2, rtype);
        }
    }
}

/*
    Shift parameters in volatile param registers to new registers
*/
void X86_Lowerer::shift_params(FunctionIR& func){
    Block* header = func.blocks[0].get();

    int gp_param = -1;
    int fp_param = -1;
    int spilt_params = 0;
    std::vector<std::pair<Operand, DataType>> params;
    for (auto it = header->ins.begin(); it != header->ins.end(); it++){
        Instruction& ins = *it;
        if (ins.op == Operation::LOCAL){
            IGNode& node = ig.get_node(ins.src1);
            if (!is_fp(ins.type)){
                ++gp_param;
                if (gp_param >= gp_params.size()) node.spill = (++spilt_params * 8) + 16; // saved rbp, saved address
                else {
                    node.assigned = gp_params[gp_param];
                    params.push_back({ins.src1, ins.type});
                }
            }
            else {
                ++fp_param;
                if (fp_param >= fp_params.size()) node.spill = (++spilt_params * 8) + 16; // saved rbp, saved address
                else {
                    node.assigned = fp_params[fp_param];
                    params.push_back({ins.src1, ins.type});
                }
            }
            continue;
        }
        if (ins.op == Operation::BEGIN_FUNC){
            it++; // head to first instruction
            for (auto& p : params){
                Operand _t = func.get_register();
                header->ins.insert(it, {Operation::MOV, p.second, _t, p.first});
            }
            return;
        }
    }
}

/*
    precolour/shift for special registers
        - rax for multiplication
        - rdx/rax for division/modulo
        - rcx for shift
*/
void X86_Lowerer::precolour_ins(FunctionIR& func){
    int fp_param = -1;
    int gp_param = -1;
    int spilt_params = 0;
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end(); it++){ // initialise all nodes
            Instruction& ins = *it;
            switch (ins.op){
                case (Operation::FLR) :
                case (Operation::DIV) : 
                case (Operation::MUL) : {
                    if (is_fp(ins.type)) break;
                    
                    Operand _rax = func.get_register();
                    IGNode& rax_node = ig.add_node(_rax, GP);
                    rax_node.assigned = static_cast<int>(RAX);

                    b->ins.insert(it, {Operation::MOV, ins.type, _rax, ins.src1});

                    ins.src1 = VOID;
                    
                    it++; // past ins
                    b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, _rax});
                    ins.dst = VOID;
                    break;
                }
                case (Operation::MOD) : {
                    Operand _rax = func.get_register();
                    IGNode& rax_node = ig.add_node(_rax, GP);
                    rax_node.assigned = static_cast<int>(RAX);

                    b->ins.insert(it, {Operation::MOV, ins.type, _rax, ins.src1});

                    ins.src1 = VOID;
                    
                    Operand _rdx = func.get_register();
                    IGNode& rdx_node = ig.add_node(_rdx, GP);
                    rdx_node.assigned = static_cast<int>(RDX);
                    
                    it++; // past ins
                    b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, _rdx});
                    ins.dst = VOID;
                    break;
                }
                case (Operation::LSL) :
                case (Operation::LSR) : {
                    if (is_fp(ins.type)) break;
                    Operand _rcx = func.get_register();
                    IGNode& node = ig.add_node(_rcx, GP);
                    node.assigned = static_cast<int>(RCX);
                    b->ins.insert(it, {Operation::MOV, ins.type, _rcx, ins.src2});
                    ins.src2 = _rcx;

                    break;
                }
                case (Operation::PARAM) : {
                    if (is_fp(ins.type)){
                        fp_param++;
                        if (fp_param >= fp_params.size()) b->ins.insert(it, {Operation::STORE, ins.type, Operand::rsp(++spilt_params * 8)});
                        else {
                            Operand _param = func.get_register();
                            IGNode& node = ig.add_node(_param, FP);
                            node.assigned = static_cast<int>(fp_params[fp_param]);
                            b->ins.insert(it, {Operation::MOV, ins.type, _param, ins.src1});
                            ins.src1 = _param;
                        }
                    }
                    else {
                        gp_param++;
                        if (gp_param >= gp_params.size()) b->ins.insert(it, {Operation::STORE, ins.type, Operand::rsp(++spilt_params * 8)});
                        else {
                            Operand _param = func.get_register();
                            IGNode& node = ig.add_node(_param, GP);
                            node.assigned = static_cast<int>(gp_params[gp_param]);
                            b->ins.insert(it, {Operation::MOV, ins.type, _param, ins.src1});
                            ins.src1 = _param;
                        }
                    }
                    break;
                }
                case (Operation::CALL) : {
                    if (spilt_params){
                        for (auto call_it = it; call_it != b->ins.begin();){
                            --call_it;
                            Instruction& temp = *call_it;
                            if (temp.op == Operation::BEGIN_CALL){
                                if (spilt_params % 2) spilt_params++; // allocate to 16B call frame
                                b->ins.insert(call_it, {Operation::SUB, DataType::PTR, Operand::rsp(0), Operand::rsp(0), Operand::imm(spilt_params * 8)});
                                break;
                            }
                        }
                    }
                }
                case (Operation::CALL_EXT) : { // (syslib calls have no spilt params)
                    gp_param = -1, fp_param = -1; // reset param count
                    if (ins.type == DataType::EMPTY) break;

                    if (is_fp(ins.type)){ // mov xmm0->dst
                        Operand _xmm0 = func.get_register();
                        IGNode& node = ig.add_node(_xmm0, FP);
                        node.assigned = static_cast<int>(XMM0);

                        it++;
                        b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, _xmm0});
                        ins.dst = _xmm0;
                    }
                    else { // mov rax->dst
                        Operand _rax = func.get_register();
                        IGNode& node = ig.add_node(_rax, GP);
                        node.assigned = static_cast<int>(RAX);

                        it++;
                        b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, _rax});
                        ins.dst = _rax;
                    }
                    if (ins.op == Operation::CALL && spilt_params)
                        b->ins.insert(it, {Operation::ADD, DataType::PTR, Operand::rsp(0), Operand::rsp(0), Operand::imm(spilt_params * 8)});
                    spilt_params = 0;

                    break;
                }
                case (Operation::RET) : {
                    if (is_fp(ins.type)){ // mov return -> xmm0
                        Operand _xmm0 = func.get_register();
                        IGNode& node = ig.add_node(_xmm0, FP);
                        node.assigned = static_cast<int>(XMM0);
                        b->ins.insert(it, {Operation::MOV, ins.type, _xmm0, ins.src1});
                        ins.src1 = _xmm0;
                    }
                    else { // mov return -> rax
                        Operand _rax = func.get_register();
                        IGNode& node = ig.add_node(_rax, GP);
                        node.assigned = static_cast<int>(RAX);
                        b->ins.insert(it, {Operation::MOV, ins.type, _rax, ins.src1});
                        ins.src1 = _rax;
                    }
                    break;
                }
                default : continue;
            }
        }
    }
}

bool cmp_op(Operation op){
    return (
        op == Operation::CEQ || 
        op == Operation::CNEQ || 
        op == Operation::CLEQ || 
        op == Operation::CGEQ || 
        op == Operation::CLT || 
        op == Operation::CGT
    );
}

/*
    Fix jump instructions to remove redundant registers
*/
void X86_Lowerer::fix_jumps(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end(); it++){
            Instruction& ins = *it;
            if (ins.op != Operation::JMP_IF) continue;
            
            if (ins.src1 == Operand::imm(1)){
                ins.op = Operation::JMP; continue;
            }
            
            it--;
            Instruction& prior = *(it++);

            if (!cmp_op(prior.op) || prior.dst != ins.src1){ // depends on an external boolean register
                b->ins.insert(it, {Operation::CEQ, DataType::EMPTY, VOID, ins.src1, Operand::imm(1)});
                ins.src1 = VOID;
                continue;
            }
            // now prior is a compare that affects the jump condition
            // don't require jmp condition register as cmp will provide the flag
            ins.src1 = VOID;
            prior.dst = VOID;
        }
    }
}

void X86_Lowerer::assign_statics(FunctionIR& func){
    if (func.is_static) statics.closures.push_back(func.name);

    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end(); it++){
            Instruction& ins = *it;

            if (ins.op == Operation::CALL_EXT){ // external functions
                statics.externs.insert(ins.target);
                continue;
            }


            if (ins.type != DataType::F32 && ins.type != DataType::F64) continue;

            std::string fp_imm;
            if (ins.src1.type == Operand::IMM){
                if (!statics.float_imms.contains(ins.src1)){
                    fp_imm = ".fp_imm_"+std::to_string(statics.float_imms.size());
                    statics.float_imms.emplace(ins.src1, fp_imm);
                }
                else fp_imm = statics.float_imms[ins.src1];
                Operand _t = func.get_register();
                b->ins.insert(it, {Operation::ADDR, ins.type, _t, VOID, VOID, fp_imm});
                ins.src1 = _t;
            }
            if (ins.src2.type == Operand::IMM){
                if (!statics.float_imms.contains(ins.src2)){
                    fp_imm = ".fp_imm_"+std::to_string(statics.float_imms.size());
                    statics.float_imms.emplace(ins.src2, fp_imm);
                }
                else fp_imm = statics.float_imms[ins.src2];
                Operand _t = func.get_register();
                b->ins.insert(it, {Operation::ADDR, ins.type, _t, VOID, VOID, fp_imm});
                ins.src2 = _t;
            }
        }
    }
}

void X86_Lowerer::write_statics(){
    // clear then append
    std::ofstream sdata("./.aux/static_data", std::ios::trunc);
    sdata.close();
    sdata.open("./.aux/static_data", std::ios::app);

    for (std::string ext : statics.externs){
        sdata << ".extern "<<ext<<'\n';
    }
    sdata << '\n';

    // writeable data -- static closures
    sdata << ".section .data\n" << ".align 8\n";

    for (std::string fname : statics.closures){
        sdata<<fname<<".local:\n";
        sdata<<"\t.quad 0\n"; // NULL env
        sdata<<"\t.quad "<<fname<<'\n'; // Function name
        sdata<<"\t.long 1\n"; // ref count
    }
    sdata << '\n';

    // readable data -- float immediates
    sdata << ".section .rodata\n" << ".align 8\n";
    for (auto& p : statics.float_imms){
        sdata<<p.second<<":\n";
        if (p.first.kind == DataType::F32){ // float
            int32_t temp = static_cast<int32_t>(p.first.value);
            float f;
            std::memcpy(&f, &temp, sizeof(temp));

            sdata <<'\t'<<p.second<<':'<<" .float "<<f<<'\n';
        }
        else {
            double d;
            std::memcpy(&d, &p.first.value, sizeof(p.first.value));

            sdata <<'\t'<<p.second<<':'<<" .double "<<d<<'\n';
        }
    }
}