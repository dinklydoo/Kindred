#include "flowcheck.hpp"
#include "parser.hpp"
#include "src/typecheck.hpp"
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

  TypeChecker& tc = TypeChecker::instance();
  tc.typecheck(*module_node);

  FlowChecker& fc = FlowChecker::instance();
  fc.flowcheck(*module_node);

  return 0;
}
