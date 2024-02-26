// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

/*
 * Compile this test against your .h files to make sure they compile. We
 * suggest adding to this file or creating your own test cases to test your
 * priority queue implementations more thoroughly. If you do not call a
 * function from here, that template is not instantiated and that function is
 * NOT compiled! So for instance, if you don't add code here to call
 * updatePriorities, that function could later cause compiler errors that you
 * don't even know about.
 *
 * Our makefile will build an executable named testPQ if you type 'make
 * testPQ' or 'make alltests' (without the quotes). This will be a debug
 * executable.
 *
 * Notice that testPairing tests the range-based constructor but main and
 * testPriorityQueue do not. Make sure to test the range-based constructor
 * for other PQ types, and also test the PairingPQ-specific member functions.
 *
 * This is NOT a complete test of your priority queues. You have to add code
 * to do more testing!
 *
 * You do not have to submit this file, but it won't cause problems if you
 * do.
 */

#include <cassert>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "BinaryPQ.h"
#include "Eecs281PQ.h"
#include "PairingPQ.h"
#include "SortedPQ.h"
#include "UnorderedPQ.h"


// A type for representing priority queue types at runtime
enum class PQType {
    Unordered,
    Sorted,
    Binary,
    Pairing,
};

// These can be pretty-printed :)
std::ostream& operator<<(std::ostream& ost, PQType pqType) {
    switch (pqType) {
    case PQType::Unordered:
        return ost << "Unordered";
    case PQType::Sorted:
        return ost << "Sorted";
    case PQType::Binary:
        return ost << "Binary";
    case PQType::Pairing:
        return ost << "Pairing";
    }

    return ost << "Unknown PQType";
}


// Compares two int const* on the integers they point to
struct IntPtrComp {
    bool operator()(const int *a, const int *b) const { return *a < *b; }
};


// Test the primitive operations on a priority queue:
// constructor, push, pop, top, size, empty.
template <template <typename...> typename PQ>
void testPrimitiveOperations() {
    std::cout << "Testing primitive priority queue operations..." << std::endl;

    PQ<int> pq {};
    Eecs281PQ<int>& eecsPQ = pq;

    eecsPQ.push(3);
    eecsPQ.push(4);
    assert(eecsPQ.size() == 2);
    assert(eecsPQ.top() == 4);

    eecsPQ.pop();
    assert(eecsPQ.size() == 1);
    assert(eecsPQ.top() == 3);
    assert(not eecsPQ.empty());

    eecsPQ.pop();
    assert(eecsPQ.size() == 0);
    assert(eecsPQ.empty());

    // TODO: Add more testing here!
    PQ<int> pq2 {};
    Eecs281PQ<int>& eecsPQ2(pq2);

    eecsPQ2.push(0);
    eecsPQ2.push(7);
    eecsPQ2.push(6);
    assert(eecsPQ2.size() == 3);
    assert(eecsPQ2.top() == 7);

    eecsPQ2.pop();
    assert(eecsPQ2.size() == 2);
    assert(eecsPQ2.top() == 6);
    assert(not eecsPQ2.empty());

    eecsPQ2.push(3);
    eecsPQ2.pop();
    assert(eecsPQ2.size() == 2);
    assert(eecsPQ2.top() == 3);

    eecsPQ2.pop();
    eecsPQ2.push(4);
    eecsPQ2.pop();
    assert(eecsPQ2.size() == 1);
    assert(eecsPQ2.top() == 0);

    eecsPQ2.pop();
    assert(eecsPQ2.size() == 0);
    assert(eecsPQ2.empty());

    const std::vector<int> vec {
            65, 21, 65, 70, 34, 59, 56, 82, 17, 89, 98, 39, 61, 58, 29, 85, 37, 5, 26, 96, 74, 98, 56, 31, 17
        };

    PQ<int> pq3 {};
    Eecs281PQ<int>& eecsPQ3(pq3);

    assert(eecsPQ3.empty());

    for (size_t q = 0; q < vec.size(); q++) {
        eecsPQ3.push(vec[q]);
        assert(eecsPQ3.size() == (q + 1));
    }

    const std::vector<int> vec_s {
        98, 98, 96, 89, 85, 82, 74, 70, 65, 65, 61, 59, 58, 56, 56, 39, 37, 34, 31, 29, 26, 21, 17, 17, 5
    };

    for (size_t q = 0; q < vec.size(); q++) {
        assert(eecsPQ3.size() == (vec.size() - q));
        assert(eecsPQ3.top() == vec_s[q]);
        eecsPQ3.pop();
    }

    std::cout << "testPrimitiveOperations succeeded!" << std::endl;
}


// Test that the priority queue uses its comparator properly. HiddenData
// can't be compared with operator<, so we use HiddenDataComp{} instead.
template <template <typename...> typename PQ>
void testHiddenData() {
    struct HiddenData {
        int data;
    };

    struct HiddenDataComp {
        bool operator()(const HiddenData &a, const HiddenData &b) const {
            // TODO: Finish this comparator
            return a.data < b.data;
        }
    };

    std::cout << "Testing with hidden data..." << std::endl;

    // TODO: Add code here to actually test with the HiddenData type.
    // Consider writing this code in the style of testPrimitiveOperations
    // above.

    PQ<HiddenData, HiddenDataComp> pq {};
    Eecs281PQ<HiddenData, HiddenDataComp>& eecsPQ = pq;

    eecsPQ.push(HiddenData{3});
    eecsPQ.push(HiddenData{4});
    assert(eecsPQ.size() == 2);
    assert(eecsPQ.top().data == 4);

    eecsPQ.pop();
    assert(eecsPQ.size() == 1);
    assert(eecsPQ.top().data == 3);
    assert(not eecsPQ.empty());

    eecsPQ.pop();
    assert(eecsPQ.size() == 0);
    assert(eecsPQ.empty());

    // TODO: Add more testing here!
    PQ<HiddenData,HiddenDataComp> pq2 {};
    Eecs281PQ<HiddenData,HiddenDataComp>& eecsPQ2(pq2);

    eecsPQ2.push(HiddenData{0});
    eecsPQ2.push(HiddenData{7});
    eecsPQ2.push(HiddenData{6});
    assert(eecsPQ2.size() == 3);
    assert(eecsPQ2.top().data == 7);

    eecsPQ2.pop();
    assert(eecsPQ2.size() == 2);
    assert(eecsPQ2.top().data == 6);
    assert(not eecsPQ2.empty());

    eecsPQ2.push(HiddenData{5});
    eecsPQ2.pop();
    assert(eecsPQ2.size() == 2);
    assert(eecsPQ2.top().data == 5);

    eecsPQ2.pop();
    eecsPQ2.push(HiddenData{4});
    eecsPQ2.pop();
    assert(eecsPQ2.size() == 1);
    assert(eecsPQ2.top().data == 0);

    eecsPQ2.pop();
    assert(eecsPQ2.size() == 0);
    assert(eecsPQ2.empty());

    std::cout << "testHiddenData succeeded!" << std::endl;
}


// Test the last public member function of Eecs281PQ, updatePriorities
template <template <typename...> typename PQ>
void testUpdatePriorities() {
    std::cout << "Testing update priorities..." << std::endl;
    std::vector<int> data {
        1,
        5,
    };

    PQ<const int*, IntPtrComp> pq {};
    Eecs281PQ<const int*, IntPtrComp>& eecsPQ = pq;

    // NOTE: If you add more data to the vector, don't push the pointers
    //   until AFTER the vector stops changing size! Think about why.
    for (auto& datum : data) {
        eecsPQ.push(&datum);
    }

    // Change some element in data (which is pointed to by an element in pq).
    // This new value should be higher than any other so its address will
    // wind qt the top after updatePriorities.
    auto& datum = data[0];
    datum = 10;
    eecsPQ.updatePriorities();
    assert(*eecsPQ.top() == 10);
    assert(eecsPQ.top() == &datum);


    //test 2: volume
    std::vector<int> data2 {
        34, 55, 29, 96, 28, 7, 62, 42, 97, 37, 88, 6, 17, 18, 29, 73, 89, 60, 60, 71, 82, 70, 20, 74, 49
    };

    PQ<const int*, IntPtrComp> pq2 {};
    Eecs281PQ<const int*, IntPtrComp>& eecsPQ2 = pq2;

    for (auto& datum : data2) {
        eecsPQ2.push(&datum);
    }

    for (size_t elt = 0; elt < 25; elt++) {
        auto& datum = data2[elt];
        datum = int(elt + size_t(101));
        eecsPQ2.updatePriorities();
        assert(*eecsPQ2.top() == int(elt + size_t(101)));
        assert(eecsPQ2.top() == &datum);
    }

    //test 3: multiple
    std::vector<int> data3 {
        47, 89, 100, 55, 87, 83, 100, 62, 100, 97, 3, 69, 9, 24, 66, 61, 12, 80, 62, 81, 49, 80, 85, 64, 17
    };

    PQ<const int*, IntPtrComp> pq3 {};
    Eecs281PQ<const int*, IntPtrComp>& eecsPQ3 = pq3;

    for (auto& datum : data3) {
        eecsPQ3.push(&datum);
    }

    for (size_t elt = 0; elt < 25; elt++) {
        auto& datum = data3[elt];
        datum = int(elt + size_t(101));
    }
    eecsPQ3.updatePriorities();
    assert(*eecsPQ3.top() == size_t(125));
    auto& datum2 = data3.back();
    assert(eecsPQ3.top() == &datum2);

    for (size_t elt = 125; elt > 100; elt--) {
        assert(*eecsPQ3.top() == int(elt));
        eecsPQ3.pop();
    }

    std::cout << "testUpdatePriorities succeeded!" << std::endl;

    // TODO: Add more testing here as you see fit.
}


// Test the pairing heap's range-based constructor, copy constructor,
// copy-assignment operator, and destructor
// TODO: Test other operations specific to this PQ type.
void testPairing() {
    std::cout << "Testing Pairing Heap separately..." << std::endl;

    { 
        const std::vector<int> vec {
            1,
            0,
        };

        std::cout << "Calling constructors" << std::endl;

        // Range-based constructor
        PairingPQ<int> pairing1 { vec.cbegin(), vec.cend() };

        // Copy constructor
        PairingPQ<int> pairing2 { pairing1 };

        // Copy-assignment operator
        PairingPQ<int> pairing3 {};
        pairing3 = pairing2;
        
        // A reference to a PairingPQ<T> is a reference to an Eecs281PQ<T>.
        // Yay for polymorphism! We can therefore write:
        Eecs281PQ<int>& pq1 = pairing1;
        Eecs281PQ<int>& pq2 = pairing2;
        Eecs281PQ<int>& pq3 = pairing3;

        assert(pq1.size() == 2);
        pq1.push(3);
        pq2.pop();
        assert(pq1.size() == 3);
        assert(not pq1.empty());
        assert(pq1.top() == 3);

        assert(pq2.size() == 1);
        assert(not pq2.empty());
        assert(pq2.top() == 0);

        pq2.push(pq3.top());
        assert(pq2.top() == pq3.top());
        

        std::cout << "Basic tests done." << std::endl;

        // TODO: Add more code to test addNode, updateElt, etc.
        auto node1 = pairing3.addNode(7);
        assert(pairing3.size() == 3);
        assert(pairing3.top() == 7);
        
        auto node2 = pairing3.addNode(5);
        assert(pairing3.size() == 4);
        assert(pairing3.top() == 7);
        
        pairing3.updateElt(node1, 8);
        assert(node1->getElt() == 8);
        assert(pairing3.top() == 8);
        assert(pairing3.size() == 4);
        
        pairing3.updateElt(node2, 9);
        assert(node2->getElt() == 9);
        assert(pairing3.top() == 9);
        assert(pairing3.size() == 4);

        auto node3 = 
        pairing3.addNode(3);
        pairing3.addNode(4);
        assert(pairing3.size() == 6);
        assert(pairing3.top() == 9);
        
        pairing3.updateElt(node3, 10);
        assert(node3->getElt() == 10);
        assert(pairing3.top() == 10);
        assert(pairing3.size() == 6);

        pairing3.updateElt(node1, 11);
        assert(node1->getElt() == 11);
        assert(pairing3.top() == 11);
        assert(pairing3.size() == 6);
        
        // That { above creates a scope, and our pairing heaps will fall out
        // of scope at the matching } below.
        std::cout << "Calling destructors" << std::endl;
    }

    {

        std::cout << "Calling constructors" << std::endl;

        PairingPQ<int> mdch {}; //mdch = mojo dojo casa house
        
        mdch.addNode(2);
        assert(mdch.size() == 1);
        assert(mdch.top() == 2);

        mdch.addNode(1);
        assert(mdch.size() == 2);
        assert(mdch.top() == 2);

        mdch.addNode(0);
        assert(mdch.size() == 3);
        assert(mdch.top() == 2);

        auto judgeJudy = mdch.addNode(4);
        assert(mdch.size() == 4);
        assert(mdch.top() == 4);

        mdch.addNode(3);
        assert(mdch.size() == 5);
        assert(mdch.top() == 4);
        
        auto rupaul = mdch.addNode(6);
        assert(mdch.size() == 6);
        assert(mdch.top() == 6);

        mdch.addNode(5);
        assert(mdch.size() == 7);
        assert(mdch.top() == 6);
        
        mdch.updateElt(judgeJudy, 7);
        assert(mdch.size() == 7);
        assert(mdch.top() == 7);

        mdch.addNode(10);
        assert(mdch.size() == 8);
        assert(mdch.top() == 10);

        mdch.addNode(9);
        assert(mdch.size() == 9);
        assert(mdch.top() == 10);

        mdch.addNode(8);
        assert(mdch.size() == 10);
        assert(mdch.top() == 10);
        
        mdch.updateElt(judgeJudy, 12);
        assert(mdch.size() == 10);
        assert(mdch.top() == 12);

        mdch.pop();
        assert(mdch.size() == 9);
        assert(mdch.top() == 10);

        mdch.pop();
        assert(mdch.size() == 8);
        assert(mdch.top() == 9);
        
        mdch.updateElt(rupaul, 10);
        assert(mdch.size() == 8);
        assert(mdch.top() == 10);

        mdch.pop();
        assert(mdch.size() == 7);
        assert(mdch.top() == 9);

        mdch.pop();
        assert(mdch.size() == 6);
        assert(mdch.top() == 8);

        mdch.pop();
        assert(mdch.size() == 5);
        assert(mdch.top() == 5);

        mdch.pop();
        assert(mdch.size() == 4);
        assert(mdch.top() == 3);

        std::cout << "Calling destructors" << std::endl;
    }

    std::cout << "testPairing succeeded!" << std::endl;
}


// Run all tests for a particular PQ type.
template <template <typename...> typename PQ>
void testPriorityQueue() {
    testPrimitiveOperations<PQ>();
    testHiddenData<PQ>();
    testUpdatePriorities<PQ>();
}

// PairingPQ has some extra behavior we need to test in updateElement.
// This template specialization handles that without changing the nice
// uniform interface of testPriorityQueue.
template <>
void testPriorityQueue<PairingPQ>() {
    testPrimitiveOperations<PairingPQ>();
    testHiddenData<PairingPQ>();
    testUpdatePriorities<PairingPQ>();
    testPairing();
}


int main() {
    const std::vector<PQType> types {
        PQType::Unordered,
        PQType::Sorted,
        PQType::Binary,
        PQType::Pairing,
    };

    std::cout << "PQ tester" << std::endl << std::endl;
    int idx { 0 };
    for (const auto &type : types) {
        std::cout << "  " << idx++ << ") " << type << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Select one: ";
    uint32_t choice {};
    std::cin >> choice;
    const PQType pqType = types.at(choice);

    std::cout << "Testing the " << pqType << " PQ...\n";

    // TODO: Add more cases to test other priority queue types.
    switch (pqType) {
    case PQType::Unordered:
        testPriorityQueue<UnorderedPQ>();
        break;
    case PQType::Sorted:
        testPriorityQueue<SortedPQ>();
        break;
    case PQType::Binary:
        testPriorityQueue<BinaryPQ>();
        break;
    case PQType::Pairing:
        testPriorityQueue<PairingPQ>();
        break;
    default:
        std::cout << "Unrecognized PQ type " << pqType << " in main.\n"
                  << "You must add tests for all PQ types." << std::endl;
        return 1;
    }

    std::cout << "All tests succeeded!" << std::endl;

    return 0;
}
