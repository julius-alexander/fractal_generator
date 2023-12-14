#include <iostream>
#include "instruction_list.h"

using namespace std;

// destructor - deallocate all nodes in list
InstructionList::~InstructionList() {
    node_t* cur = head;
    while (cur != nullptr) {
        node_t* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}


// Prints instructions
ostream& operator<<(ostream& out, const InstructionList& instructions) {
    for (hilbert_t move : instructions) {
        if (move == FORWARD) { out << "F "; }
        if (move == TURN_LEFT) { out << "L "; }
        if (move == TURN_RIGHT) { out << "R "; }
        if (move == ODD)
            ;// { out << "O "; } // do nothing
        if (move == EVEN)
            ;// { out << "E "; } // do nothing
    }
    return out;
}


// Adds move to end of list
void InstructionList::append(hilbert_t move) {
    node_t* newNode = new node_t;
    newNode->move = move;
    newNode->next = nullptr;

    if (head == nullptr) { head = tail = newNode; }

    else { 
        tail->next = newNode;
        tail = newNode;
    }
}


// Applies substitution rules to list
void InstructionList::substitute(const unordered_map<hilbert_t, const InstructionList*>& rules) {
    node_t* cur = head;
    // create copy of subs list
    while (cur != nullptr) {
        auto rule = rules.find(cur->move);

        // checks if current move is a substitution symbol
        if (rule != rules.end()) {
            node_t* target = cur->next;     // save node after symbol for later
            node_t* ruleNode = rule->second->head;
            // making copy of rhs of substitution symbol to reference later
            InstructionList* newInstructs = new InstructionList;

            while (ruleNode != nullptr) {
                newInstructs->append(ruleNode->move);
                ruleNode = ruleNode->next;
            }
            // Replace symbol with rule and connect original list to rule
            cur->move = newInstructs->head->move;
            cur->next = newInstructs->head->next;

            // move cur to the end of the new instructions (substitution rule)
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            // connect substitution rule back to original list
            cur->next = target;
        }
        cur = cur->next;
    }
}
