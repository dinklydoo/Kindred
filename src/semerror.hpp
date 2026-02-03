#pragma once
#include "ast.hpp"

struct SemanticError{
    enum class Kind{
        TYPE, UNDEF, REDEF, REF, ACCESS, ARG, MAIN, INEXHAUSTIVE
    };
    Kind kind;
    Source location;
    std::string message;
};

struct SemanticWarning{
    enum class Kind{
        UNREACHABLE, POSTDECL
    };
    Kind kind;
    Source location;
    std::string message;
};

// todo : maybe use a sorted construct by location
struct ErrorList {
    std::vector<SemanticError> errors;

    void push_error(std::string msg, SemanticError::Kind kind, Source& loc);

    void type_error(std::string message, ExpNode& node);
    void redef_error(std::string label, type_ptr def, Source& loc);
    void undef_error(std::string message, ExpNode& node);
    void reference_error(std::string label, type_ptr def, ExpNode& node);
    void access_error(std::string message, ExpNode& node);
    void arg_error(std::string message, ExpNode& node);
    void inexh_error(std::string message, ExpNode& node);
    void main_error(Source& loc);

    void report_errors();
};

struct WarningList {
    std::vector<SemanticWarning> warnings;

    void push_warning(std::string msg, SemanticWarning::Kind kind, Source& loc);

    void unreach_warning(std::string msg, Source& loc);
    void postdecl_warning(std::string name, Type::Kind k, DeclNode& node);

    void report_warnings();
};

std::string type_to_string(type_ptr type);
std::string kind_to_string(Type::Kind kind);