#pragma once
#include "semerror.hpp"
#include "visitor.hpp"
#include "ast.hpp"
#include <memory>
#include <unordered_set>
#include <stack>

namespace fc {

struct ExBlock { 
    bool ex = false; //exhausted flag
    bool contained = false;// pattern seen flag
    Type::Kind kind;
    virtual bool exhausted() { return ex; }
};

struct ListExBlock : ExBlock {
    bool e_case = false; // empty case
    bool s_case = false; // singular case

    int subsumes = -1; // minimum length >= 1 seen

    bool exhausted() override {
        return (ex || (e_case && s_case));
    }

    ListExBlock() { kind = Type::Kind::List; }
};
struct EnumExBlock : ExBlock {
    std::unordered_set<std::string> rem;

    bool exhausted() override {
        return (ex || rem.empty());
    }

    EnumExBlock() { kind = Type::Kind::Enum; }
};
struct BoolExBlock : ExBlock {
    bool t_case = false; // true case
    bool f_case = false; // false case

    bool exhausted() override {
        return (ex || (t_case && f_case));
    }

    BoolExBlock() {kind = Type::Kind::Bool; }
};
struct StructExBlock : ExBlock {
    std::unordered_set<std::vector<bool>> seen;
    bool nil_case;
    bool full_case;

    bool exhausted() override {
        return (ex || (nil_case && full_case));
    }

    StructExBlock() {kind = Type::Kind::Struct; }
};
template<typename T>
struct ValExBlock : ExBlock {
    std::unordered_set<T> seen;
};

using exb_ptr = std::unique_ptr<ExBlock>;
class FlowStack {
    std::stack<exb_ptr> stack;

public:
    void enter_branch(exb_ptr block){ stack.push(std::move(block)); }
    void exit_branch(){ stack.pop(); }

    exb_ptr& get_top(){ 
        return stack.top(); 
    };
};

using pattern_lit = std::variant<char, int32_t, int64_t, float, double>;

struct FlowChecker : Visitor {
    static FlowChecker& instance() {
        static FlowChecker fc;
        return fc;
    }
    // using shared instance of types
    TypeSystem& type_s = TypeSystem::instance();

    bool main_defined = false;
    FlowStack blocks;

    ErrorList errors;
    WarningList warnings;

    void flowcheck( ModuleNode& node);

    void add_pattern(ExBlock&, type_ptr, pattern_lit);

    void visit( VarDecl& node) override {};
    void visit( FuncDecl& node) override;
    void visit( EnumDecl& node) override;
    void visit( StructDecl& node) override;
    void visit( UnaryNode& node) override {};
    void visit( BinaryNode& node) override {};
    void visit( CallNode& node) override {};
    void visit( StructNode& node) override {};
    void visit( AccessNode& node) override {};
    void visit( NominalNode& node) override {};
    void visit( CharLit& node) override;
    void visit( IntLit& node) override;
    void visit( FloatLit& node) override;
    void visit( BoolLit& node) override;
    void visit( ListPatternLit& node) override;
    void visit( StructPatternLit& node) override;
    void visit( EnumLit& node) override;
    void visit( DefaultLit& node) override;
    void visit( ElseLit& node) override;
    void visit( NilLit& node) override;
    void visit( EmptyLit& node) override;
    void visit( ReturnNode& node) override {};
    void visit( CaseNode& node) override;
    void visit( CaseBranchNode& node) override;
    void visit( GuardNode& node) override;
    void visit( GuardBranchNode& node) override;
    void visit( ListNode& node) override {};
    void visit( ProgramNode& node) override;
    void visit( ModuleNode& node) override;
    void visit( ReadNode& node) override {};
    void visit( PrintNode& node) override {};
};

}