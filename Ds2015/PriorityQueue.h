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

	int MaxSize,Size;
	V **List;
	C cmp;
	
	void DoubleSpace(){
		V **temp=List;
		List=new V*[2*MaxSize+1];
		for (int i=1;i<=Size;i++){
			List[i]=new V(*temp[i]);
			delete temp[i];
		}	
		MaxSize*=2;
		delete [] temp;
	}

	int down(int x){
		int k=2*x;
		while (k<=Size){
			if (k<Size && cmp(*List[k+1],*List[k])) k++;
			if (cmp(*List[k],*List[x])){
				V *tmp=List[k];
				List[k]=List[x];
				List[x]=tmp;
			}
			else return x;
			x=k;
			k=x*2;
		}
	}
	
	int up(int x){
		while (x/2){
			if (cmp(*List[x],*List[x/2])){
				V *tmp=List[x];
				List[x]=List[x/2];
				List[x/2]=tmp;
			}
			else return x;
			x/=2;
		}
	}
	
    class Iterator
    {
    public:
	
		int Next,Now,Jump,Cnt;
		PriorityQueue *Obj;
		
		Iterator(PriorityQueue *Class){
			Obj=Class;
			Next=1;
			Now=0;
			Jump=0;
			Cnt=0;
		}
	
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
			if (Obj->Size==0) return 0;
			return Next<=Obj->Size;
		}

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const V &next() {
			if (hasNext()){
				Now=Next;
				int tmp=Next;
				if (Jump){
					Next=Jump;
					Jump=0;
				}
				else 
					Next++;
				if (Now>Cnt) Cnt=Now;
				return *Obj->List[tmp];
			}
			else throw ElementNotExist();
		}

		/**
		 * TODO Removes from the underlying collection the last element
		 * returned by the iterator.
		 * The behavior of an iterator is unspecified if the underlying
		 * collection is modified while the iteration is in progress in
		 * any way other than by calling this method.
		 * @throw ElementNotExist
		 */
		void remove() {
			if (Now){
				delete Obj->List[Now];
				Obj->List[Now]=Obj->List[Obj->Size--];
				Next=Obj->up(Now);
				Next=Obj->down(Next);
				if (Next>=Cnt) Next=Cnt;
				else if (Next<Cnt) Jump=Cnt+1;
				Now=0;
			}
			else throw ElementNotExist();
		}
    };

    /**
     * TODO Constructs an empty priority queue.
     */
    PriorityQueue() { 
		MaxSize=10;
		Size=0;
		List=new V*[MaxSize+1];
	}

    /**
     * TODO Destructor
     */
    ~PriorityQueue() { 
		for (int i=1;i<=Size;i++)
			delete List[i];
		delete [] List;	
	}

    /**
     * TODO Assignment operator
     */
    PriorityQueue &operator=(const PriorityQueue &x) { 
		if (&x==this) return *this;
		while (MaxSize<x.Size) 
			DoubleSpace();
		Size=x.Size;
		for (int i=1;i<=Size;i++)
			List[i]=new V(*x.List[i]);
		return *this;
	}

    /**
     * TODO Copy-constructor
     */
    PriorityQueue(const PriorityQueue &x) { 
		MaxSize=10;
		Size=0;
		List=new V*[MaxSize+1];
		*this=x;
	}

	/**
	 * TODO Initializer_list-constructor
	 * Constructs a priority queue over the elements in this Array List.
     * Requires to finish in O(n) time.
	 */
	PriorityQueue(const ArrayList<V> &x) { 
		MaxSize=10;
		Size=0;
		List=new V*[MaxSize+1];
		while (MaxSize<x.Size)
			DoubleSpace();
		Size=x.Size;
		for (int i=1;i<=Size;i++)
			List[i]=new V(*x.List[i-1]);
		for (int i=Size/2;i>=1;i--)
			down(i);
	}

    /**
     * TODO Returns an iterator over the elements in this priority queue.
     */
    Iterator iterator() {
		return Iterator(this);
	}

    /**
     * TODO Removes all of the elements from this priority queue.
     */
    void clear() {
		for (int i=1;i<=Size;i++)
			delete List[i];
		Size=0;
	}

    /**
     * TODO Returns a const reference to the front of the priority queue.
     * If there are no elements, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &front() const {
		if (Size==0) throw ElementNotExist();
		return *List[1];
	}

    /**
     * TODO Returns true if this PriorityQueue contains no elements.
     */
    bool empty() const {
		return Size==0;
	}

    /**
     * TODO Add an element to the priority queue.
     */
    void push(const V &value) {
		if (Size==MaxSize) DoubleSpace();
		List[++Size]=new V(value);
		up(Size);
	}

    /**
     * TODO Removes the top element of this priority queue if present.
     * If there is no element, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void pop() {
		if (Size==0) throw ElementNotExist();
		delete List[1];
		List[1]=List[Size--];
		down(1);
	}

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const {
		return Size;
	}
};

#endif
