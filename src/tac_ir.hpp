#include "cstdint"
#include <vector>

struct Operand {
    enum Type {REG, IMM, VAR};

    Type type;
    int64_t value;

private:
    static int reg_count;
    Operand(Type type, int64_t val) : type(type), value(val) {};

public:
    Operand reg(){
        if (!reg_count) reg_count = 0;
        return Operand{ REG, reg_count++};
    }
    Operand imm(int64_t val){
        return Operand{IMM, val};
    }
    Operand var(int64_t id){
        // convert var names to id values
        return Operand{VAR, id};
    }
    virtual ~Operand() = default;
};

enum class Operation {
    // arith
    ADD, SUB, MUL, DIV, MOD,
    // logical/bitwise
    AND, OR, XOR, NEG,
    LSL, LSR,
    // comparative
    CLT, CGT, CLEQ, CGEQ, CEQ, CNEQ,
    // data movement
    MOV, CST_INT, CST_LONG, CST_FLOAT, CST_DOUBLE,
    // control flow
    JMP, JMP_IF, RET, LABEL,
    // functional
    CALL, PARAM,
    // mem
    LOAD, STORE
};

struct Instruction {
    Operation op;
    Operand dst;
    Operand src1;
    Operand src2;
    int64_t target;
};

struct Block {
    std::vector<Instruction> ins;
    
};