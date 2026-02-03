#pragma once
#include "ast.hpp"

struct Visitor {
    virtual ~Visitor() = default;  // ← THIS LINE

    virtual void visit( IntLit& node) =0;
    virtual void visit( FloatLit& node) =0;
    virtual void visit( BoolLit& node) =0;
    virtual void visit( CharLit& node) =0;
    virtual void visit( ListPatternLit& node) =0;
    virtual void visit( StructPatternLit& node) =0;
    virtual void visit( NilLit& node) =0;
    virtual void visit( DefaultLit& node) =0;
    virtual void visit( ElseLit& node) =0;
    virtual void visit( EnumLit& node) =0;
    virtual void visit( EmptyLit& node) =0;

    virtual void visit( AccessNode& node) =0;
    virtual void visit( VarDecl& node) =0;
    virtual void visit( FuncDecl& node) =0;
    virtual void visit( EnumDecl& node) =0;
    virtual void visit( StructDecl& node) =0;
    virtual void visit( UnaryNode& node) =0;
    virtual void visit( BinaryNode& node) =0;
    virtual void visit( StructNode& node) =0;
    virtual void visit( CallNode& node) =0;
    virtual void visit( NominalNode& node) =0;
    virtual void visit( ReturnNode& node) =0;
    virtual void visit( CaseNode& node) =0;
    virtual void visit( CaseBranchNode& node) =0;
    virtual void visit( GuardNode& node) =0;
    virtual void visit( GuardBranchNode& node) =0;
    virtual void visit( ListNode& node) =0;
    virtual void visit( ProgramNode& node) =0;
    virtual void visit( ModuleNode& node) =0;
    virtual void visit( ReadNode& node) =0;
    virtual void visit( PrintNode& node) =0;
};