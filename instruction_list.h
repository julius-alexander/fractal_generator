#ifndef __INSTRUCTION_LIST_H
#define __INSTRUCTION_LIST_H

using namespace std;

//Represents a single instruction
enum hilbert_t { FORWARD, TURN_LEFT, TURN_RIGHT, ODD, EVEN };

//Class representing instructions for drawing a Hilbert curve
class InstructionList {
		
	typedef struct node {
		hilbert_t move;
		struct node* next;
		void operator=(const struct node& rhs) { move = rhs.move; }
	} node_t;
		
	friend ostream& operator<<(ostream&, const InstructionList& list);
		
	private:
		node_t* head;
		node_t* tail;
		double dist;

    public:
        class iterator {
            private:
                const node_t* node;
            public:
                iterator(const node_t* node) : node(node) {}
                hilbert_t operator*() const { return node->move; }
                void operator++() { node = node->next; }
                bool operator!=(iterator rhs) const { return node != rhs.node; }
            };

        InstructionList() { head = tail = nullptr; dist = 1.0; }
        ~InstructionList();
        iterator begin() const { return iterator(head); }
        iterator end() const { return iterator(nullptr); }
        void append(hilbert_t);
        void substitute(const unordered_map<hilbert_t, const InstructionList*>&);
        double getDistance() const { return dist; }
        void setDistance(double d) { dist = d; }
};

ostream& operator<<(ostream&, const InstructionList& list);

#endif
