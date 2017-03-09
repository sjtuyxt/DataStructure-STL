/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, where it means
 * the length of the array of your internal implemention
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class T>
class ArrayList
{
public:

	int MaxSize,Size;
	T **List;
	
	void DoubleSpace(){
		T **temp=List;
		List=new T*[2*MaxSize];
		for (int i=0;i<Size;i++){
			List[i]=new T(*temp[i]);
			delete temp[i];
		}	
		MaxSize*=2;
		delete [] temp;
	}
	
    class Iterator
    {
    public:
		int Now,Next;
		ArrayList *Obj;
		
		Iterator(ArrayList *Class){
			Now=-1;
			Next=0;
			Obj=Class;
		}
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
			return Next<Obj->Size;
		}
        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next() {
			if (hasNext()){
				Now=Next;
				return *(Obj->List[Next++]);
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
			if (Now!=-1){
				delete Obj->List[Now];
				for (int i=Next;i<Obj->Size;i++)
					Obj->List[i-1]=Obj->List[i];
				Obj->Size--;
				Now=-1;
				Next--;
			}
			else throw ElementNotExist();
		}
    };

    /**
     * TODO Constructs an empty array list.
     */
    ArrayList() { 
		Size=0;
		MaxSize=10;
		List=new T*[MaxSize];
	}

    /**
     * TODO Destructor
     */
    ~ArrayList() { 
		for (int i=0;i<Size;i++)
		delete List[i];
		delete [] List;
	}

    /**
     * TODO Assignment operator
     */
    ArrayList& operator=(const ArrayList& x) { 
		if (&x==this) return *this;
		for (int i=0;i<Size;i++)
			delete List[i];
		Size=0;
		while (MaxSize<x.Size) {
			DoubleSpace();
		}	
		Size=x.Size;
		for (int i=0;i<Size;i++)
			List[i]=new T(*x.List[i]);
		return *this;	
	}

    /**
     * TODO Copy-constructor
     */
    ArrayList(const ArrayList& x):List(NULL),Size(x.Size),MaxSize(x.MaxSize)  {
		List=new T*[MaxSize];
		for (int i=0;i<Size;i++)
			List[i]=new T(*x.List[i]);
	}

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e) {
		if (Size==MaxSize) DoubleSpace();
		List[Size++]=new T(e);
		return true;
	}

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element) {
		if (index<0||index>Size) throw IndexOutOfBound();
		if (Size==MaxSize) DoubleSpace();
		for (int i=Size;i>index;i--)
		List[i]=List[i-1];
		List[index]=new T(element);
		Size++;
	}

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear() {
		Size=0;
	}

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const {
		for (int i=0;i<Size;i++)
			if (*List[i]==e) return 1;
		return 0;
	}

    /**
     * TODO Returns a const reference to the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const {
		if (index<0||index>Size) throw IndexOutOfBound();
		return *List[index];
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
		delete List[index];
		for (int i=index;i<Size-1;i++)
			List[i]=List[i+1];
		Size--;
	}

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e) {
		for (int i=0;i<Size;i++)
			if (*List[i]==e){
				removeIndex(i);
				return 1;
			}
		return 0;
	}

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element) {
		if (index<0||index>=Size) throw IndexOutOfBound();
		delete List[index];
		List[index]=new T(element);
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
