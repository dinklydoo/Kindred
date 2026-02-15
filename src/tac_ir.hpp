#include "cstdint"
#include <string>
#include <vector>
#include <iostream>

struct Operand {
    enum Type {REG, IMM, VAR};

    Type type;
    int64_t value;
    
public:
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
    virtual ~Operand() = default;

    std::string op_str(){
        std::string str;
        switch (type){
            case (REG) : str += 'r'; break;
            case (IMM) : str += 'i'; break;
            case (VAR) : str += 'v'; break; 
        }
        str += std::to_string(value);
        return str;
    }
};

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
    CALL, PARAM,
    // mem
    LOAD, STORE, ADDR // access label pointer (for functions)
};

enum class DataType {
    EMPTY, I32, I64, F32, F64, BOOL, PTR
    , I8 // I8 for char
};

#define NULL_PTR Operand::imm(0)
#define TRUE Operand::imm(1)
#define FALSE Operand::imm(0)
struct Instruction {
    Operation op;
    DataType type;
    Operand dst;
    Operand src1;
    Operand src2;
    std::string target; // jump label

    void print_ins(){
        switch (op){
            case (Operation::ADD) : std::cout << "add"; break;
            case (Operation::SUB) : std::cout << "sub"; break;
            case (Operation::MUL) : std::cout << "mul"; break;
            case (Operation::DIV) : std::cout << "div"; break;
            case (Operation::MOD) : std::cout << "mod"; break;
            case (Operation::POW) : std::cout << "pow"; break;
            case (Operation::FLR) : std::cout << "flr"; break;
            case (Operation::AND) : std::cout << "and"; break;
            case (Operation::OR) : std::cout << "or"; break;
            case (Operation::XOR) : std::cout << "xor"; break;
            case (Operation::NEG) : std::cout << "neg"; break;
            case (Operation::NOT) : std::cout << "not"; break;
            case (Operation::LSL) : std::cout << "lsl"; break;
            case (Operation::LSR) : std::cout << "lsr"; break;
            case (Operation::CLT) : std::cout << "clt"; break;
            case (Operation::CGT) : std::cout << "cgt"; break;
            case (Operation::CLEQ) : std::cout << "cleq"; break;
            case (Operation::CGEQ) : std::cout << "cgeq"; break;
            case (Operation::CEQ) : std::cout << "ceq"; break;
            case (Operation::CNEQ) : std::cout << "cneq"; break;
            case (Operation::MOV) : std::cout << "mov"; break;
            case (Operation::CST_I32) : std::cout << "cst_i32"; break;
            case (Operation::CST_I64) : std::cout << "cst_i64"; break;
            case (Operation::CST_F32) : std::cout << "cst_f32"; break;
            case (Operation::CST_F64) : std::cout << "cst_f64"; break;
            case (Operation::JMP_IF) : std::cout << "jmp_if"; break;
            case (Operation::LOAD) : std::cout << "load"; break;
            case (Operation::STORE) : std::cout << "store"; break;
            case (Operation::PARAM) : std::cout << "param"; break;
            case (Operation::CALL) : std::cout << "call"; break;
            case (Operation::JMP) : std::cout << "jmp"; break;
            case (Operation::RET) : std::cout << "ret"; break;
            case (Operation::ADDR) : std::cout << "addr"; break;
            case (Operation::LABEL) : std::cout << target<<'\n'; return;
        }
        switch (op){
            case (Operation::ADD) : case (Operation::SUB) : case (Operation::MUL) :
            case (Operation::DIV) : case (Operation::MOD) : case (Operation::POW) :
            case (Operation::FLR) : case (Operation::AND) : case (Operation::OR) : 
            case (Operation::XOR) : case (Operation::LSL) : case (Operation::LSR) :
            case (Operation::CLT) : case (Operation::CGT) : case (Operation::CLEQ) :
            case (Operation::CGEQ) : case (Operation::CEQ) : case (Operation::CNEQ) :
            case (Operation::LOAD) :
            case (Operation::STORE) : std::cout<<' '<<dst.op_str()<<' '<<src1.op_str()<<' '<<src2.op_str()<<'\n'; break;
            case (Operation::MOV) : case (Operation::NEG) : case (Operation::NOT) : 
            case (Operation::CST_I32) : case (Operation::CST_I64) : case (Operation::CST_F32) : 
            case (Operation::CALL) :
            case (Operation::CST_F64) : std::cout<<' '<<dst.op_str()<<' '<<src1.op_str()<<'\n'; break;
            case (Operation::JMP_IF) : std::cout<<' '<<src1.op_str()<<' '<<target<<'\n'; break;
            case (Operation::RET) :
            case (Operation::PARAM) : std::cout<<' '<<src1.op_str()<<'\n'; break;
            case (Operation::JMP) : std::cout<<' '<<target<<'\n';
            case (Operation::ADDR) : std::cout<<' '<<dst.op_str()<<' '<<target<<'\n'; break;
            default: return;
        }
    }
};

struct Block {
    std::vector<Instruction> ins;  
};

struct FunctionIR {
    std::vector<Block> blocks;

    void print_ir(){
        for (Block& b : blocks){
            for (Instruction& ins : b.ins){
                ins.print_ins();
            }
        }
    }
};
