// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"

// A specialized version of the priority queue ADT implemented as a binary heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function, or verify that it is already done
        // data.push_back(TYPE()); //FIX THIS SHIT
    } // BinaryPQ


    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function
        // BinaryPQ(comp);
        for (InputIterator w = start; w != end; w++) {
            push(w);
        } push(end);
        //(void)start;  // Delete this line when you implement this function
        //(void)end;  // Delete this line when you implement this function
    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of order and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        for (size_t w = 0; w < data.size(); w++) {
            if (this->compare(data[child_more(w),data[w]])) {
                TYPE temp = data[child_more(w)];
                data[child_more(w)] = data[w];
                data[w] = temp;
            } else if (this->compare(data[child_less(w),data[w]])) {
                TYPE temp = data[child_less(w)];
                data[child_less(w)] = data[w];
                data[w] = temp;
            }
        }

    } // updatePriorities()


    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val) {
        // TODO: Implement this function.
        data.push_back(val);
        for (size_t w = (data.size() - size_t(1)); w > 0; w = parent(w)) {
            if(this->compare(data[w],data[parent(w)])) {
                TYPE temp = data[parent(w)];
                data[parent(w)] = data[w];
                data[w] = temp;
            } else break;
        }
        //(void)val;  // Delete this line when you implement this function
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the PQ is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop() {
        TYPE temp = data.back();
        data.back() = data.front();
        data.front() = temp();
        data.pop_back();
        for (size_t w = 0; w < data.size(); w = child_more(w)) {
            if(this->compare(data[child_more(w)],data[w])) {
                TYPE temp = data[w];
                data[w] = data[child_more(w)];
                data[child_more(w)] = temp;
            } else break;
        }
        // TODO: Implement this function.
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function.

        // These lines are present only so that this provided file compiles.
        //static TYPE temp; // TODO: Delete this line
        return data.front();      // TODO: Delete or change this line
    } // top()


    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function. Might be very simple,
        // depending on your implementation.
        return data.size(); // TODO: Delete or change this line
    } // size()


    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function. Might be very simple,
        // depending on your implementation.
        return data.empty(); // TODO: Delete or change this line
    } // empty()


private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    // TODO: Add any additional member functions you require here.
    //       For instance, you might add fixUp() and fixDown().
    size_t child_l(const size_t n) const {
        return (size_t(2)*n+size_t(1));
    }
    size_t child_r(const size_t n) const {
        return (child_l(n) + size_t(1));
    }
    size_t child_more(const size_t n) const {
        if (this->compare(data[child_l(n), child_r(n)])) {
            return child_l(n);
        } else return child_r(n);
    }
    size_t child_less(const size_t n) const {
        if (!(this->compare(data[child_l(n), child_r(n)]))) {
            return child_l(n);
        } else return child_r(n);
    } 
    size_t parent(const size_t n) const {
        return (((n+(n%size_t(2)))/size_t(2))/size_t(1));
    }
}; // BinaryPQ


#endif // BINARYPQ_H
