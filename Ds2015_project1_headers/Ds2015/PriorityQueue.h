/** @file */
#ifndef __PRIORITYQUEUE_H
#define __PRIORITYQUEUE_H

#include "ArrayList.h"
#include "ElementNotExist.h"
#include "Less.h"

/**
 * This is a priority queue based on a priority priority queue. The
 * elements of the priority queue are ordered according to their 
 * natual ordering (operator<), or by a Comparator provided as the
 * second template parameter.
 * The head of this queue is the least element with respect to the
 * specified ordering (different from C++ STL).
 * The iterator does not return the elements in any particular order.
 * But it is required that the iterator will eventually return every
 * element in this queue (even if removals are performed).
 */

template <class V, class C = Less<V> >
class PriorityQueue
{
public:
    class Iterator
    {
    public:
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {}

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const V &next() {}

		/**
		 * TODO Removes from the underlying collection the last element
		 * returned by the iterator.
		 * The behavior of an iterator is unspecified if the underlying
		 * collection is modified while the iteration is in progress in
		 * any way other than by calling this method.
		 * @throw ElementNotExist
		 */
		void remove() {}
    };

    /**
     * TODO Constructs an empty priority queue.
     */
    PriorityQueue() { }

    /**
     * TODO Destructor
     */
    ~PriorityQueue() { }

    /**
     * TODO Assignment operator
     */
    PriorityQueue &operator=(const PriorityQueue &x) { }

    /**
     * TODO Copy-constructor
     */
    PriorityQueue(const PriorityQueue &x) { }

	/**
	 * TODO Initializer_list-constructor
	 * Constructs a priority queue over the elements in this Array List.
     * Requires to finish in O(n) time.
	 */
	PriorityQueue(const ArrayList<V> &x) { }

    /**
     * TODO Returns an iterator over the elements in this priority queue.
     */
    Iterator iterator() {}

    /**
     * TODO Removes all of the elements from this priority queue.
     */
    void clear() {}

    /**
     * TODO Returns a const reference to the front of the priority queue.
     * If there are no elements, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &front() const {}

    /**
     * TODO Returns true if this PriorityQueue contains no elements.
     */
    bool empty() const {}

    /**
     * TODO Add an element to the priority queue.
     */
    void push(const V &value) {}

    /**
     * TODO Removes the top element of this priority queue if present.
     * If there is no element, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void pop() {}

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const {}
};

#endif
