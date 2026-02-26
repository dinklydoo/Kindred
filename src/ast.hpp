#pragma once
#include "types.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <set>

struct Visitor;

struct ASTNode{
    Source location;
    public: 
        virtual ~ASTNode() = default;
        virtual void accept(Visitor& v) = 0;
};

struct ExpNode;
using expr_ptr = std::unique_ptr<ExpNode>;
struct ExpNode : ASTNode{
    type_ptr resolved_type;
    virtual bool is_literal() { return false; }
};

using litval = std::variant<int64_t, double, bool, char>;
struct LiteralNode : ExpNode{
    public: 
        virtual ~LiteralNode() = default;
        bool is_literal() override { return true; }
        virtual litval get_val() = 0;
};
    
struct DeclNode : ASTNode {
    public : virtual ~DeclNode() = default;
};
    
using decl_ptr = std::unique_ptr<DeclNode>;
using node_ptr = std::unique_ptr<ASTNode>;
using literal_ptr = std::unique_ptr<LiteralNode>;

struct IntLit : LiteralNode{ 
    int64_t value; 
    public: 
        void accept(Visitor& v) override;
        litval get_val() override { return value; }
};
struct FloatLit : LiteralNode{
    double value; 
    public:
        void accept(Visitor& v) override;
        litval get_val() override { return value; }
};
struct BoolLit : LiteralNode{ 
    bool value; 
    public: 
        void accept(Visitor& v) override;
        litval get_val() override { return value; }
};
struct CharLit : LiteralNode{ 
    char value; 
    public: 
        void accept(Visitor& v) override;
        litval get_val() override { return value; }
};
struct ListPatternLit : LiteralNode { 
    std::vector<std::string> patterns; 
    public:
        void accept(Visitor& v) override;
        litval get_val() override { return -1; }
};
struct StructPatternLit : LiteralNode {
    std::string name; 
    std::vector<std::string> patterns;
    public:
        void accept(Visitor& v) override;
        litval get_val() override { return -1; }
};
struct EmptyLit : LiteralNode {
    public:
        void accept(Visitor& v) override;
        litval get_val() override { return -1; }
};
struct NilLit : LiteralNode{
    public:
        void accept(Visitor& v) override;
        litval get_val() override { return -1; }
};
struct DefaultLit : LiteralNode{ 
    public:
        void accept(Visitor& v) override;
        litval get_val() override { return -1; }
};
struct ElseLit : LiteralNode{
    public:
        void accept(Visitor& v) override;
        litval get_val() override { return -1; }
};
struct EnumLit : LiteralNode{ 
    std::string elem; 
    public:
        void accept(Visitor& v) override;
        litval get_val() override { return -1; }
};

enum NominalKind {
    NOMINAL, ENUM_VAL, VAR_REF
};

// during parsing, cant tell if a value is an enum or a variable name,
// post type checking need to fix these nodes
struct NominalNode : ExpNode {
    std::string label;
    NominalKind kind = NOMINAL;
    public: virtual void accept(Visitor& v) override;
};

struct AccessNode : ExpNode {
    expr_ptr struct_expr;
    std::string field;
    std::string sn;
    public: virtual void accept(Visitor& v) override;
};

enum UnaryOp {
    MINUS, LNEG, BNOT
    // unary minus, logical negation, boolean not
};

struct UnaryNode : ExpNode{
    UnaryOp op;
    expr_ptr exp;
    public: virtual void accept(Visitor& v) override;
};

enum BinaryOp {
    ADD, SUB, MUL, DIV, POW, MOD, FLR, // arithmetic
    LAND, LOR, LXOR, LSR, LSL, // logical (binary)
    BAND, BOR, // boolean
    CGT, CLT, CGEQ, CLEQ, CEQ, CNEQ, // comparitive
    CONCAT, INDEX, // list based
    APPEND, PREPEND
};

static bool is_cmp(BinaryOp op){
    return (
        op == CGT || op == CLT ||
        op == CGEQ || op == CLEQ ||
        op == CEQ || op == CNEQ
    );
}

struct BinaryNode : ExpNode{
    BinaryOp op;
    expr_ptr l_exp;
    expr_ptr r_exp;
    public: virtual void accept(Visitor& v) override;
};

struct CallNode : ExpNode {
    expr_ptr f_exp; // nullable
    std::vector<expr_ptr> params;

    std::vector<type_ptr> ptypes;
    public: virtual void accept(Visitor& v) override;
};

struct StructNode : ExpNode {
    std::string name;
    std::vector<expr_ptr> fields;

    std::vector<type_ptr> ftypes;
    public: virtual void accept(Visitor& v) override;
};

struct Param {
    std::string name;
    type_ptr type;
    Source location;
};

// struct LambNode : ExpNode {
//     std::vector<Param> params;
//     type_ptr ret;
//     expr_ptr body;
//     public: virtual void accept(Visitor& v) override;
// };

struct ProgramNode : ExpNode {
    std::vector<decl_ptr> decl;
    expr_ptr body;
    public: virtual void accept(Visitor& v) override;
};
using prog_ptr = std::unique_ptr<ProgramNode>;

struct ReturnNode : ExpNode {
    expr_ptr rexp;
    public: virtual void accept(Visitor& v) override;
};

struct CaseBranchNode : ExpNode {
    literal_ptr pattern;
    prog_ptr body;
    bool reachable = true;
    bool pattern_type; // struct or list pattern
    public: virtual void accept(Visitor& v) override;
};

using c_branch_ptr = std::unique_ptr<CaseBranchNode>;

struct CaseNode : ExpNode {
    expr_ptr target;
    std::vector<c_branch_ptr> patterns;
    public: virtual void accept(Visitor& v) override;
};

struct GuardBranchNode : ExpNode {
    expr_ptr match;
    prog_ptr body;
    bool reachable = true;
    public: virtual void accept(Visitor& v) override;
};

using g_branch_ptr = std::unique_ptr<GuardBranchNode>;

struct GuardNode : ExpNode {
    std::vector<g_branch_ptr> branches;
    public: virtual void accept(Visitor& v) override;
};

struct ListNode : ExpNode {
    std::vector<expr_ptr> elems;
    public: virtual void accept(Visitor& v) override;
};

struct StructDecl : DeclNode{
    std::string name;
    std::vector<Field> fields;

    public: virtual void accept(Visitor& v) override;
};

struct EnumDecl : DeclNode{
    std::string name;
    std::vector<std::string> evar;
    public: virtual void accept(Visitor& v) override;
};

struct PrintNode : DeclNode {
    expr_ptr msg;
    public: virtual void accept(Visitor& v) override;
};

struct ReadNode : ExpNode {
    public: virtual void accept(Visitor& v) override;
};

struct ModuleNode : ASTNode {
    std::vector<decl_ptr> decl;
    public: virtual void accept(Visitor& v) override;
};

using module_ptr = std::unique_ptr<ModuleNode>;
using guard_ptr = std::unique_ptr<GuardNode>;
using case_ptr = std::unique_ptr<CaseNode>;
using struct_decl_ptr = std::unique_ptr<StructDecl>;
using enum_decl_ptr = std::unique_ptr<EnumDecl>;

using var = std::pair<std::string, type_ptr>;
using varset = std::set<var>;
struct FuncDecl : DeclNode{
    std::string name;
    std::vector<Param> params;
    type_ptr ret;
    type_ptr ftype;
    prog_ptr body;

    varset captures = {}; // which variables are captured from outer scopes
    public: virtual void accept(Visitor& v) override;
};

struct VarDecl : DeclNode {
    std::string name;
    type_ptr type;
    expr_ptr r_val; 
    public: virtual void accept(Visitor& v) override;
};

using var_decl_ptr = std::unique_ptr<VarDecl>;
using list_ptr = std::unique_ptr<ListNode>;
using func_decl_ptr = std::unique_ptr<FuncDecl>;
using read_ptr = std::unique_ptr<ReadNode>;
using print_ptr = std::unique_ptr<PrintNode>;
using bin_ptr = std::unique_ptr<BinaryNode>;
using un_ptr = std::unique_ptr<UnaryNode>;
using nom_ptr = std::unique_ptr<NominalNode>;
