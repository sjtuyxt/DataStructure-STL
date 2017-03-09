/** @file */
#ifndef __DEQUE_H
#define __DEQUE_H

#include "ElementNotExist.h"
#include "IndexOutOfBound.h"

/**
 * An deque is a linear collection that supports element insertion and removal at both ends.
 * The name deque is short for "double ended queue" and is usually pronounced "deck".
 * Remember: all functions but "contains" and "clear" should be finished in O(1) time.
 *
 * You need to implement both iterators in proper sequential order and ones in reverse sequential order. 
 */
template <class T>
class Deque
{
public:
	
	T **List;
	int Head,Tail,MaxSize;
	
	void DoubleSpace(){
		T **tmp=List;
		MaxSize*=2;
		List=new T*[MaxSize];
		int h,t,m=(Head+Tail)/2;
		h=t=MaxSize/2;;
		for (int i=m;i>Head;i--){
			List[h--]=new T(*tmp[i]);
			delete tmp[i];
		}
		for (int i=m+1;i<=Tail;i++){
			List[++t]=new T(*tmp[i]);
			delete tmp[i];
		}
		Head=h;
		Tail=t;
		delete [] tmp;
	}
	
    class Iterator
    {
    public:
		
		int Next,Now;
		bool Exist,Rev;
		Deque *Obj;
		
		Iterator(bool itrRev,Deque *Class){
			Obj=Class;
			Rev=itrRev;
			if (!Rev) {
				Next=Obj->Head+1;
				Now=-1;
			}
			else{
				Next=Obj->Tail;
				Now=-1;
			}
			Exist=0;
		}
		
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
			if (Obj->Head==Obj->Tail) return 0;
			if (!Rev) 
				return Now!=Obj->Tail;
			else
				return Now-1!=Obj->Head;
		}

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next() {
			if (hasNext()){
				Now=Next;
				if (!Rev) 
					Next++;
				else 
					Next--;
				Exist=1;
				return *Obj->List[Now];
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
			if (Exist){
				delete Obj->List[Now];
				for (int i=Now;i<Obj->Tail;i++)
					Obj->List[i]=Obj->List[i+1];
				Obj->Tail--;
				if (!Rev){
					Next=Now;
					Now--;
				}
				Exist=0;
			}
			else throw ElementNotExist();
		}
    };

    /**
     * TODO Constructs an empty deque.
     */
    Deque() { 
		MaxSize=10;
		Tail=Head=5;
		List=new T*[10];
	}

    /**
     * TODO Destructor
     */
    ~Deque() { 
		for (int i=Head+1;i<=Tail;i++)
			delete List[i];
		delete [] List;
	}

    /**
     * TODO Assignment operator
     */
    Deque& operator=(const Deque& x) { 
		if (&x==this) return *this;
		for (int i=Head+1;i<=Tail;i++)
			delete List[i];
		while (MaxSize<x.MaxSize) 
			DoubleSpace();
		Head=x.Head;
		Tail=x.Tail;
		for (int i=Head+1;i<=Tail;i++)
			List[i]=new T(*x.List[i]);
		return *this;	
	}

    /**
     * TODO Copy-constructor
     */
    Deque(const Deque& x) { 
		MaxSize=10;
		Tail=Head=5;
		List=new T*[10];
		while (MaxSize<x.MaxSize) 
			DoubleSpace();
		Head=x.Head;
		Tail=x.Tail;
		for (int i=Head+1;i<=Tail;i++)
			List[i]=new T(*x.List[i]);
	}
	
	/**
	 * TODO Inserts the specified element at the front of this deque. 
	 */
	void addFirst(const T& e) { 
		if (Head==-1) DoubleSpace();
		List[Head--]=new T(e);
	}

	/**
	 * TODO Inserts the specified element at the end of this deque.
	 */
	void addLast(const T& e) { 
		if (Tail+1==MaxSize) DoubleSpace();
		List[++Tail]=new T(e);
	}

	/**
	 * TODO Returns true if this deque contains the specified element.
	 */
	bool contains(const T& e) const { 
		for (int i=Head+1;i<=Tail;i++)
			if (*List[i]==e) return 1;
		return 0;
	}

	/**
	 * TODO Removes all of the elements from this deque.
	 */
	 void clear() { 
		for (int i=Head+1;i<=Tail;i++)
			delete List[i];
		Head=Tail=MaxSize/2;
	 }

	 /**
	  * TODO Returns true if this deque contains no elements.
	  */
	bool isEmpty() const { 
		return Head==Tail;
	}

	/**
	 * TODO Retrieves, but does not remove, the first element of this deque.
	 * @throw ElementNotExist
	 */
	 const T& getFirst() { 
		if (Head==Tail) throw ElementNotExist();
		return *List[Head+1];
	 }

	 /**
	  * TODO Retrieves, but does not remove, the last element of this deque.
	  * @throw ElementNotExist
	  */
	 const T& getLast() { 
		if (Head==Tail) throw ElementNotExist();
		return *List[Tail];
	 }

	 /**
	  * TODO Removes the first element of this deque.
	  * @throw ElementNotExist
	  */
	void removeFirst() { 
		if (Head==Tail) throw ElementNotExist();
		delete List[++Head];
	}

	/**
	 * TODO Removes the last element of this deque.
	 * @throw ElementNotExist
	 */
	void removeLast() { 
		if (Head==Tail) throw ElementNotExist();
		delete List[Tail--];
	}

	/**
	 * TODO Returns a const reference to the element at the specified position in this deque.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	const T& get(int index) const { 
		if (index<0||index>=Tail-Head) throw IndexOutOfBound();
		return *List[Head+index+1];
	}
	
	/**
	 * TODO Replaces the element at the specified position in this deque with the specified element.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	void set(int index, const T& e) { 
		if (index<0||index>=Tail-Head) throw IndexOutOfBound();
		delete List[Head+index+1];
		List[Head+index+1]=new T(e);
	}

	/**
	 * TODO Returns the number of elements in this deque.
	 */
	 int size() const { 
		return Tail-Head;
	 }

	 /**
	  * TODO Returns an iterator over the elements in this deque in proper sequence.
	  */
	 Iterator iterator() {
		return Iterator(0,this);
	 }

	 /**
	  * TODO Returns an iterator over the elements in this deque in reverse sequential order.
	  */
	 Iterator descendingIterator() {
		return Iterator(1,this);
	 }
};

#endif
