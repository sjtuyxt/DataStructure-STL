/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"
#include<cstring>
/**
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K, class V>
class TreeMap
{
public:

    class Entry
    {
        friend class TreeMap<K,V>;
    private:
        K key;
        V value;
        Entry *Father,*Son[2];
        int bj;
    public:
        Entry(K k, V v)
        {
            key = k;
            value = v;
            Father=Son[0]=Son[1]=NULL;
            bj=0;
        }
        Entry()
        {
            Father=Son[0]=Son[1]=NULL;
            bj=0;
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
    
	Entry *Root,*Min,*Max;
    int Cnt;
	
	void put(const K &key, const V &value)
	{
		if (containsKey(key))
		{
			Entry *tmp=find(Root->Son[1],key);
			Entry *tmp1=new Entry(key,value);
			if (tmp->Son[0]) tmp->Son[0]->Father=tmp1;
			if (tmp->Son[1]) tmp->Son[1]->Father=tmp1;
			if (tmp==tmp->Father->Son[1]) tmp->Father->Son[1]=tmp1;
			else tmp->Father->Son[0]=tmp1;
			tmp1->Father=tmp->Father;
			tmp1->Son[1]=tmp->Son[1];
			tmp1->Son[0]=tmp->Son[0];
			delete tmp;
		}
		else
		{
			Entry *tmp=new Entry(key,value);
			insert(Root,tmp);
			Cnt++;
		}
	}
	
    void clearTree(Entry *p)
    {
        if (!p) return;
        Entry **List=new Entry*[Cnt+10];
        int Head=0,Tail=0;
        List[Head]=p;
        Entry *tmp;
        while (Head<=Tail)
        {
            tmp=List[Head];
            if (tmp->Son[0]) List[++Tail]=tmp->Son[0];
            if (tmp->Son[1]) List[++Tail]=tmp->Son[1];
            delete tmp;
            Head++;
        }
        delete [] List;
    }
	
    int f(Entry *p) const
    {
        return p==p->Father->Son[1];
    }
	
    void rotate(Entry *p) const
    {
        Entry *Father=p->Father;
        int Turn=f(p);
        Father->Son[Turn]=p->Son[1^Turn];
        if (p->Son[1^Turn]) 
			p->Son[1^Turn]->Father=Father;
        p->Father=Father->Father;
        if (Father->Father) 
			Father->Father->Son[f(Father)]=p;
        p->Son[1^Turn]=Father;
        Father->Father=p;
    }
	
    void Splay(Entry *p,Entry *Root) const
    {
        if (!p || !Root || p==Root) return;
        Entry *Father=Root->Father;
        while (p->Father!=Father)
        {
            if (p->Father->Father==Father) rotate(p);
            else if (f(p)==f(p->Father))
            {
                rotate(p->Father);
                rotate(p);
            }
            else
            {
                rotate(p);
                rotate(p);
            }
        }
    }
	
    Entry *find(Entry *p,K key) const
    {
        Entry *tmp;
        while (p)
        {
            tmp=p;
            if (p->bj==0 && (!(p->key<key)) && (!(key<p->key))) break;
            if (p->bj<0 || (p->bj==0 && p->key<key)) p=p->Son[1];
            else p=p->Son[0];
        }
        Splay(tmp,Root->Son[1]);
        if (tmp->bj==0 && (!(tmp->key<key)) && (!(key<tmp->key))) return tmp;
        return NULL;
    }
	
    Entry *search(Entry *p,V value) const
    {
        if (!p) return NULL;
        Entry **List=new Entry*[Cnt+10];
        int Head=0,Tail=0;
        List[Head]=p;
        Entry *tmp;
        while (Head<=Tail)
        {
            tmp=List[Head];
            if (tmp->value==value && tmp->bj==0) break;
            if (tmp->Son[0]) 
				List[++Tail]=tmp->Son[0];
            if (tmp->Son[1]) 
				List[++Tail]=tmp->Son[1];
            Head++;
        }
        delete [] List;
        if (tmp->value==value && tmp->bj==0) return tmp;
        return NULL;
    }
	
    void insert(Entry *p,Entry *q)
    {
        Entry *tmp;
        while (p)
        {
            tmp=p;
            if ((p->bj<q->bj) || (p->bj==q->bj && p->key<q->key)) p=p->Son[1];
            else p=p->Son[0];
        }
        q->Father=tmp;
        if ((tmp->bj<q->bj) || (tmp->bj==q->bj && tmp->key<q->key)) tmp->Son[1]=q;
        else tmp->Son[0]=q;
        Splay(q,Root->Son[1]);
    }
	
    class Iterator
    {
    public:
	
        Entry *Next,*Root,*Min,*Max;
        const TreeMap *Obj;
		
        Iterator(const TreeMap *Class)
        {
            Obj=Class;
            Root=Class->Root;
            Min=Class->Min;
            Max=Class->Max;
            Obj->Splay(Min,Root->Son[1]);
            Next=Min->Son[1];
            while (Next->Son[0]) 
				Next=Next->Son[0];
            Obj->Splay(Next,Root->Son[1]);
        }
        /**
         * TODO Returns true if the iteration has more Listents.
         */
        bool hasNext()
        {
            return Next!=Max;
        }

        /**
         * TODO Returns the next Listent in the iteration.
         * @throw ElementNotExist exception when hasNext() == Fatherlse
         */
        const Entry &next()
        {
            if (hasNext())
            {
                Entry *tmp=Next;
                Obj->Splay(Next,Root->Son[1]);
                Obj->Splay(Max,Root->Son[1]->Son[1]);
                if (Next->Son[1]->Son[0]==NULL) Next=Max;
                else
                {
                    Entry *t=Next->Son[1]->Son[0];
                    while (t->Son[0]) t=t->Son[0];
                    Next=t;
                }
                return *tmp;
            }
            else throw ElementNotExist();
        }
    };
	
    /**
     * TODO Constructs an empty tree map.
     */
    TreeMap()
    {
        Cnt=0;
        Root=new Entry();
        Root->bj=-2;
        Min=new Entry();
        Min->bj=-1;
        Max=new Entry();
        Max->bj=1;
        insert(Root,Min);
        insert(Root,Max);
    }
    /**
     * TODO Destructor
     */
    ~TreeMap()
    {
        clearTree(Root);
    }

    /**
     * TODO Assignment operator
     */
    TreeMap &operator=(const TreeMap &x)
    {
        if (&x==this) return *this;
        int snt=x.size();
        clearTree(Root->Son[1]);
        Root->Son[1]=Root->Son[0]=NULL;
        Cnt=0;
        Min=new Entry();
        Min->bj=-1;
        Max=new Entry();
        Max->bj=1;
        insert(Root,Min);
        insert(Root,Max);
        Iterator itr=x.iterator();
        for (int i=0; i<snt; i++)
        {
            Entry Next=itr.next();
            put(Next.key,Next.value);
        }
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    TreeMap(const TreeMap &x)
    {
        Root=new Entry();
        Root->bj=-2;
        Cnt=0;
        *this=x;
    }

    /**
     * TODO Returns an iterator over the Listents in this map.
     */
    Iterator iterator() const
    {
        return Iterator(this);
    }

    /**
     * TODO Removes all of the mappings from this map.
     */
    void clear()
    {
        clearTree(Root->Son[1]);
        Root->Son[1]=Root->Son[0]=NULL;
        Cnt=0;
        Min=new Entry();
        Min->bj=-1;
        Max=new Entry();
        Max->bj=1;
        insert(Root,Min);
        insert(Root,Max);
    }

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key) const
    {
        return find(Root->Son[1],key)!=NULL;
    }
    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const
    {
        return search(Root->Son[1],value)!=NULL;
    }

    /**
     * TODO Returns a const reference to the value to which the specified key is mapped.
     * If the key is not present in this map, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &get(const K &key) const
    {
        if (containsKey(key))
        {
            Entry *t=find(Root->Son[1],key);
            return t->value;
        }
        else throw ElementNotExist();
    }

    /**
     * TODO Returns true if this map contains no key-value mappings.
     */
    bool isEmpty() const
    {
        return Cnt==0;
    }

    /**
     * TODO Associates the specified value with the specified key in this map.
     */


    /**
     * TODO Removes the mapping for the specified key from this map if present.
     * If there is no mapping for the specified key, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void remove(const K &key)
    {
        if (containsKey(key))
        {
            Entry *t=find(Root->Son[1],key);
            Splay(t,Root->Son[1]);
            Cnt--;
            Entry *t1=t->Son[0];
            while (t1->Son[1]) 
				t1=t1->Son[1];
            Entry *t2=t->Son[1];
            while (t2->Son[0]) 
				t2=t2->Son[0];
            Splay(t1,Root->Son[1]);
            Splay(t2,Root->Son[1]->Son[1]);
            Root->Son[1]->Son[1]->Son[0]=NULL;
            delete t;
        }
        else throw ElementNotExist();
    }

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const
    {
        return Cnt;
    }
};

#endif
