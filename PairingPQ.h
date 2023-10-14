// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure
            // to initialize it here.
            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr }, parent{ nullptr}
            {}

            // Description: Allows access to the element at that Node's
            // position.  There are two versions, getElt() and a dereference
            // operator, use whichever one seems more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
            // function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *parent;
            // TODO: Add one extra pointer (parent or previous) as desired.
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
        root = nullptr;
        count = 0;
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
        root = nullptr;
        count = 0;
        for (InputIterator w = start; w != end; w++) {
            push(*w);
        } 

        //(void)start;  // Delete this line when you implement this function
        //(void)end;  // Delete this line when you implement this function
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
        root = nullptr;
        count = 0;
        std::deque<Node*> intake;
        intake.push_back(other.root);
        while (!intake.empty()) {
            if (intake.front()->sibling != nullptr) {
                intake.push_back(intake.front()->sibling);
            }
            if (intake.front()->child != nullptr) {
                intake.push_back(intake.front()->child);
            }
            this->push(intake.front()->elt);
            intake.pop_front();
        }
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        // HINT: Use the copy-swap method from the "Arrays and Containers"
        // lecture.
        // (void)rhs;  // Delete this line when you implement this function
        root = nullptr;
        count = 0;
        PairingPQ temp(rhs);
        std::swap(root,temp.root);
        std::swap(count,temp.count);
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        while (size() > 1) {
            pop();
            //std::cout << size() << std::endl;
        } delete root;
        //count--;
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant.  You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        std::deque<Node*> intake;
        std::deque<Node*> temp;
        intake.push_back(root);
        root = nullptr;
        while (!intake.empty()) {
            if (intake.front()->sibling != nullptr) {
                intake.push_back(intake.front()->sibling);
            }
            if (intake.front()->child != nullptr) {
                intake.push_back(intake.front()->child);
            }
            temp.push_back(intake.front());
            intake.pop_front();
        }
        root = temp.front();
        temp.pop_front();
        for (size_t y = temp.size(); y > 1; y--) { //(temp.size()+((temp.size()%size_t(2))/size_t(2)))
            Node* a = temp.back();
            temp.pop_back();
            Node* b = temp.back();
            temp.pop_back();
            temp.push_front(meld(a,b));
        } while (temp.size() > 1) {
            Node* a = temp.front();
            temp.pop_front();
            Node* b = temp.front();
            temp.pop_front();
            temp.push_front(meld(a,b));
        } 
        root = temp.front();
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely
    //              in the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);    
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the pairing heap is empty. Though you are welcome to
    // if you are familiar with them, you do not need to use exceptions in
    // this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
        if (size() == 1) {
            std::cout << "deleting root\n";
            delete root;
            //root = nullptr;
            //std::cout << "node deleted (special)\n";
        } else if (size() == 2) {
            //std::cout << "deleting last child\n";
            Node* temp = root->child;
            delete root;
            root = temp;
        } else {
            //std::cout << "deleting (normal)\n";
            std::deque<Node*> temp;
            Node* f = root->child;
            while (f != nullptr) {
                temp.push_back(f);
                Node* g = f->sibling;
                f->sibling = nullptr;
                f->parent = nullptr;
                f = g;
            } for (size_t y = temp.size(); y > 1; y--) { 
                Node* a = temp.back();
                temp.pop_back();
                Node* b = temp.back();
                temp.pop_back();
                temp.push_front(meld(a,b));
            } while (temp.size() > 1) {
                Node* a = temp.front();
                temp.pop_front();
                Node* b = temp.front();
                temp.pop_front();
                temp.push_front(meld(a,b));
            } 
            delete root;
            //std::cout << "node deleted\n";
            root = temp.front();
            temp.pop_front();
        }
        count--;
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function

        // These lines are present only so that this provided file compiles.
        //static TYPE temp; // TODO: Delete this line
        return root->elt;      // TODO: Delete or change this line
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function
        return count; // TODO: Delete or change this line
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function
        return (count == 0); // TODO: Delete or change this line
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value.  Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //              extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        // TODO: Implement this function
        Node* current = node;
        node->elt = new_value;
        while (this->compare(current,current->parent)) {
            Node* temp = current->parent;
            current->parent = temp->parent;
            temp->parent = current;
            temp->child = current->child;
            current->child = temp;
            Node* temp2 = current->sibling;
            current->sibling = temp->sibling;
            temp->sibling = temp2;
            if (temp == root) {
                root = current;
                break;
            }
        }
        //(void)node;  // Delete this line when you implement this function
        //(void)new_value;  // Delete this line when you implement this func
    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // Runtime: O(1)
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    Node* addNode(const TYPE &val) {
        // TODO: Implement this function 
        Node* baby = new Node(val);
        std::cout << baby << std::endl;
        if (root == nullptr) {
            //std::cout << "first node pushed\n";
            root = baby;
        } else if (!this->compare(root->elt,baby->elt)) {
            //std::cout << "pushing via swap\n";
            Node* temp = root->child;
            root->child = baby;
            baby->sibling = temp;
        } else {
            //std::cout << "pushing via rebase\n";
            baby->child = root;
            root = baby;
        } count++;
        //(void)val;  // Delete this line when you implement this function
        return baby; // TODO: Delete or change this line
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    // require here.
    Node* root;
    size_t count;
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    // papers).
    Node* meld (Node* a, Node* b) {
        if (!this->compare(a->elt,b->elt)) {
            a->child = b;
            b->parent = a;
            return a;
        } else {
            b->child = a;
            a->parent = b;
            return b;
        }
    }

    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H
