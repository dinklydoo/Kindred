#include "parser.hpp"
#include "src/typecheck.hpp"
#include "src/flowcheck.hpp"
#include "src/ir_lower.hpp"
#include "src/closure.hpp"
#include "src/cfg_builder.hpp"
#include "src/liveness.hpp"

#include <string>

void yy::parser::error(const yy::location& loc,const std::string& msg) {
    std::cout << "An error occured: " << msg << std::endl;
}

#ifdef YYDEBUG
  int yydebug = 1;
#endif

extern module_ptr module_node;
std::vector<FunctionIR> IR_program;
std::vector<InterferenceGraph> interf_graph;

int main() {
  yydebug = 1;
  yy::parser parser;
  parser.parse();

  tc::TypeChecker& tc = tc::TypeChecker::instance();
  tc.typecheck(*module_node);

  std::cout << "[Kindred Compiler] : Typecheck Passed\n";

  fc::FlowChecker& fc = fc::FlowChecker::instance();
  fc.flowcheck(*module_node);

  std::cout << "[Kindred Compiler] : Flowcheck Passed\n";

  cs::ClosureGen& cg = cs::ClosureGen::instance();
  cg.generate(*module_node);
  std::cout << "[Kindred Compiler] : Closures Generated \n";

  ir::IR_Lowerer& ir = ir::IR_Lowerer::instance();
  std::cout << "[Kindred Compiler] : IR Generated\n";
  IR_program = ir.lower(*module_node);
  print_ir(IR_program);

  cfg::CFGBuilder& cfg = cfg::CFGBuilder::instance();
  cfg.build_cfg(IR_program);
  std::cout << "[Kindred Compiler] : CFG Constructed\n";

  LivenessAnalyzer& la = LivenessAnalyzer::instance(X86);
  la.analyze(IR_program);
  std::cout << "[Kindred Compiler] : Liveness Analysis Complete\n";
  
  for (FunctionIR& func : IR_program) interf_graph.push_back(
    la.gen_interference(func)
  );

  return 0;
}
