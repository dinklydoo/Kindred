#pragma once

#include "interf_graph.hpp"
#include "tac_ir.hpp"
#include "x86_regalloc.hpp"

static std::vector<GPReg> gp_params = {RDI, RSI, RDX, RCX, R8, R9};
static std::vector<FPReg> fp_params = {XMM0, XMM1, XMM2, XMM3, XMM4, XMM5};

InterferenceGraph lower_x86(FunctionIR& func);
void add_nodes(FunctionIR& func, InterferenceGraph& ig);
void shift_params(FunctionIR& func, InterferenceGraph& ig);
void precolour_ins(FunctionIR& func, InterferenceGraph& ig);