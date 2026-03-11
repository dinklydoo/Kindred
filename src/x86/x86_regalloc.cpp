#include "x86_regalloc.hpp"
#include "compile_flags.hpp"
#include "interf_graph.hpp"
#include "liveness.hpp"
#include "cfg_builder.hpp"
#include "tac_ir.hpp"
#include "x86_lower.hpp"
#include <unordered_map>
#include <vector>

void X86_RegAlloc::allocate_prog(std::vector<FunctionIR>& prog, ObjectFormat OBJECT_FORMAT){
    for (FunctionIR& func : prog){
        allocate_func(func, OBJECT_FORMAT);
    }
    X86_Lowerer& xl = X86_Lowerer::instance(OBJECT_FORMAT);
    xl.write_statics();
}

void X86_RegAlloc::allocate_func(FunctionIR& func, ObjectFormat OBJECT_FORMAT){
    X86_Lowerer& xl = X86_Lowerer::instance(OBJECT_FORMAT);
    ig = xl.lower_x86(func);
    // write_func(func);
    LivenessAnalyzer& la = LivenessAnalyzer::instance(X86);
    while (true) {
        ig = InterferenceGraph();
        add_nodes(func);
        precolor_func(func);
        la.gen_interference(func, ig);
        rewrite_coalesce(func);
        if (is_colourable(func)) break;
        // write_func(func);
    }
    allocate_reg(func);
    convert_reg(func);
}

void X86_RegAlloc::add_nodes(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins){
            RType src_type = dtype_to_rtype(ins.type);
            RType dst_type = src_type;

            // special case for cast float operations, ins type represents src type not resultant
            if (ins.op == Operation::CST_F32 || ins.op == Operation::CST_F64) dst_type = FP;

            if (ins.dst.is_register()) ig.add_node(ins.dst, dst_type);
            if (ins.src1.is_register()) ig.add_node(ins.src1, src_type);
            if (ins.src2.is_register()) ig.add_node(ins.src2, src_type);
        }
    }
}

void X86_RegAlloc::precolor_func(FunctionIR& func){
    precolor_locals(func);
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end(); it++){
            Instruction& ins = *it;
            switch (ins.op){
                case (Operation::MOD) : {
                    IGNode& _rdx = ig.get_node(ins.dst);
                    _rdx.assigned = static_cast<int>(RDX);
                }
                case (Operation::FLR) :
                case (Operation::DIV) : 
                // case (Operation::MUL) : 
                {
                    if (is_fp(ins.type)) break;
                    
                    IGNode& _rax = ig.get_node(ins.src1);
                    _rax.assigned = static_cast<int>(RAX);
                    break;
                }
                case (Operation::LSL) :
                case (Operation::LSR) : {
                    if (!ins.src2.is_register()) break;

                    IGNode& _rcx = ig.get_node(ins.src2);
                    _rcx.assigned = static_cast<int>(RCX);
                    break;
                }
                case (Operation::BEGIN_CALL) : {
                    precolor_params(it);
                    break;
                }
                case (Operation::CALL) : 
                case (Operation::CALL_EXT) : {
                    if (ins.type == DataType::EMPTY) break;

                    if (is_fp(ins.type)){ // mov xmm0->dst
                        IGNode& _xmm0 = ig.get_node(ins.dst);
                        _xmm0.assigned = static_cast<int>(XMM0);
                    }
                    else { // mov rax->dst
                        IGNode& _rax = ig.get_node(ins.dst);
                        _rax.assigned = static_cast<int>(RAX);
                    }
                    break;
                }
                case (Operation::RET) : {
                    if (is_fp(ins.type)){ // mov return -> xmm0
                        IGNode& _xmm0 = ig.get_node(ins.src1);
                        _xmm0.assigned = static_cast<int>(XMM0);
                        break;
                    }
                    else { // mov return -> rax
                        IGNode& _rax = ig.get_node(ins.src1);
                        _rax.assigned = static_cast<int>(RAX);
                        break;
                    }
                    break;
                }
                default : continue;
            }
        }
    }
}

void X86_RegAlloc::precolor_locals(FunctionIR& func){
    int fp_param = -1;
    int gp_param = -1;
    int spilt_params = 0;
    Block* header = func.blocks[0].get();
    for (Instruction& ins : header->ins){
        if (ins.op == Operation::BEGIN_FUNC) return;

        if (ins.op == Operation::LOCAL){
            IGNode& node = ig.get_node(ins.src1);
            if (!is_fp(ins.type)){
                gp_param++;
                if (gp_param < gp_params.size())
                    node.assigned = static_cast<int>(gp_params[gp_param]);
                else node.spill = (++spilt_params) * 8;
            }
            else {
                fp_param++;
                if (fp_param < fp_params.size())
                    node.assigned = static_cast<int>(fp_params[fp_param]);
                else node.spill = (++spilt_params) * 8;
            }
        }
    }
}

void X86_RegAlloc::precolor_params(std::list<Instruction>::iterator it){
    int fp_param = -1;
    int gp_param = -1;
    while (true) {
        Instruction& ins = *it;
        if (ins.op == Operation::CALL || ins.op == Operation::CALL_EXT) return;

        if (ins.op == Operation::PARAM){
            IGNode& node = ig.get_node(ins.src1);
            if (!is_fp(ins.type)){
                gp_param++;
                if (gp_param < gp_params.size())
                    node.assigned = static_cast<int>(gp_params[gp_param]);
            }
            else {
                fp_param++;
                if (fp_param < fp_params.size())
                    node.assigned = static_cast<int>(fp_params[fp_param]);
            }
        }
        it++;
    }
}

/*
    Check whether any nodes are left uncoloured in the graph
*/
bool InterferenceGraph::is_uncoloured(){
    for (IGNode& node : nodes){
        if (node.invalid()) continue;

        if (!node.allocated()) return true;
    }
    return false;
}

IGNode* InterferenceGraph::get_low_deg(){
    for (IGNode& node : nodes){
        if (node.invalid()) continue;
        if (node.allocated()) continue;

        int K = (node.type == GP)? GPR_count : FPR_count;
        if (get_interf_size(node) < K) return &node;
    }
    return nullptr;
}

IGNode& X86_RegAlloc::spill_node(FunctionIR& func){
    std::unordered_map<Operand, int, Operand::OperandHash> first_encounter;
    std::unordered_map<Operand, int, Operand::OperandHash> last_encounter;
    std::unordered_map<Operand, double, Operand::OperandHash> costs;

    int i = 0;
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins){
            i++;
            if (ins.dst.is_register()){
                if (!first_encounter.contains(ins.dst)) first_encounter[ins.dst] = i;
                last_encounter[ins.dst] = std::max(last_encounter[ins.dst], i);
            }
            if (ins.src1.is_register()){
                if (!first_encounter.contains(ins.src1)) first_encounter[ins.src1] = i;
                last_encounter[ins.src1] = std::max(last_encounter[ins.src1], i);
            }
            if (ins.src2.is_register()){
                if (!first_encounter.contains(ins.src2)) first_encounter[ins.src2] = i;
                last_encounter[ins.src2] = std::max(last_encounter[ins.src2], i);
            }
        }
    }
    for (auto& p : first_encounter){
        Operand op = p.first;
        IGNode& node = ig.get_node(op);
        if (costs.contains(op) || node.uses == 0) continue;

        costs[op] = (double)node.uses / ig.get_interf_size(node);
    }
    IGNode* candidate = nullptr;
    double cand_priority = 0;

    for (auto& p : costs){
        Operand op = p.first;
        int lifespan = last_encounter[op] - first_encounter[op];
        double sp_priority = (double)lifespan / p.second;

        if (!candidate || sp_priority > cand_priority){
            candidate = &ig.get_node(op);
            cand_priority = sp_priority;
        }
    }
    func.spill_offset -= 8;
    candidate->spill = func.spill_offset;
    return *candidate;
}

/*
    Agressive spill handling, on single spill rewrite IR to include spill
    with short-lived temps
*/
void X86_RegAlloc::rewrite_spill(FunctionIR& func, Operand op, int spill){
    Operand _ebp = Operand::rbp(spill);
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end(); it++){
            Instruction& ins = *it;

            Operand _t = VOID;
            if (ins.src1 == op || ins.src2 == op){
                RType src_type = dtype_to_rtype(ins.type);
                if (ins.op == Operation::CALL || ins.op == Operation::LOAD) src_type = GP;

                _t = get_scratch_reg(ins, src_type);
            
                if (ins.src1 == op) ins.src1 = _t;
                if (ins.src2 == op) ins.src2 = _t;

                if (ins.op == Operation::CALL || ins.op == Operation::LOAD)
                    b->ins.insert(it, {Operation::LOAD, DataType::PTR, _t, _ebp});
                else
                    b->ins.insert(it, {Operation::LOAD, ins.type, _t, _ebp});
            }


            if (ins.dst == op){
                RType dst_type = dtype_to_rtype(ins.type);
                if (ins.op == Operation::CST_F32 || ins.op == Operation::CST_F64) dst_type = FP;

                if (ins.op == Operation::STORE){
                    if (_t == VOID) _t = get_scratch_reg(ins, GP);
                    // if src and dst are the same spilled operand 
                    ins.dst = _t;
                    b->ins.insert(it, {Operation::LOAD, DataType::PTR, _t, _ebp});
                    continue;
                }
                if (_t == VOID) _t = get_scratch_reg(ins, dst_type);
                ins.dst = _t;
                    
                it++;
                DataType dtype = ins.type;
                switch (ins.op){
                    case (Operation::CST_F64) : dtype = DataType::F64; break;
                    case (Operation::CST_F32) : dtype = DataType::F32; break;
                    case (Operation::CST_I64) : dtype = DataType::I64; break;
                    case (Operation::CST_I32) : dtype = DataType::I32; break;
                    default : break;
                }
                b->ins.insert(it--, {Operation::STORE, dtype, _ebp, _t});
            }
        }
    }
}

/*
    Rewrite for coalesced nodes, delete mov instances
    replace nodes with coalesce
*/
void X86_RegAlloc::rewrite_coalesce(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (auto it = b->ins.begin(); it != b->ins.end();){
            Instruction& ins = *it;

            // two nodes are coalesced (pure move -> copy -> delete instruction)
            if (ins.op == Operation::MOV && ig.coalesced(ins.dst, ins.src1)){ 
                it = b->ins.erase(it); continue;
            }
            
            // replace registers with coalesced operand
            if (ins.dst.is_register()) ins.dst = ig.get_node(ins.dst).op;
            if (ins.src1.is_register()) ins.src1 = ig.get_node(ins.src1).op;
            if (ins.src2.is_register()) ins.src2 = ig.get_node(ins.src2).op;
            it++;
        }
    }
    //write_func(func);
}

bool X86_RegAlloc::is_colourable(FunctionIR& func){
    simplify_stack.clear();
    while (ig.is_uncoloured()){
        IGNode* node_ptr = ig.get_low_deg();
        if (!node_ptr){
            IGNode& spilled = spill_node(func);
            rewrite_spill(func, spilled.op, spilled.spill);
            write_func(func);
            
            // restore state
            for (IGNode& node : ig.nodes) node.simplified = false;
            return false;
        }
        simplify_stack.push_back(node_ptr);
        node_ptr->simplified = true;
    }
    return true;
}

void X86_RegAlloc::allocate_reg(FunctionIR& func){
    write_func(func);
    while (!simplify_stack.empty()){
        IGNode& node = *simplify_stack.back();
        simplify_stack.pop_back();

        std::set<int> free_reg;
        if (node.type == GP) free_reg = {
            RAX, RBX, RCX, RDX, RDI, RSI, R8, 
            R9, R12, R13, R14, R15, //R10, R11
        };
        else free_reg = {
            XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8, 
            XMM9, XMM10, XMM11, XMM12, XMM13, //XMM14, XMM15
        };
        for (int inf : node.interfere){
            IGNode& temp = ig.nodes[ig.node_union.find_node(inf)];
            if (temp.allocated()) free_reg.erase(temp.assigned);
        }
        int assign = *free_reg.begin();
        node.assigned = assign;
    }
}

Operand X86_RegAlloc::get_phys_reg(Operand v){
    IGNode& node = ig.get_node(v);
    if (node.type == GP) return Operand::gpr(node.assigned);
    else return Operand::fpr(node.assigned);
}

Operand X86_RegAlloc::get_scratch_reg(Instruction& ins, RType rtype){
    std::set<GPReg> free_gps = {R10, R11};
    std::set<FPReg> free_fps = {XMM14, XMM15};

    std::vector<Operand> ops = {ins.dst, ins.src1, ins.src2};
    for (Operand op : ops){
        if (op.type == Operand::Type::GPR) free_gps.erase(static_cast<GPReg>(op.value));
        if (op.type == Operand::Type::FPR) free_fps.erase(static_cast<FPReg>(op.value));
    }
    return (rtype == GP)? 
        Operand::gpr(*free_gps.begin()) :
        Operand::fpr(*free_fps.begin()) ;
}

void X86_RegAlloc::convert_reg(FunctionIR& func){
    for (auto bit = func.blocks.begin(); bit != func.blocks.end(); bit++){
        Block* b = bit->get();
        for (Instruction& ins : b->ins){
            if (ins.dst.is_register())ins.dst = get_phys_reg(ins.dst);
            if (ins.src1.is_register())ins.src1 = get_phys_reg(ins.src1);
            if (ins.src2.is_register())ins.src2 = get_phys_reg(ins.src2);
        }
    }
}