#pragma once
#include <string>
#include <variant>

enum class TokenType{
    ASSGN,
    ADD, MUL, DIV, MOD, FLR, POW,
    LAND, LOR, LXOR, LNOT, LNEG, LSR, LSL, 
    CGT, CGEQ, CLEQ, CEQ, CNEQ, 
    CONCAT, CASE, OF, ARROW, NIL, EMPTY,
    MAIN,
    DEFAULT, DECLARE, INCLUDE,
    FUNC, TSEP, 
    LBRA, RBRA, SQ_LBRA, SQ_RBRA,
    LAMB, 
    T_BOOL, T_CHAR, 
    T_INT, T_LONG, 
    T_FLOAT, T_DOUBLE, 
    INT, FLOAT, STRING,
    STRUCT, ENUM,
    READ, PRINT
    TRUE, FALSE, 
    DOT, COMMA,
    LABEL, 
    EOF
};

using TokenValue = std::variant<
    std::monostate, long, double, bool, std::string, char>;

struct Token {
    TokenType type;
    TokenValue value;
};

// make a token with non value association
Token make_token(TokenType type){
    return Token {
        type, std::monostate{}
    }
};

// overload : make a token with a value association
Token make_token(TokenType type, TokenValue value){
    return Token {
        type, value
    };
}
