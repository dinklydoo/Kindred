#include "visitor.hpp"

// visitor pattern boilerplate

void IntLit::accept(Visitor& v){ v.visit(*this);}
void FloatLit::accept(Visitor& v){v.visit(*this);}
void BoolLit::accept(Visitor& v){v.visit(*this);}
void CharLit::accept(Visitor& v){v.visit(*this);}
void ListLit::accept(Visitor& v){v.visit(*this);}
void ListPatternLit::accept(Visitor& v){v.visit(*this);}
void NilLit::accept(Visitor& v){v.visit(*this);}
void DefaultLit::accept(Visitor& v){v.visit(*this);}
void EnumLit::accept(Visitor& v){v.visit(*this);}
void NominalNode::accept(Visitor& v){v.visit(*this);}
void AccessNode::accept(Visitor& v){v.visit(*this);}
void VarDecl::accept(Visitor& v){v.visit(*this);}
void UnaryNode::accept(Visitor& v){v.visit(*this);}
void BinaryNode::accept(Visitor& v){v.visit(*this);}
void CallNode::accept(Visitor& v){v.visit(*this);}
void StructNode::accept(Visitor& v){v.visit(*this);}
void ProgramNode::accept(Visitor& v){v.visit(*this);}
void ReturnNode::accept(Visitor& v){v.visit(*this);}
void CaseBranchNode::accept(Visitor& v){v.visit(*this);}
void CaseNode::accept(Visitor& v){v.visit(*this);}
void GuardBranchNode::accept(Visitor& v){v.visit(*this);}
void GuardNode::accept(Visitor& v){v.visit(*this);}
void ListNode::accept(Visitor& v){v.visit(*this);}
void StructDecl::accept(Visitor& v){v.visit(*this);}
void EnumDecl::accept(Visitor& v){v.visit(*this);}
void PrintNode::accept(Visitor& v){v.visit(*this);}
void ReadNode::accept(Visitor& v){v.visit(*this);}
void ModuleNode::accept(Visitor& v){v.visit(*this);}
void FuncDecl::accept(Visitor& v){v.visit(*this);}