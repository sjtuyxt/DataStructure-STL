/** @file */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "ElementNotExist.h"

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your internal implemention, not the current number of the
 * elements.
 *
 * Template argument H are used to specify the hash function.
 * H should be a class with a static function named ``hashCode'',
 * which takes a parameter of type K and returns a value of type int.
 * For example, the following class
 * @code
 *      class Hashint {
 *      public:
 *          static int hashCode(int obj) {
 *              return obj;
 *          }
 *      };
 * @endcode
 * specifies an hash function for integers. Then we can define:
 * @code
 *      HashMap<int, int, Hashint> hash;
 * @endcode
 *
 * Hash function passed to this class should observe the following rule: if two keys
 * are equal (which means key1 == key2), then the hash code of them should be the
 * same. However, it is not generally required that the hash function should work in
 * the other direction: if the hash code of two keys are equal, the two keys could be
 * different.
 *
 * Note that the correctness of HashMap should not rely on the choice of hash function.
 * This is to say that, even the given hash function always returns the same hash code
 * for all keys (thus causing a serious collision), methods of HashMap should still
 * function correctly, though the performance will be poor in this case.
 *
 * The order of iteration could be arbitary in HashMap. But it should be guaranteed
 * that each (key, value) pair be iterated exactly once.
 */
template <class K, class V, class H>
class HashMap
{
public:
    class Entry
    {
	friend class HashMap<K,V,H>;
	private:
        K key;
        V value;
    public:
        Entry(K k, V v)
        {
            key = k;
            value = v;
        }

        K getKey() const
        {
            return key;
        }

        V getValue() const
        {
            return value;
        }
    };

	int MaxSize,Size;
	LinkedList<Entry> *List;
	
	int calc(int x) const{
		return (x%MaxSize+MaxSize)%MaxSize;
	}
	
	void DoubleSpace(){
		MaxSize*=2;
		Size=0;
		LinkedList<Entry> *tmp=List;
		List=new LinkedList<Entry>[MaxSize];
		for (int i=0;i<MaxSize/2;i++){
			while (tmp[i].size()){
				put(tmp[i].getFirst().key,tmp[i].getFirst().value);
				tmp[i].removeFirst();
			}
		}
		delete [] tmp;
	}
	
    class Iterator
    {
    public:
	
		int Now;
		typename LinkedList<Entry>::Iterator itr;
		const HashMap *Obj;
		
		Iterator(const HashMap *Class): Now(0), Obj(Class), itr(Class->List[0].iterator()){}
		
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
			if (itr.hasNext()) return 1;
			for (int i=Now+1;i<Obj->MaxSize;i++)
				if (Obj->List[i].size())
					return 1;
			return 0;
		}

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const Entry &next() {
			//printf("%d\n",Now);
			if (hasNext()){
				if (itr.hasNext()){
					return itr.next();
				}
				for (int i=Now+1;i<Obj->MaxSize;i++)
					if (Obj->List[i].size()){
						Now=i;
						itr=Obj->List[Now].iterator();
						return itr.next(); 
					}
			}
			else throw ElementNotExist();
		}
    };

    /**
     * TODO Constructs an empty hash map.
     */
    HashMap() { 
		MaxSize=10;
		Size=0;
		List=new LinkedList<Entry>[MaxSize];
	}

    /**
     * TODO Destructor
     */
    ~HashMap() { 
		delete	[] List;
	}

    /**
     * TODO Assignment operator
     */
    HashMap &operator=(const HashMap &x) { 
		if (&x==this) return *this;
		while (MaxSize<x.MaxSize)
			DoubleSpace();
		for (int i=0;i<MaxSize;i++)
			List[i]=x.List[i];
		Size=x.Size;
		return	*this;	
	}

    /**
     * TODO Copy-constructor
     */
    HashMap(const HashMap &x) { 
		MaxSize=10;
		Size=0;
		List=new LinkedList<Entry>[MaxSize];
		*this=x;
	}

    /**
     * TODO Returns an iterator over the elements in this map.
     */
    Iterator iterator() const {
		return Iterator(this);
	}

    /**
     * TODO Removes all of the mappings from this map.
     */
    void clear() {
		for (int i=0;i<MaxSize;i++)
			List[i].clear();
		Size=0;
	}

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key) const {
		int t=calc(H::hashCode(key));
		typename LinkedList<Entry>::Iterator itr=List[t].iterator();
		for (int i=1;i<=List[t].size();i++)
			if (itr.next().key==key) return 1;
		return 0;
	}

    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const {
		for (int i=0;i<MaxSize;i++){
			typename LinkedList<Entry>::Iterator itr=List[i].iterator();
			for (int j=1;j<=List[i].size();j++)
				if (itr.next().value==value) return 1;
		}
		return 0;
	}

    /**
     * TODO Returns a const reference to the value to which the specified key is mapped.
     * If the key is not present in this map, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &get(const K &key) const {
		int t=calc(H::hashCode(key));
		typename LinkedList<Entry>::Iterator itr=List[t].iterator();
		for (int i=1;i<=List[t].size();i++){
			Entry *tmp=new Entry(itr.next());
			if (tmp->key==key) return tmp->value;
		}	
		throw ElementNotExist();
	}

    /**
     * TODO Returns true if this map contains no key-value mappings.
     */
    bool isEmpty() const {
		return Size==0;
	}

    /**
     * TODO Associates the specified value with the specified key in this map.
     */
    void put(const K &key, const V &value) {
		if (Size>=MaxSize/5) DoubleSpace();
		int t=calc(H::hashCode(key));
		typename LinkedList<Entry>::Iterator itr=List[t].iterator();
		for (int i=1;i<=List[t].size();i++){
			Entry *tmp=new Entry(itr.next());
			if (tmp->key==key) 
				itr.remove();
		}	
		List[t].add(Entry(key,value));
		Size++;
	}

    /**
     * TODO Removes the mapping for the specified key from this map if present.
     * If there is no mapping for the specified key, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void remove(const K &key) {
		int t=calc(H::hashCode(key));
		typename LinkedList<Entry>::Iterator itr=List[t].iterator();
		for (int i=1;i<=List[t].size();i++){
			if (itr.next().key==key) {
				itr.remove();
				Size--;
				return;
			}
		}	
		throw ElementNotExist();
	}

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const {
		return Size;
	}
};

#endif
