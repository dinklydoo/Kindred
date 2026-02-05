#include "src/flowcheck.hpp"
#include "parser.hpp"
#include "src/typecheck.hpp"
#include "src/ir_lower.hpp"
#include <string>

void yy::parser::error(const yy::location& loc,const std::string& msg) {
    std::cout << "An error occured: " << msg << std::endl;
}

#ifdef YYDEBUG
  int yydebug = 1;
#endif

extern module_ptr module_node;

int main() {
  yydebug = 1;
  yy::parser parser;
  parser.parse();

  tc::TypeChecker& tc = tc::TypeChecker::instance();
  tc.typecheck(*module_node);

  fc::FlowChecker& fc = fc::FlowChecker::instance();
  fc.flowcheck(*module_node);

  ir::IR_Lowerer& ir = ir::IR_Lowerer::instance();
  ir.lower(*module_node);

  return 0;
}
