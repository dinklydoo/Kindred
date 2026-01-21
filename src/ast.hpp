#include "types.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

struct Source {
    int line;
    int col;
};

struct ASTNode{
    Source location;
    public: virtual ~ASTNode() = default;
};

struct ExpNode : ASTNode{ };

using expr_ptr = std::unique_ptr<ExpNode>;

struct LiteralNode : ExpNode{
    public: virtual ~LiteralNode() = default;
};

using literal_ptr = std::unique_ptr<LiteralNode>;

struct IntLit : LiteralNode{ int32_t value; };
struct LongLit : LiteralNode{ int64_t value; };
struct FloatLit : LiteralNode{ float value; };
struct DoubleLit : LiteralNode{ double value; };
struct BoolLit : LiteralNode{ bool value; };
struct CharLit : LiteralNode{ char value; };
struct ListLit : LiteralNode { std::vector<literal_ptr> elems; };
struct ListPatternLit : LiteralNode { std::vector<std::string> patterns; };
struct NilLit : LiteralNode{ };
struct DefaultLit : LiteralNode{ };
struct EnumLit : LiteralNode{ std::string elem; };

enum UnaryOp {
    MINUS, LNEG, BNOT
    // unary minus, logical negation, boolean not
};

// during parsing, cant tell if a value is an enum or a variable name,
// post type checking need to fix these nodes
struct NominalNode : ExpNode {
    std::string label;
};

// field label for struct access
struct FieldNode : ExpNode {
    std::string field;
};

struct UnaryNode : ExpNode{
    UnaryOp op;
    expr_ptr exp;
};

enum BinaryOp {
    ADD, SUB, MUL, DIV, POW, MOD, FLR, // arithmetic
    LAND, LOR, LXOR, LSR, LSL, // logical (binary)
    BAND, BOR, // boolean
    CGT, CLT, CGEQ, CLEQ, CEQ, CNEQ, // comparitive
    CONCAT, INDEX, // list based
    ASSIGN, // var decl
    ACCESS // structure based
};

struct BinaryNode : ExpNode{
    BinaryOp op;
    expr_ptr l_exp;
    expr_ptr r_exp;
};

/* Node for structs/function calls that can share syntax */
/*
    Function calls as:
        foo(arg1, arg2)
    
    Structure constructors as:
        struct(field, field2)

    Both tokenized as LABEL LBRA expr_list RBRA
    Specialize node types later in semantic/type checking
*/
struct ParamNode : ExpNode{
    std::string label;
    std::vector<expr_ptr> params;
};

struct FunCallNode : ExpNode{
    std::string func;
    std::vector<expr_ptr> args;
};

struct Param {
    std::string name;
    type_ptr type;
};

struct LambNode : ExpNode {
    std::vector<Param> params;
    type_ptr ret;
    expr_ptr body;
    //explicit LambNode(std::vector<Param> params, type_ptr type, expr_ptr body): params(std::move(params)), type(type), body(std::move(body)) {}
};

struct CaseBranchNode {
    literal_ptr pattern;
    expr_ptr body;
};

using c_branch_ptr = std::unique_ptr<CaseBranchNode>;

struct CaseNode : ExpNode {
    expr_ptr target;
    std::vector<c_branch_ptr> patterns;
};

struct GuardBranchNode {
    expr_ptr match;
    expr_ptr body;
};

using g_branch_ptr = std::unique_ptr<GuardBranchNode>;

struct GuardNode : ExpNode {
    expr_ptr target;
    std::vector<g_branch_ptr> branches;
};

struct ListNode : ExpNode {
    std::vector<expr_ptr> elems;
};

struct StructNode : ExpNode {
    std::string name;
    std::vector<expr_ptr> fields;
};

struct DeclNode : ASTNode {
    public : virtual ~DeclNode() = default;
};

using decl_ptr = std::unique_ptr<DeclNode>;

struct VarNode : ExpNode{
    std::string label;
    type_ptr type; // unsure if needed if type checking done prior
};

struct Field {
    type_ptr type;
    std::string name;
};

struct StructDecl : DeclNode{
    std::string name;
    std::vector<Field> fields;
};

struct EnumDecl : DeclNode{
    std::string name;
    std::vector<std::string> evar;
};

struct PrintNode : ExpNode {
    expr_ptr msg;
};

struct ReadNode : ExpNode {
    expr_ptr var;
};

struct ProgramNode : ExpNode {
    std::vector<expr_ptr> program;
    expr_ptr ret;
};

struct ModuleNode : ASTNode {
    std::vector<decl_ptr> decl;
};

using module_ptr = std::unique_ptr<ModuleNode>;
using prog_ptr = std::unique_ptr<ProgramNode>;
using guard_ptr = std::unique_ptr<GuardNode>;
using case_ptr = std::unique_ptr<CaseNode>;
using struct_decl_ptr = std::unique_ptr<StructDecl>;
using enum_decl_ptr = std::unique_ptr<EnumDecl>;

struct FuncDecl : DeclNode{
    std::string name;
    std::vector<Param> params;
    type_ptr ret;
    prog_ptr body;
};

using list_ptr = std::unique_ptr<ListNode>;
using var_ptr = std::unique_ptr<VarNode>;
using func_decl_ptr = std::unique_ptr<FuncDecl>;
using read_ptr = std::unique_ptr<ReadNode>;
using print_ptr = std::unique_ptr<PrintNode>;
using bin_ptr = std::unique_ptr<BinaryNode>;
using un_ptr = std::unique_ptr<UnaryNode>;
using nom_ptr = std::unique_ptr<NominalNode>;
