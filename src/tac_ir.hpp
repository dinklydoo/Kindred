#pragma once
#include "cstdint"
#include <fstream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <set>
#include <list>
#include <iostream>

enum class DataType {
    EMPTY, I32, I64, F32, F64, BOOL, PTR
    , I8 // I8 for char
};

enum RType { GP, FP };

struct Operand {
    enum Type {
        REG, // virtual register
        IMM, // immediate value
        VAR, // virtual register (name binded - variables/functions)
        EMP,

        GPR, // general purpose register
        FPR, // floating point register
        RSP, // generic stack pointer
        RBP // generic base pointer
    };

    Type type;
    DataType kind = DataType::EMPTY;
    int64_t value;
    
public:
    bool operator==(const Operand& other) const {
        return (other.type == type && other.value == value && kind == other.kind);    
    }
    bool is_register(){ return type == REG || type == VAR;}

    struct OperandHash {
        std::size_t operator()(const Operand& op) const {
            std::size_t seed = 0;

            seed ^= std::hash<int>{}(static_cast<int>(op.type))
                    + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            seed ^= std::hash<int>{}(static_cast<int>(op.kind))
                    + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            seed ^= std::hash<int64_t>{}(op.value)
                    + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            return seed;
        }
    };

    static Operand reg(int64_t rc){
        Operand temp;
        temp.type = REG;
        temp.value = rc;
        return temp;
    }
    static Operand imm(int64_t val){
        Operand temp;
        temp.type = IMM;
        temp.value = val;
        return temp;
    }
    static Operand var(int64_t id){
        // convert var names to id values
        Operand temp;
        temp.type = VAR;
        temp.value = id;
        return temp;
    }
    static Operand empty(){
        Operand temp;
        temp.type = EMP;
        temp.value = 0;
        return temp;
    }

    /* ==================================================================================================================

                REG ALLOC

    ================================================================================================================== */ 
    static Operand rbp(int64_t offset){
        Operand temp;
        temp.type = RBP;
        temp.value = offset;
        return temp;
    }
    static Operand rsp(int64_t offset){
        Operand temp;
        temp.type = RSP;
        temp.value = offset;
        return temp;
    }
    static Operand gpr(int64_t id){
        Operand temp;
        temp.type = GPR;
        temp.value = id;
        return temp;
    }
    static Operand fpr(int64_t id){
        Operand temp;
        temp.type = FPR;
        temp.value = id;
        return temp;
    }

    virtual ~Operand() = default;

    std::string op_str(){
        std::string str;
        switch (type){
            case (REG) : str += 'r'; break;
            case (IMM) : str += 'i'; break;
            case (VAR) : str += 'v'; break; 
            case (RBP) : str += "rbp"; break; 
            case (RSP) : str += "rsp"; break;
            case (GPR) : str += "gpr"; break;
            case (FPR) : str += "fpr"; break;
            case (EMP) : return "";
        }
        if (type == RBP || type == RSP){ 
            if (value) str = '['+str;
            else return str;

            if (value > 0) str += '+';
            str += std::to_string(value);
            str += ']';
        }
        else str += std::to_string(value);
        return str;
    }
};
#define VOID Operand::empty()

enum class Operation {
    // arith
    ADD, SUB, MUL, DIV, MOD, POW, FLR,
    // logical/bitwise
    AND, OR, XOR, NEG, NOT,
    LSL, LSR,
    // comparative
    CLT, CGT, CLEQ, CGEQ, CEQ, CNEQ,
    // data movement
    MOV, CST_I32, CST_I64, CST_F32, CST_F64,
    // control flow
    JMP, JMP_IF, RET, LABEL,
    // functional
    CALL, PARAM, LOCAL, CALL_EXT, 
    // mem
    LOAD, STORE, ADDR, // access label pointer (for closures)
    
    BEGIN_FUNC, BEGIN_CALL // helper labels
};

static bool is_fp(DataType op){
    return (op == DataType::F32 || op == DataType::F64);
}

static bool cmp_op(Operation op){
    return (
        op == Operation::CEQ || 
        op == Operation::CNEQ || 
        op == Operation::CLEQ || 
        op == Operation::CGEQ || 
        op == Operation::CLT || 
        op == Operation::CGT
    );
}

static RType dtype_to_rtype(DataType dtype){
    if (dtype == DataType::F32 || dtype == DataType::F64) return FP;
    return GP;
}

#define NULL_PTR Operand::imm(0)
#define TRUE Operand::imm(1)
#define FALSE Operand::imm(0)
struct Instruction {
    Operation op;
    DataType type;
    Operand dst = VOID;
    Operand src1 = VOID;
    Operand src2 = VOID;
    std::string target; // jump label

    bool is_move(){
    if (op == Operation::MOV) return true;

    if (op == Operation::CST_I32 || op == Operation::CST_I64) return true;
    switch (op) {
        case (Operation::MOV) :
        case (Operation::CST_I32) :
        case (Operation::CST_I64) : return true;
        case (Operation::CST_F64) : return (type == DataType::F32);
        default : return false; // CST_F32 will always move from a GPR to FPR
    }
}

    void print_ins(std::ostream& fd){
        switch (op){
            case (Operation::ADD) : fd << "add"; break;
            case (Operation::SUB) : fd << "sub"; break;
            case (Operation::MUL) : fd << "mul"; break;
            case (Operation::DIV) : fd << "div"; break;
            case (Operation::MOD) : fd << "mod"; break;
            case (Operation::POW) : fd << "pow"; break;
            case (Operation::FLR) : fd << "flr"; break;
            case (Operation::AND) : fd << "and"; break;
            case (Operation::OR) : fd << "or"; break;
            case (Operation::XOR) : fd << "xor"; break;
            case (Operation::NEG) : fd << "neg"; break;
            case (Operation::NOT) : fd << "not"; break;
            case (Operation::LSL) : fd << "lsl"; break;
            case (Operation::LSR) : fd << "lsr"; break;
            case (Operation::CLT) : fd << "clt"; break;
            case (Operation::CGT) : fd << "cgt"; break;
            case (Operation::CLEQ) : fd << "cleq"; break;
            case (Operation::CGEQ) : fd << "cgeq"; break;
            case (Operation::CEQ) : fd << "ceq"; break;
            case (Operation::CNEQ) : fd << "cneq"; break;
            case (Operation::MOV) : fd << "mov"; break;
            case (Operation::CST_I32) : fd << "cst_i32"; break;
            case (Operation::CST_I64) : fd << "cst_i64"; break;
            case (Operation::CST_F32) : fd << "cst_f32"; break;
            case (Operation::CST_F64) : fd << "cst_f64"; break;
            case (Operation::JMP_IF) : fd << "jmp_if"; break;
            case (Operation::LOAD) : fd << "load"; break;
            case (Operation::STORE) : fd << "store"; break;
            case (Operation::LOCAL) : fd << "local"; break;
            case (Operation::PARAM) : fd << "param"; break;
            case (Operation::CALL_EXT) :
            case (Operation::CALL) : fd << "call"; break;
            case (Operation::JMP) : fd << "jmp"; break;
            case (Operation::RET) : fd << "ret"; break;
            case (Operation::ADDR) : fd << "addr"; break;
            case (Operation::LABEL) : fd << target<<'\n'; return;
            case (Operation::BEGIN_FUNC) : fd << "begin func:\n"; return;
            default : return;
        }
        switch (op){
            case (Operation::ADD) : case (Operation::SUB) : case (Operation::MUL) :
            case (Operation::DIV) : case (Operation::MOD) : case (Operation::POW) :
            case (Operation::AND) : case (Operation::OR) : case (Operation::XOR) : 
            case (Operation::LSL) : case (Operation::LSR) : case (Operation::CLT) : 
            case (Operation::CGT) : case (Operation::CLEQ) : case (Operation::CGEQ) : 
            case (Operation::CEQ) : case (Operation::CNEQ) : case (Operation::LOAD) :
            case (Operation::STORE) : fd<<' '<<dst.op_str()<<' '<<src1.op_str()<<' '<<src2.op_str()<<'\n'; break;
            case (Operation::MOV) : case (Operation::NEG) : case (Operation::NOT) : 
            case (Operation::CST_I32) : case (Operation::CST_I64) : case (Operation::CST_F32) : 
            case (Operation::CALL) : case (Operation::FLR) :
            case (Operation::CST_F64) : fd<<' '<<dst.op_str()<<' '<<src1.op_str()<<'\n'; break;
            case (Operation::JMP_IF) : fd<<' '<<src1.op_str()<<' '<<target<<'\n'; break;
            case (Operation::RET) :
            case (Operation::LOCAL) :
            case (Operation::PARAM) : fd<<' '<<src1.op_str()<<'\n'; break;
            case (Operation::JMP) : fd<<' '<<target<<'\n'; break;
            case (Operation::CALL_EXT) :
            case (Operation::ADDR) : fd<<' '<<dst.op_str()<<' '<<target<<'\n'; break;
            default: return;
        }
    }
};



using virtual_var = std::pair<Operand, RType>;
struct VarHash {
    std::size_t operator()(const virtual_var& var) const {
        std::size_t seed = 0;

        seed ^= std::hash<int>{}(static_cast<int>(var.second))
                + 0x9e3779b9 + (seed << 6) + (seed >> 2);

        seed ^= Operand::OperandHash{}(var.first)
                + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};
using virtual_varset = std::unordered_set<virtual_var, VarHash>;
using opset = std::unordered_set<Operand, Operand::OperandHash>;
struct Block {
    std::string label;
    std::list<Instruction> ins;

    std::set<Block*> out_edge;
    std::set<Block*> in_edge;

    virtual_varset use, def;
    virtual_varset live_in, live_out;
};

using blockptr = std::unique_ptr<Block>;
struct FunctionIR {
    std::string name;
    std::vector<blockptr> blocks;

    int spill_offset = 0;
    int reg_count = 0;
    bool is_static = false;

    Operand get_register(){ return Operand::reg(reg_count++); }

    void print_ir(std::ostream& fd){
        for (auto& b : blocks){
            for (Instruction& ins : b->ins){
                ins.print_ins(fd);
            }
        }
    }
};

static void print_ir(std::vector<FunctionIR>& program){
    for (FunctionIR& ir : program){
        std::cout << ir.name << ":\n";

        ir.print_ir(std::cout);
        std::cout << '\n';
    }
}

static void write_ir(std::vector<FunctionIR>& program){
    std::string path = "./.aux/ir_representation.txt";
    std::ofstream trunc_ir(path, std::ios::trunc);
    trunc_ir.close(); // truncate
    std::ofstream ir_file(path, std::ios::app);
    for (FunctionIR& ir : program){
        ir_file << ir.name << ":\n";
        ir.print_ir(ir_file);
        ir_file << '\n';
    }
}

static void write_func(FunctionIR& program){
    std::string path = "./.aux/ir_"+program.name+".txt";
    std::ofstream trunc_ir(path, std::ios::trunc);
    trunc_ir.close(); // truncate
    std::ofstream ir_file(path, std::ios::app);
    ir_file << program.name << ":\n";
    program.print_ir(ir_file);
    ir_file << '\n';
}