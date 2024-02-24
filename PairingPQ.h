// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>
#include <cassert>
#include <iostream>

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
                : elt{ val }, child{ nullptr }, sibling{ nullptr }, previous{ nullptr }
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
            Node *previous; // TODO: Add one extra pointer (parent or previous) as desired.
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
        root = nullptr;
        count = 0;
        this->compare = comp;
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
        this->count = 0;
        this->root = nullptr;
        this->compare = comp;
        InputIterator here = start;
        while (here != end) {
            push(*here);
            here++;
        }

        /*
        (void)start;  // Delete this line when you implement this function
        (void)end;  // Delete this line when you implement this function
        */
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
        this->compare = other.compare;
        std::deque<Node*> singles;
        std::deque<Node*> hold;
        hold.push_back(other.root);
        while (!hold.empty()) {
            Node* a = hold.front();
            Node* b = a->child;
            hold.pop_front();
            singles.push_back(a);
            while (b != nullptr) {
                hold.push_back(b);
                b = b->sibling;
            }
        } while (!singles.empty()) {
            Node* temp = singles.front();
            this->push(temp->getElt());
            singles.pop_front();
        }
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // TODO: Implement this function.
        // HINT: Use the copy-swap method from the "Arrays and Containers"
        // lecture.
        //(void)rhs;  // Delete this line when you implement this function
        this->root = nullptr;
        this->count = 0;
        PairingPQ temp(rhs);
        std::swap(root,temp.root);
        std::swap(count,temp.count);
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        while (!this->empty()) {
            this->pop();
        }
        // TODO: Implement this function.
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant.  You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        std::deque<Node*> singles;
        std::deque<Node*> hold;
        hold.push_back(root);
        while (!hold.empty()) {
            Node* a = hold.front();
            Node* b = a->child;
            hold.pop_front();
            a->previous = nullptr;
            root = b;
            singles.push_back(a);
            a->child = nullptr;
            while (b != nullptr) {
                Node* c = b->sibling;
                b->sibling = nullptr;
                if(c != nullptr) c->previous = nullptr;
                hold.push_back(b);
                b = c;
            }
        } while (!singles.empty()) {
            Node* temp = singles.front();
            add_in(temp);
            singles.pop_front();
        }
        // TODO: Implement this function.
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
        if (this->size() == 1) {
            Node* her = root;
            root = nullptr;
            delete her;
            count--;
        } else if (this->size() == 2) {
            Node* her = root;
            root = her->child;
            root->previous = nullptr;
            delete her;
            count--;
        } else {
            std::deque<Node*> hold;
            Node* a = root;
            Node* b = a->child;
            root = nullptr;
            delete a;
            count--;
            while (b != nullptr) {
                hold.push_back(b);
                b->previous = nullptr;
                a = b;
                b = a->sibling;
                a->sibling = nullptr;
            } while (!hold.empty()) {
                Node* temp = hold.front();
                add_in(temp);
                hold.pop_front();
            }
        }
        // sever family ties, store children in hold, addNode the children back
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function
        assert(this->root != nullptr);
        return (root->getElt());
        // These lines are present only so that this provided file compiles.
        /* static TYPE temp; // TODO: Delete this line
        return temp;      // TODO: Delete or change this line */
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function
        return count;
        //return 0; // TODO: Delete or change this line
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
        Node* tSib = node->sibling;
        Node* tPre = node->previous;
        std::deque<Node*> hold;
        Node* a = node;
        Node* b = a->child;

        node->sibling = nullptr;
        node->child = nullptr;
        node->previous = nullptr;

        if(tSib != nullptr) tSib->previous = tPre;

        node->elt = new_value;
        hold.push_back(node);

        while (b != nullptr) {
            hold.push_back(b);
            a = b;
            b = a->sibling;
            a->sibling = nullptr;
            b->previous = nullptr;
        } while (!hold.empty()) {
            add_in(hold.front());
            hold.pop_front();
        }

        /* (void)node;  // Delete this line when you implement this function
        (void)new_value;  // Delete this line when you implement this func */
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
        Node* her = new Node(val);
        add_in(her);
        count++;
        return her;
        /* (void)val;  // Delete this line when you implement this function
        return nullptr; // TODO: Delete or change this line */
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    // require here.
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    // papers).
    void add_in (Node* her) {
        if (this->root == nullptr) {
            root = her;
        } else if (this->compare(root->getElt(),her->getElt())) {
            root->previous = her;
            her->child = root;
            root = her;
        } else {
            if (root->child == nullptr) {
                root->child = her;
                her->previous = root;
            } else {
                Node* him = root->child;
                root->child = her;
                her->previous = root;
                her->sibling = him;
                him->previous = her;
            }
        }
    }

    Node* root;
    size_t count;
    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H
