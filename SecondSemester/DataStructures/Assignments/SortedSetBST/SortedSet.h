#pragma once
#include <iostream>
using namespace std;
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;


class SortedSet {
	friend class SortedSetIterator;
private:
	//TODO - Representation
    Relation r;
    TElem* elems;
    int cap;
    int length;
    TElem root;
    //helper functions
    void resize(){
        TElem* newElems = new TElem[cap*2];
        for(int i = 0; i < cap; i++)
            newElems[i] = elems[i];
        delete[] elems;
        elems = newElems;
        cap *= 2;
    }


public:
    //helper functions
    int getIndex(TElem elem) const;
    TElem getLeft(TElem elem) const;

    TElem getRight(TElem elem) const;
    TElem getParent(TElem elem) const;
    void setLeft(TElem elem, TElem left) const;
    void setRight(TElem elem, TElem right) const;

	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();


};
