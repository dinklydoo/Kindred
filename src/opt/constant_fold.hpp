#include "ast.hpp"
#include "visitor.hpp"

struct ConstantFolder : Visitor {
    static ConstantFolder& instance() {
        static ConstantFolder cf;
        return cf;
    }

    void constant_fold( ModuleNode& node );

    void visit( VarDecl& node) override ;
    void visit( FuncDecl& node) override ;
    void visit( EnumDecl& node) override {};
    void visit( StructDecl& node) override {};
    void visit( UnaryNode& node) override ;
    void visit( BinaryNode& node) override ;
    void visit( CallNode& node) override {};
    void visit( StructNode& node) override ;
    void visit( AccessNode& node) override ;
    void visit( NominalNode& node) override {};
    void visit( CharLit& node) override ;
    void visit( IntLit& node) override ;
    void visit( FloatLit& node) override ;
    void visit( BoolLit& node) override ;
    void visit( EmptyLit& node) override {};
    void visit( ListPatternLit& node) override {};
    void visit( NilLit& node) override {};
    void visit( StructPatternLit& node) override {};
    void visit( EnumLit& node) override {};
    void visit( DefaultLit& node) override {};
    void visit( ElseLit& node) override {};
    void visit( ReturnNode& node) override ;
    void visit( CaseNode& node) override ;
    void visit( CaseBranchNode& node) override ;
    void visit( GuardNode& node) override ;
    void visit( GuardBranchNode& node) override ;
    void visit( ListNode& node) override ;
    void visit( ProgramNode& node) override ;
    void visit( ModuleNode& node) override;
    void visit( ReadNode& node) override {};
    void visit( PrintNode& node) override {};
};