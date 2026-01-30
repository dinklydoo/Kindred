#pragma once
#include "types.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

struct Visitor;

struct Source {
    int line;
    int col;
};

struct ASTNode{
    Source location;
    public: 
        virtual ~ASTNode() = default;
        virtual void accept(Visitor& v) = 0;
};

struct ExpNode : ASTNode{
    type_ptr resolved_type;
};

struct LiteralNode : ExpNode{
    public: virtual ~LiteralNode() = default;
};
    
struct DeclNode : ASTNode {
    public : virtual ~DeclNode() = default;
};
    
using decl_ptr = std::unique_ptr<DeclNode>;
using node_ptr = std::unique_ptr<ASTNode>;
using expr_ptr = std::unique_ptr<ExpNode>;
using literal_ptr = std::unique_ptr<LiteralNode>;

struct IntLit : LiteralNode{ 
    int64_t value; 
    public: virtual void accept(Visitor& v) override;
};
struct FloatLit : LiteralNode{
    double value; 
    public: virtual void accept(Visitor& v) override;
};
struct BoolLit : LiteralNode{ 
    bool value; 
    public: virtual void accept(Visitor& v) override;
};
struct CharLit : LiteralNode{ 
    char value; 
    public: virtual void accept(Visitor& v) override;
};
struct ListLit : LiteralNode { 
    std::vector<literal_ptr> elems; 
    public: virtual void accept(Visitor& v) override;
};
struct ListPatternLit : LiteralNode { 
    std::vector<std::string> patterns; 
    public: virtual void accept(Visitor& v) override;
};
struct NilLit : LiteralNode{
    public: virtual void accept(Visitor& v) override;
};
struct DefaultLit : LiteralNode{ 
    public: virtual void accept(Visitor& v) override;
};
struct EnumLit : LiteralNode{ 
    std::string elem; 
    public: virtual void accept(Visitor& v) override;
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
};

struct BinaryNode : ExpNode{
    BinaryOp op;
    expr_ptr l_exp;
    expr_ptr r_exp;
    public: virtual void accept(Visitor& v) override;
};

struct CallNode : ExpNode {
    std::string label;
    std::vector<expr_ptr> params;
    public: virtual void accept(Visitor& v) override;
};

struct StructNode : ExpNode {
    std::string name;
    std::vector<expr_ptr> fields;
    public: virtual void accept(Visitor& v) override;
};


struct Param {
    std::string name;
    type_ptr type;
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

struct Field {
    type_ptr type;
    std::string name;
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

struct ReadNode : DeclNode {
    std::string name;
    type_ptr type;
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

struct FuncDecl : DeclNode{
    std::string name;
    std::vector<Param> params;
    type_ptr ret;
    prog_ptr body;
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
