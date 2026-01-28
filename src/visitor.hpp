#include "ast.hpp"

struct Visitor {
    virtual void visit( IntLit& node);
    virtual void visit( FloatLit& node);
    virtual void visit( BoolLit& node);
    virtual void visit( CharLit& node);
    virtual void visit( ListLit& node);
    virtual void visit( ListPatternLit& node);
    virtual void visit( NilLit& node);
    virtual void visit( DefaultLit& node);
    virtual void visit( EnumLit& node);

    virtual void visit( AccessNode& node);
    virtual void visit( VarDecl& node);
    virtual void visit( FuncDecl& node);
    virtual void visit( EnumDecl& node);
    virtual void visit( StructDecl& node);
    virtual void visit( UnaryNode& node);
    virtual void visit( BinaryNode& node);
    virtual void visit( StructNode& node);
    virtual void visit( CallNode& node);
    virtual void visit( NominalNode& node);
    virtual void visit( ReturnNode& node);
    virtual void visit( CaseNode& node);
    virtual void visit( CaseBranchNode& node);
    virtual void visit( GuardNode& node);
    virtual void visit( GuardBranchNode& node);
    virtual void visit( ListNode& node);
    virtual void visit( ProgramNode& node);
    virtual void visit( ModuleNode& node);
    virtual void visit( ReadNode& node);
    virtual void visit( PrintNode& node);
};