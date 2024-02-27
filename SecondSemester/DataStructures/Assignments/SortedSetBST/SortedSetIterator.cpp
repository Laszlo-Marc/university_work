#include "SortedSetIterator.h"
#include <exception>

using namespace std;


SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	//TODO - Implementation
    //push all the left nodes in the stack
    this->stack = new TElem[m.length];
    this->stackSize = 0;
    TElem current = this->multime.root;
    while (current != NULL_TELEM) {
        this->stack[this->stackSize++] = current;
        current = m.getLeft(current);
    }
}


void SortedSetIterator::first() {
	//TODO - Implementation
    TElem current = this->multime.root;
    while (current != NULL_TELEM) {
        this->stack[this->stackSize] = current;
        this->stackSize++;
        current = this->multime.getLeft(current);
    }
}


void SortedSetIterator::next() {
	//TODO - Implementation
    if(this->valid()) {
        TElem current = this->stack[--this->stackSize];
        if (this->multime.getRight(current) != NULL_TELEM) {
            current = this->multime.getRight(current);
            while (current != NULL_TELEM) {
                this->stack[this->stackSize++] = current;
                current = this->multime.getLeft(current);
            }
        }
    }
    else {
        throw exception();
    }
}


TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation
    if(this->valid()) {
        return this->stack[--this->stackSize];
    }
    else {
        throw exception();
    }
}

bool SortedSetIterator::valid() const {
	//TODO - Implementation
    if (this->stackSize == 0) {
        return false;
    }
    return true;
}

