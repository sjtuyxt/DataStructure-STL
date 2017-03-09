/** @file */
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T>
class LinkedList
{
public:

	class node{
		public:
		T *Data;
		node *Next,*Last;
		node(){
			Next=Last=NULL;
			Data=NULL;
		}
	};
	node Head,Tail;
	int Size;
	
    class Iterator
    {
    public:
		node *Now,*Next,*Last;
		bool exist;
		LinkedList *Obj;
		
		Iterator(LinkedList *Class){
			Obj=Class;
			exist=0;
			Now=Last=NULL;
			Next=Obj->Head.Next;
		}
		
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
			if (Obj->Size==0) return 0;
			return Next!=&(Obj->Tail);
		}

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next() {
			if (hasNext()){
				Last=Now;
				Now=Next;
				Next=Now->Next;
				exist=1;
				return *(Now->Data);
			}
			else throw ElementNotExist();
		}

        /**
         * TODO Removes from the underlying collection the last element
         * returned by the iterator
         * The behavior of an iterator is unspecified if the underlying
         * collection is modified while the iteration is in progress in
         * any way other than by calling this method.
         * @throw ElementNotExist
         */
        void remove() {
			if (exist){
				Now->Last->Next=Now->Next;
				Now->Next->Last=Now->Last;
				Obj->Size--;
				delete Now->Data;
				delete Now;
				exist=0;
			}
			else throw ElementNotExist();
		}
    };

    /**
     * TODO Constructs an empty linked list
     */
    LinkedList() {
		Size=0;
		Head.Next=&Tail;
		Tail.Last=&Head;
	}

    /**
     * TODO Copy constructor
     */
    LinkedList(const LinkedList<T> &c) {	
		Size=0;
		Head.Next=&Tail;
		Tail.Last=&Head;
		for (node *tmp=c.Head.Next;tmp!=&c.Tail;tmp=tmp->Next)
			add(*tmp->Data);
	}

    /**
     * TODO Assignment operator
     */
    LinkedList<T>& operator=(const LinkedList<T> &c) {
		if (&c==this) return *this;
		while (Size) 
			removeFirst(); 
		for (node *tmp=c.Head.Next;tmp!=&c.Tail;tmp=tmp->Next)
			add(*tmp->Data);
		return *this;	
	}

    /**
     * TODO Desturctor
     */
    ~LinkedList() {
		while (Size) 
			removeFirst(); 
	}

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e) {
		add(Size,e);
	}

    /**
     * TODO Inserts the specified element to the beginning of this list.
     */
    void addFirst(const T& elem) {
		add(0,elem);
	}

    /**
     * TODO Insert the specified element to the end of this list.
     * Equivalent to add.
     */
    void addLast(const T &elem) {
		add(elem);
	}

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element) {
		if (index<0||index>Size) throw IndexOutOfBound();
		node *k=Head.Next;
		if (index<=Size/2){
			for (int i=1;i<=index;i++)
				k=k->Next;
		}
		else {
			k=&Tail;
			for (int i=Size;i>index;i--)
				k=k->Last;
		}
		node *tmp=new node;
		tmp->Data=new T(element);
		tmp->Next=k;
		tmp->Last=k->Last;
		k->Last->Next=tmp;
		k->Last=tmp;
		Size++;
	}

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear() {
		while (Size) 
			removeFirst(); 
	}

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const {
		node *k=Head.Next;
		for (int i=1;i<=Size;i++){
			if (*k->Data==e) return 1;
			k=k->Next;
		}	
		return 0;
	}

    /**
     * TODO Returns a const reference to the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const {
		if (index<0||index>=Size) throw IndexOutOfBound();
		node *tmp=Head.Next;
		for (int i=1;i<=index;i++)
			tmp=tmp->Next;
		return *tmp->Data;
	}

    /**
     * TODO Returns a const reference to the first element.
     * @throw ElementNotExist
     */
    const T& getFirst() const {
		if (Size==0) throw ElementNotExist();
		return *Head.Next->Data;
	}

    /**
     * TODO Returns a const reference to the last element.
     * @throw ElementNotExist
     */
    const T& getLast() const {
		if (Size==0) throw ElementNotExist();
		return *Tail.Last->Data;
	}

    /**
     * TODO Returns true if this list contains no elements.
     */
    bool isEmpty() const {
		return Size==0;
	}

    /**
     * TODO Removes the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void removeIndex(int index) {
		if (index<0||index>=Size) throw IndexOutOfBound();
		node *tmp=Head.Next;
		for (int i=1;i<=index;i++)
			tmp=tmp->Next;
		tmp->Last->Next=tmp->Next;
		tmp->Next->Last=tmp->Last;
		delete tmp->Data;
		delete tmp;
		Size--;
	}

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e) {
		node *tmp=Head.Next;
		for (int i=1;i<=Size;i++){
			if (*tmp->Data==e){
				tmp->Last->Next=tmp->Next;
				tmp->Next->Last=tmp->Last;
				delete tmp->Data;
				delete tmp;
				Size--;
				return 1;
			}
			tmp=tmp->Next;
		}	
		return 0;
	}

    /**
     * TODO Removes the first element from this list.
     * @throw ElementNotExist
     */
    void removeFirst() {
		if (Size==0) throw ElementNotExist();
		node *tmp=Head.Next;
		tmp->Last->Next=tmp->Next;
		tmp->Next->Last=tmp->Last;
		delete tmp->Data;
		delete tmp;
		Size--;
	}

    /**
     * TODO Removes the last element from this list.
     * @throw ElementNotExist
     */
    void removeLast() {
		if (Size==0) throw ElementNotExist();
		node *tmp=Tail.Last;
		tmp->Last->Next=tmp->Next;
		tmp->Next->Last=tmp->Last;
		delete tmp->Data;
		delete tmp;
		Size--;
	}

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element) {
		if (index<0||index>=Size) throw IndexOutOfBound();
		node *tmp=Head.Next;
		for (int i=1;i<=index;i++)
			tmp=tmp->Next;
		delete tmp->Data;
		tmp->Data=new T(element);
	}

    /**
     * TODO Returns the number of elements in this list.
     */
    int size() const {
		return Size;
	}

    /**
     * TODO Returns an iterator over the elements in this list.
     */
    Iterator iterator() {
		return Iterator(this);
	}
};

#endif
