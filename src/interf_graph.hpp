#pragma once

#include <unordered_set>
#include <vector>
#include <cassert>
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

    bool allocated() { return assigned > -1 || spill < 0; }
    bool invalid() { return !valid || simplified; }
};

struct NodeUnion {
    std::unordered_map<Operand, int, Operand::OperandHash> virtual_map;
    std::vector<int> dsu;

    int get_node(Operand op){
        return virtual_map[op] = find_node(virtual_map[op]);
    }

    void union_nodes(Operand op1, Operand op2){
        int n1 = virtual_map[op1];
        int n2 = virtual_map[op2];

        int u1 = find_node(n1);
        int u2 = find_node(n2);
        if (u1 == u2) return;

        // we union op2 into op1 -> wrapper function will handle precolor ordering
        dsu[u2] = u1;
    }

    bool add_node(Operand op){
        if (virtual_map.contains(op)) return false;

        virtual_map.emplace(op, dsu.size());
        dsu.push_back(dsu.size());
        return true;
    }

    int find_node(int node){
        if (dsu[node] == node) return node;
        return dsu[node] = find_node(dsu[node]);
    }
};

using movelist = std::vector<std::pair<Operand, Operand>>;
struct InterferenceGraph {
    NodeUnion node_union;
    std::vector<IGNode> nodes;

    int spill_offset = 0;

    IGNode& add_node(Operand op, RType rtype){
        if (node_union.add_node(op))
            nodes.push_back({op, rtype});
        return nodes[node_union.get_node(op)];
    }

    IGNode& get_node(Operand op){ return nodes[node_union.get_node(op)]; }

    bool coalesced(Operand o1, Operand o2){
        if (!o1.is_register() || !o2.is_register()) return false;
        return node_union.get_node(o1) == node_union.get_node(o2);
    }

    bool interferes(IGNode& node, int idx){
        int idx_p = node_union.find_node(idx);

        std::unordered_set<int> interf;
        for (int inf : node.interfere){
            int p = node_union.find_node(inf);
            interf.insert(p);
        }
        node.interfere = interf;
        return node.interfere.contains(idx_p);
    }

    void add_edge(Operand o1, Operand o2){
        int i = node_union.get_node(o1);
        int j = node_union.get_node(o2);
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
        int i = node_union.get_node(o1);
        int j = node_union.get_node(o2);

        IGNode& n1 = nodes[i];
        IGNode& n2 = nodes[j];

        // interference
        if (interferes(n1, j) || interferes(n2, i) || n1.spill || n2.spill) return FAIL;

        if (n1.allocated() || n2.allocated()) return GEORGE;
        return BRIGG;
    }

    /*
        Merge two nodes based on move instr,
        If a node is precoloured prefer merge into the precoloured one
    */
    void merge_nodes(Operand o1, Operand o2){
        int i = node_union.get_node(o1);
        int j = node_union.get_node(o2);
        if (i == j) return;

        IGNode& n1 = nodes[i];
        IGNode& n2 = nodes[j];

        if (n2.allocated() || (!n1.allocated() && j < i)){
            n1.interfere = smart_union(o1, o2);
            n1.valid = false;
            node_union.union_nodes(o2, o1);
            n2.uses += n1.uses;    
        }
        else {
            n1.interfere = smart_union(o1, o2);
            n2.valid = false;
            node_union.union_nodes(o1, o2);
            n1.uses += n2.uses;
        }
    }


    std::unordered_set<int> smart_union(Operand o1, Operand o2){
        int i = node_union.get_node(o1);
        int j = node_union.get_node(o2);

        IGNode& n1 = nodes[i];
        IGNode& n2 = nodes[j];

        std::unordered_set<int> set_union;
        std::set_union(
            n1.interfere.begin(), n1.interfere.end(),
            n2.interfere.begin(), n2.interfere.end(),
            std::inserter(set_union, set_union.begin())
        );
        std::unordered_set<int> new_union;
        for (int inf : set_union){
            int p = node_union.find_node(inf);
            IGNode& temp = nodes[p];
            if (!temp.spill) new_union.insert(p);
        }
        return new_union;
    }

    int get_interf_size(IGNode& node){
        std::unordered_set<int> interf;
        for (int inf : node.interfere){
            int p = node_union.find_node(inf);
            IGNode& temp = nodes[p];
            if (temp.spill || temp.invalid()) continue; 
            interf.insert(p);
        }
        return interf.size();
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
        if (nodes[id1].allocated() && nodes[id2].allocated())
            return nodes[id1].assigned == nodes[id2].assigned;

        int pci = id1;
        int uci = id2;
        if (nodes[id2].allocated()) std::swap(pci, uci);

        IGNode& pc = nodes[pci];
        IGNode& uc = nodes[uci];

        int colour = pc.assigned;
        for (int n : uc.interfere){
            int p = node_union.find_node(n);
            IGNode& temp = nodes[p];
            if (temp.invalid() || temp.spill) continue;

            if (temp.assigned == colour) return false;
            if (get_interf_size(temp) >= rcount && !interferes(temp, pci)) return false;
        }
        return true;
    }

    bool is_uncoloured();
    IGNode* get_low_deg();
    IGNode& spill_node();
};
