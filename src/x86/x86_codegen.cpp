#include "x86_codegen.hpp"
#include "tac_ir.hpp"
#include "x86/x86_regalloc.hpp"
#include <fstream>
#include <string>

void X86_CodeGen::write_header(){
    std::ofstream sfile(path, std::ios::trunc);
    sfile.close();
    sfile.open(path, std::ios::app);

    std::ifstream hfile("./.aux/static_data");
    sfile << hfile.rdbuf();
    hfile.close();
}

void X86_CodeGen::write_func(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins) write_ins(ins);
    }
    std::ofstream sfile(path, std::ios::app);
    sfile << '\n';
}

std::string X86_CodeGen::reg_string(Operand op, DataType type){
    std::string str;
    switch (op.type){
        case (Operand::IMM) : str="$"+std::to_string(op.value); break;
        case (Operand::RBP) : 
        case (Operand::RSP) : {
            if (op.type == Operand::RSP) str = "%rsp";
            else str = "%rbp";

            break;
        }
        case (Operand::GPR) : str='%'+x86_gpr_string(static_cast<GPReg>(op.value), type); break;
        case (Operand::FPR) : str='%'+x86_fpr_string(static_cast<FPReg>(op.value)); break;
        default : break;
    }
    return str;
}

void X86_CodeGen::write_ins(Instruction& ins){
    std::ofstream sfile(path, std::ios::app);
    switch (ins.op){
        // jump label is type independent
        case (Operation::LABEL) : 
            sfile<<ins.target<<'\n'; return;
        case (Operation::RET) : 
            sfile<<"ret"<<'\n'; return;
        case (Operation::CALL) : {
            if (ins.src1.is_register()){ // call a closure
                sfile<<"call *"<<reg_string(ins.src1, DataType::PTR)<<'\n';
                break;
            }
        }
        case (Operation::CALL_EXT) :
            sfile<<"call "<<ins.target<<'\n'; return;
        // helper instructions no effect on codegen
        case (Operation::BEGIN_FUNC) :
        case (Operation::BEGIN_CALL) :
        case (Operation::PARAM) :
        case (Operation::LOCAL) : return;
        default : break;
    }   
    if (!is_fp(ins.type)) write_gp_ins(ins);
    else write_fp_ins(ins);
}

std::string ins_suffix(DataType type){
    switch (type){
        case (DataType::BOOL) : // bool use byte registers
        case (DataType::I8) : return "b";
        case (DataType::I32) : return "l";
        case (DataType::I64) : return "q";
        case (DataType::F32) : return "ss";
        case (DataType::F64) : return "sd";
        default : return "";
    }
}

void X86_CodeGen::write_gp_ins(Instruction& ins){
    std::ofstream sfile(path, std::ios::app);
    DataType type = ins.type;

    std::string suf = ins_suffix(type);
    switch (ins.op) {
        case (Operation::ADD) : 
        case (Operation::SUB) : 
        case (Operation::MUL) :
        case (Operation::XOR) :
        {
            std::string op;
            if (ins.op == Operation::ADD) op = "add";
            if (ins.op == Operation::SUB) op = "sub";
            if (ins.op == Operation::MUL) op = "imul";
            if (ins.op == Operation::XOR) op = "xor";

            op += suf;

            // mov first operand to dst eg.) movq $5, %rax
            if (ins.dst != ins.src1) 
                sfile<<"mov"+suf+" "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, type)<<'\n';
            sfile << op+" "+reg_string(ins.src2, type)+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::DIV) :
        case (Operation::FLR) :
        case (Operation::MOD) :
        {
            if (ins.type == DataType::I32) sfile <<"cdq\n";
            else sfile << "cqo\n";
            sfile<<"idiv"+ins_suffix(type)+", "+reg_string(ins.src2, type)<<'\n';
            break;
        }
        case (Operation::NEG) : 
        {
            // MIGHT ACTUALLY WANT TO DO THIS PROPERLY (IE IGNORE HI-BITS) -- might add to math lib
            int64_t mask;
            if (type == DataType::I8) mask = 0xFFULL;
            if (type == DataType::I32) mask = 0xFFFFFFFFULL;
            if (type == DataType::I64) mask = 0xFFFFFFFFFFFFFFFFULL;
            sfile<<"xor"+suf+' '+reg_string(Operand::imm(mask), type)+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::NOT) :
        {
            sfile<<"xorb "+reg_string(Operand::imm(1), type)+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }        
        case (Operation::LSL) :
        case (Operation::LSR) : {
            std::string op;
            if (ins.op == Operation::LSL) op = "sal";
            else op = "sar";
            sfile<<op+suf+' '+reg_string(ins.src2, type)+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::MOV) : {
            sfile<<"mov"+suf+' '+reg_string(ins.src1, type)+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::CST_F64) : {
            if (type == DataType::I8) sfile<<"movsbq "+reg_string(ins.src1, type)+", "+reg_string(ins.src1, DataType::I64)<<'\n';
            if (type == DataType::I32) sfile<<"movslq "+reg_string(ins.src1, type)+", "+reg_string(ins.src1, DataType::I64)<<'\n';

            sfile<<"cvtsi2sdq "+reg_string(ins.src1, DataType::I64)+", "+reg_string(ins.dst, DataType::F64)<<'\n';
        }
        case (Operation::CST_F32) : {
            if (type == DataType::I8) sfile<<"movsbl "+reg_string(ins.src1, type)+", "+reg_string(ins.src1, DataType::I32)<<'\n';

            if (type == DataType::I64)
                sfile<<"cvtsi2ssq "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, DataType::F32)<<'\n';
            else
                sfile<<"cvtsi2ssl "+reg_string(ins.src1, DataType::I32)+", "+reg_string(ins.dst, DataType::F32)<<'\n';
            break;
        }
        case (Operation::CST_I32) : {
            sfile<<"movsbl "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, DataType::I32)<<'\n';
            break;
        }
        case (Operation::CST_I64) : {
            if (type == DataType::I8) 
                sfile<<"movsbq "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, DataType::I64)<<'\n';
            else 
                sfile<<"movslq "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, DataType::I64)<<'\n';
            break;
        }
        case (Operation::CLT) :
        case (Operation::CGT) :
        case (Operation::CLEQ) :
        case (Operation::CGEQ) :
        case (Operation::CEQ) :
        case (Operation::CNEQ) :
        {
            if (ins.dst == VOID){
                jump_flag = ins.op;
                break; // only sets flag
            }
            // compare instruction needs floating point check
            sfile<<"cmp"+suf+" "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, type)<<'\n';
            std::string op;
            switch (ins.op){
                case (Operation::CLT) : op = "setl"; break;
                case (Operation::CGT) : op = "setg"; break;
                case (Operation::CLEQ) : op = "setle"; break;
                case (Operation::CGEQ) : op = "setge"; break;
                case (Operation::CEQ) : op = "sete"; break;
                case (Operation::CNEQ) : op = "setne"; break;
                default : break;
            }
            sfile<<op+" "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::JMP_IF) :
        {
            if (ins.src1 == VOID){ // look at flag
                std::string jp_flag;
                switch (jump_flag){
                    case (Operation::CLT) : jp_flag="l"; break;
                    case (Operation::CGT) : jp_flag="g"; break;
                    case (Operation::CLEQ) : jp_flag="le"; break;
                    case (Operation::CGEQ) : jp_flag="ge"; break;
                    case (Operation::CEQ) : jp_flag="e"; break;
                    case (Operation::CNEQ) : jp_flag="ne"; break;
                    default : break;
                }
                sfile<<"j"+jp_flag+" "+ins.target<<'\n';
                break;
            }
            // dependent on ext register -> test first
            sfile<<"test"+suf+" "+reg_string(ins.src1, type)+", "+reg_string(ins.src1, type)<<'\n';
            sfile<<"jnz "+ins.target<<'\n';
            break;
        }
        case (Operation::JMP) : {
            sfile<<"jmp "+ins.target<<'\n';
            break;
        }
        case (Operation::LOAD) : {
            std::string src = '('+reg_string(ins.src1, type)+')';
            if (ins.src1.type == Operand::RBP || ins.src1.type == Operand::RSP){
                if (ins.src1.value) src = std::to_string(ins.src1.value)+src;
            }
            sfile<<"mov"+suf+" "+src+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::STORE) : {
            std::string dst = '('+reg_string(ins.dst, type)+')';
            if (ins.dst.type == Operand::RBP || ins.dst.type == Operand::RSP){
                if (ins.dst.value) dst = std::to_string(ins.dst.value)+dst;
            }
            sfile<<"mov"+suf+" "+reg_string(ins.src1, type)+", "+dst<<'\n';
            break;
        }
        case (Operation::ADDR) : { // addr with pointer context -> closure
            sfile<<"leaq "+ins.target+"(%rip), "+reg_string(ins.dst, DataType::PTR)<<'\n';
            break;
        }
        default : return;
    }

}

void X86_CodeGen::write_fp_ins(Instruction& ins){
    std::ofstream sfile(path, std::ios::app);
    std::string suf = ins_suffix(ins.type);
    DataType type = ins.type;
    switch (ins.op) {
        case (Operation::MUL) :
        case (Operation::DIV) :
        case (Operation::ADD) :
        case (Operation::SUB) : {
            std::string op;
            switch (ins.op){
                case (Operation::MUL) : op = "mul"; break;
                case (Operation::DIV) : op = "div"; break;
                case (Operation::ADD) : op = "add"; break;
                case (Operation::SUB) : op = "sub"; break;
                default : break;
            }
            if (ins.src1 != ins.dst)
                sfile<<"mov"+suf+" "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, type)<<'\n';
            sfile<<op+suf+" "+reg_string(ins.src2, type)+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::FLR) : { // might push this to x86_lower with precolour (bandaid fix for now)
            if (ins.src1 != ins.dst)
                sfile<<"mov"+suf+" "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, type)<<'\n';
            sfile<<"div"+suf+" "+reg_string(ins.src2, type)+", "+reg_string(ins.dst, type)<<'\n';
            sfile<<"cvt"+suf+"2siq "+reg_string(ins.dst, type)+", %r11"<<'\n';
            sfile<<"cvtsi2"+suf+"q %r11, "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::MOV) : {
            sfile<<"mov"+suf+" "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::CST_F64) : {
            sfile<<"cvtss2sd "+reg_string(ins.src1, type)+", "+reg_string(ins.dst, type)<<'\n';
            break;
        }
        case (Operation::LOAD) : {

            break;
        }
        case (Operation::STORE) : {

            break;
        }
        case (Operation::ADDR) : { // floating point address -> static value

            break;
        }
        default : return;
    }
}
