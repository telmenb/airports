#pragma once

#include "airport.hpp"
#include <vector>

/**
 * heap: A min-priority queue of Airports implemented as a heap.
 *
 * @design Chase Geigle
 * @author Telmen Bayarsaikhan, Anish Sabnis
 */
class heap
{
  public:
    /**
     * Constructs an empty heap.
     */
    heap();

    /**
     * Constructs a heap from a vector of elements by copying the
     * elements into the heap's storage and then running the buildHeap
     * algorithm.
     *
     * @param elems The elements that should be placed in the heap.
     */
    heap(const std::vector<Airport*>& elems);

    /**
     * Removes the element with highest priority according to the
     * higherPriority() functor.
     *
     * @return The element with highest priority in the heap.
     */
    Airport* pop();

    /**
     * Returns, but does not remove, the element with highest priority.
     *
     * @return The highest priority element in the entire heap.
     */
    Airport* peek() const;

    /**
     * Inserts the given element into the heap, restoring the heap
     * property after the insert as appropriate.
     *
     * @param elem The element to be inserted.
     */
    void push(Airport* elem);

    /**
     * Updates the element at the provided index of the heap array.
     * The update is done in such a way that the array will be 
     * corrected, so it will remain as a valid heap.
     *
     * @param idx The index of the element to be updated 
     * (This is root()-indexed, so will work if
     * using either zero or one-indexed heaps)
     * @param elem The element to be updated with.
     */
    void updateElem(const size_t & idx, Airport* elem);

    /**
     * Determines if the given heap is empty.
     *
     * @return Whether or not there are elements in the heap.
     */
    bool empty() const;

    /*Gets the vector of elems.*/
    void getElems(std::vector<Airport*> & heaped) const;

    /**
     * Helper function that returns the root index of this heap.
     * 
     * @return The index of the root node of the heap.
     */
    size_t root() const;

    /**
     * Inline helper to return the size of the _elems vector.
     * 
     * @return The size of _elems.
     */
    size_t size() { return _elems.size(); }

  private:
    /**
     * The internal storage for this heap, 1-indexed.
     */
    std::vector<Airport*> _elems;

    /**
     * Comparison function. This function takes two Airports and returns true
     * if the first parameter has a higher priority (lower dij-dist) than the second.
     */
    bool higherPriority(Airport* one, Airport* two) const { return one < two; }

    /**
     * Helper function that returns the index of the left child of a
     * node in the heap.
     *
     * @param currentIdx The index of the current node.
     * @return The index of the left child of the current node.
     */
    size_t leftChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the right child of a
     * node in the heap.
     *
     * @param currentIdx The index of the current node.
     * @return The index of the right child of the current node.
     */
    size_t rightChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the parent of a node
     * in the heap.
     *
     * @param currentIdx The index of the current node.
     * @return The index of the parent of the current node.
     */
    size_t parent(size_t currentIdx) const;

    /**
     * Helper function that determines whether a given node has a
     * child.
     *
     * @param currentIdx The index of the current node.
     * @return A boolean indicating whether the current node has a
     *  child or not.
     */
    bool hasAChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the child with the
     * highest priority as defined by the higherPriority() function.
     *
     * @param currentIdx The index of the current node.
     * @return The index of the highest priority child of this node.
     */
    size_t maxPriorityChild(size_t currentIdx) const;

    /**
     * Helper function that restores the heap property by sinking a
     * node down the tree as necessary.
     *
     * @param currentIdx The index of the current node that is being
     *  sunk down the tree.
     */
    void heapifyDown(size_t currentIdx);

    /**
     * Helper function that restores the heap property by bubbling a
     * node up the tree as necessary.
     *
     * @param currentIdx The index of the current node that is being
     *  bubbled up the tree.
     */
    void heapifyUp(size_t currentIdx);
};