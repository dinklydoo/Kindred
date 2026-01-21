#include "parser.hpp"
#include <string>

void yy::parser::error(const std::string& msg) {
    std::cout << "An error occured: " << msg << std::endl;
}

#ifdef YYDEBUG
  int yydebug = 1;
#endif

extern module_ptr module;

int main() {
    yydebug = 1;
    yy::parser parser;
    parser.parse();
    return 0;
}
