#include "tac_ir.hpp"
#include "interf_graph.hpp"
#include "x86_lower.hpp"

/*
    Instruction Selection for X86 aware IR
    from target-independent IR
*/
InterferenceGraph lower_x86(FunctionIR& func){
    InterferenceGraph ig;
    add_nodes(func, ig);
    shift_params(func, ig);
    precolour_ins(func, ig);
    return ig;
}

void add_nodes(FunctionIR& func, InterferenceGraph& ig){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins){ // initialise all nodes
            if (ins.dst.is_register()) ig.add_node(ins.dst, ins.type);
            if (ins.src1.is_register()) ig.add_node(ins.src1, ins.type);
            if (ins.src2.is_register()) ig.add_node(ins.src2, ins.type);
        }
    }
}

/*
    Shift parameters in volatile param registers to new registers
*/
void shift_params(FunctionIR& func, InterferenceGraph& ig){
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
void precolour_ins(FunctionIR& func, InterferenceGraph& ig){
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
                    IGNode& rax_node = ig.add_node(_rax, ins.type);
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
                    IGNode& rax_node = ig.add_node(_rax, ins.type);
                    rax_node.assigned = static_cast<int>(RAX);

                    b->ins.insert(it, {Operation::MOV, ins.type, _rax, ins.src1});

                    ins.src1 = VOID;
                    
                    Operand _rdx = func.get_register();
                    IGNode& rdx_node = ig.add_node(_rdx, ins.type);
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
                    IGNode& node = ig.add_node(_rcx, ins.type);
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
                            IGNode& node = ig.add_node(_param, ins.type);
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
                            IGNode& node = ig.add_node(_param, ins.type);
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
                        IGNode& node = ig.add_node(_xmm0, ins.type);
                        node.assigned = static_cast<int>(XMM0);

                        it++;
                        b->ins.insert(it, {Operation::MOV, ins.type, ins.dst, _xmm0});
                        ins.dst = _xmm0;
                    }
                    else { // mov rax->dst
                        Operand _rax = func.get_register();
                        IGNode& node = ig.add_node(_rax, ins.type);
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
                        IGNode& node = ig.add_node(_xmm0, ins.type);
                        node.assigned = static_cast<int>(XMM0);
                        b->ins.insert(it, {Operation::MOV, ins.type, _xmm0, ins.src1});
                        ins.src1 = _xmm0;
                    }
                    else { // mov return -> rax
                        Operand _rax = func.get_register();
                        IGNode& node = ig.add_node(_rax, ins.type);
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





