#include "tac_ir.hpp"
#include "interf_graph.hpp"
#include <cstring>
#include <fstream>
#include <string>
#include <unordered_map>
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
    shift_params(func);
    lower_ins(func);
    write_func(func);
    return ig;
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
    std::unordered_map<Operand, int, Operand::OperandHash> spills;
    std::unordered_map<Operand, Operand, Operand::OperandHash> remap;
    for (auto it = header->ins.begin(); it != header->ins.end(); it++){
        Instruction& ins = *it;
        if (ins.op == Operation::LOCAL){
            Operand _t = func.get_register();
            remap.emplace(ins.src1, _t);

            if (!is_fp(ins.type)){
                ++gp_param;
                if (gp_param >= gp_params.size()) spills[ins.src1] = (++spilt_params * 8) + 16; // saved rbp, saved address
                params.push_back({ins.src1, ins.type});
            }
            else {
                ++fp_param;
                if (fp_param >= fp_params.size()) spills[ins.src1] = (++spilt_params * 8) + 16; // saved rbp, saved address
                params.push_back({ins.src1, ins.type});
            }
            continue;
        }
    }

    // replace all instances of variables with remappings
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins){
            if (ins.op == Operation::LOCAL) continue;

            if (remap.contains(ins.dst)) ins.dst = remap[ins.dst];
            if (remap.contains(ins.src1)) ins.src1 = remap[ins.src1];
            if (remap.contains(ins.src2)) ins.src2 = remap[ins.src2];
        }
    }

    for (auto it = header->ins.begin(); it != header->ins.end(); it++){
        Instruction& ins = *it;
        if (ins.op == Operation::BEGIN_FUNC){
            it++; // head to first instruction
            for (auto& p : params){
                if (spills.contains(p.first))
                    header->ins.insert(it, {Operation::LOAD, p.second, remap[p.first], Operand::rbp(spills[p.first])});
                else header->ins.insert(it, {Operation::MOV, p.second, remap[p.first], p.first});
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
void X86_Lowerer::lower_ins(FunctionIR& func){
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
                //case (Operation::MUL) : 
                {
                    if (is_fp(ins.type)) break;
                    
                    Operand _rax = func.get_register();
                    b->ins.insert(it, {Operation::MOV, ins.type, _rax, ins.src1});

                    ins.src1 = _rax;
                    
                    it++; // past ins
                    b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, _rax});
                    ins.dst = _rax;
                    break;
                }
                case (Operation::MOD) : {
                    Operand _rax = func.get_register();
                    b->ins.insert(it, {Operation::MOV, ins.type, _rax, ins.src1});

                    ins.src1 = _rax;
                    Operand _rdx = func.get_register();
                    
                    it++; // past ins
                    b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, _rdx});
                    ins.dst = _rdx;
                    break;
                }
                case (Operation::LSL) :
                case (Operation::LSR) : {
                    Operand _rcx = func.get_register();

                    if (!ins.src2.is_register()) break; // immediates can be directly called

                    b->ins.insert(it, {Operation::MOV, ins.type, _rcx, ins.src2});
                    b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, ins.src1});
                    ins.src2 = _rcx;
                    ins.src1 = ins.dst;

                    break;
                }
                case (Operation::PARAM) : {
                    if (is_fp(ins.type)){
                        fp_param++;
                        if (fp_param >= fp_params.size()) b->ins.insert(it, {Operation::STORE, ins.type, Operand::rsp(++spilt_params * 8), ins.src1});
                        else {
                            Operand _param = func.get_register();
                            b->ins.insert(it, {Operation::MOV, ins.type, _param, ins.src1});
                            ins.src1 = _param;
                        }
                    }
                    else {
                        gp_param++;
                        if (gp_param >= gp_params.size()) b->ins.insert(it, {Operation::STORE, ins.type, Operand::rsp(++spilt_params * 8), ins.src1});
                        else {
                            Operand _param = func.get_register();
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

                        it++;
                        b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, _xmm0});
                        ins.dst = _xmm0;
                    }
                    else { // mov rax->dst
                        Operand _rax = func.get_register();

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
                        b->ins.insert(it, {Operation::MOV, ins.type, _xmm0, ins.src1});
                        ins.src1 = _xmm0;
                    }
                    else { // mov return -> rax
                        Operand _rax = func.get_register();
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

            if (!cmp_op(prior.op) && prior.dst != ins.src1){ // depends on an external boolean register
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