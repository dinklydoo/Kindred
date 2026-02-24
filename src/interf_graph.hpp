#pragma once

#include <vector>
#include "tac_ir.hpp"

struct IGNode {
    Operand op;
    RType type;
    std::unordered_set<int> interfere;
    int assigned = -1;
    int uses = 0;
    int spill = 0;

    bool valid = true; // coalesced
    bool simplified = false; // during register allocation

    bool allocated() { return assigned > -1 || spill; }
};

using movelist = std::vector<std::pair<Operand, Operand>>;
struct InterferenceGraph {
    std::unordered_map<Operand, int, Operand::OperandHash> virtual_map;
    std::vector<IGNode> nodes;

    int spill_offset = 0;

    IGNode& add_node(Operand op, RType rtype){
        if (!virtual_map.contains(op)){
            nodes.push_back({op, rtype});
            virtual_map[op] = nodes.size() - 1;
        }
        return nodes[virtual_map[op]];
    }
    IGNode& get_node(Operand op){ return nodes[virtual_map[op]]; }

    bool coalesced(Operand o1, Operand o2){
        if (!o1.is_register() || !o2.is_register()) return false;
        return virtual_map[o1] == virtual_map[o2];
    }

    void add_edge(Operand o1, Operand o2){
        int i = virtual_map[o1];
        int j = virtual_map[o2];
        if (i == j) return;
        nodes[i].interfere.insert(j);
        nodes[j].interfere.insert(i);
    }

    void incr_uses(Operand op, RType rtype){
        IGNode& node = add_node(op, rtype);
        node.uses++;
    }

    /*
        specify merge option
            - If any node is precoloured we must use georges rule
            - If both uncoloured then we use briggs rule
    */
    #define BRIGG 1
    #define GEORGE 0
    #define FAIL -1
    int merge_type(Operand o1, Operand o2){
        int i = virtual_map[o1];
        int j = virtual_map[o2];

        IGNode& n1 = nodes[i];
        IGNode& n2 = nodes[j];

        // interference
        if (n1.interfere.contains(j) || n2.interfere.contains(i) || n1.spill || n2.spill) return FAIL;

        if (n1.allocated() || n2.allocated()) return GEORGE;
        return BRIGG;
    }

    /*
        Merge two nodes based on move instr,
        If a node is precoloured prefer merge into the precoloured one
    */
    void merge_nodes(Operand o1, Operand o2){
        int i = virtual_map[o1];
        int j = virtual_map[o2];
        if (i == j) return;

        IGNode& n1 = nodes[i];
        IGNode& n2 = nodes[j];

        if (n2.allocated()){ // pre-coloured
            std::set_union(
                n1.interfere.begin(), n1.interfere.end(),
                n2.interfere.begin(), n2.interfere.end(),
                std::inserter(n2.interfere, n2.interfere.begin())
            );
            nodes[i].valid = false;
            virtual_map[o1] = j;
            nodes[j].uses += nodes[i].uses;
        }
        else {
            std::set_union(
                n1.interfere.begin(), n1.interfere.end(),
                n2.interfere.begin(), n2.interfere.end(),
                std::inserter(n1.interfere, n1.interfere.begin())
            );
            nodes[j].valid = false;
            virtual_map[o2] = i;
            nodes[i].uses += nodes[j].uses;
        }
    }

    /*
        Lazy propogation of merges, only when we touch the union set
        do we actually check validity of nodes (if they have been merged into)
    */
    std::unordered_set<int> smart_union(Operand o1, Operand o2){
        int i = virtual_map[o1];
        int j = virtual_map[o2];

        IGNode& n1 = nodes[i];
        IGNode& n2 = nodes[j];

        std::unordered_set<int> set_union;
        std::set_union(
            n1.interfere.begin(), n1.interfere.end(),
            n2.interfere.begin(), n2.interfere.end(),
            std::inserter(set_union, set_union.begin())
        );
        for (auto it = set_union.begin(); it != set_union.end();){
            IGNode& temp = nodes[*it];
            if (!temp.valid || temp.spill) it = set_union.erase(it);
            else it++;
        }
        return set_union;
    }

    int get_interf_size(IGNode& node){
        int res = 0;
        for (auto it = node.interfere.begin(); it != node.interfere.end(); ){
            IGNode& temp = nodes[*it];
            if (!temp.valid || temp.spill){ 
                it = node.interfere.erase(it);
                continue;
            }
            if (!temp.simplified) res++;
            it++;
        }
        return res;
    }

    bool briggs_safe(std::unordered_set<int>& merge, int rcount){
        int hard_nodes = 0;
        for (int i : merge){
            IGNode& node = nodes[i];
            if (get_interf_size(node) >= rcount) hard_nodes++;
        }
        return (hard_nodes < rcount);
    }

    bool george_safe(int id1, int id2, int rcount){
        if (
            nodes[id1].allocated() && nodes[id2].allocated()
            && (nodes[id1].assigned != nodes[id2].assigned)
        ) return false;

        int pci = id1;
        int uci = id2;
        if (nodes[id2].assigned > -1) std::swap(pci, uci);

        IGNode& pc = nodes[pci];
        IGNode& uc = nodes[uci];
        
        for (int n : uc.interfere){
            IGNode& temp = nodes[n];
            if (get_interf_size(temp) >= rcount && !temp.interfere.contains(pci)) return false;
        }
        return true;
    }

    bool is_uncoloured();
    IGNode* get_low_deg();
    IGNode& spill_node();
};
