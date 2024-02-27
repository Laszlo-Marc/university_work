#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <cstring>
using namespace std;





SortedSet::SortedSet(Relation r) {
	//TODO - Implementation
    this->r = r;
    this->cap = 100;
    this->length=0;
    this->elems = new TElem[100];
    this->root = NULL_TELEM;
    memset(elems, NULL_TELEM, cap);
}


bool SortedSet::add(TComp elem) {
    if (this->cap == this->length) {
        resize();
    }
    if (search(elem)) {
        return false;
    }
    if (this->length == 0) { // case tree is empty
        this->root = elem;
        this->elems[0] = elem;
        this->length++;
        return true;
    }
    TElem current = this->root;
    while (current != NULL_TELEM) {
        if (r(elem, current)) {
            if (getLeft(current) == NULL_TELEM) {
                setLeft(current, elem);
                this->elems[length] = elem;
                this->length++;
                return true;
            }
            else {
                current = getLeft(current);
            }
        }
        else {
            if (getRight(current) == NULL_TELEM) {
                setRight(current, elem);
                this->elems[length] = elem;
                this->length++;
                return true;
            }
            else {
                current = getRight(current);
            }
        }
    }
    return false; // Element not added
}

bool SortedSet::remove(TComp elem) {
    if (!search(elem)) {
        return false; // Element not found
    }
    // Case 1: Remove a leaf
    if (getLeft(elem) == NULL_TELEM && getRight(elem) == NULL_TELEM) {
        if (getParent(elem) == NULL_TELEM) {
            root = NULL_TELEM;
        } else if (getLeft(getParent(elem)) == elem) {
            setLeft(getParent(elem), NULL_TELEM);
        } else {
            setRight(getParent(elem), NULL_TELEM);
        }
        this->elems[getIndex(elem)] = NULL_TELEM;
        this->length--;
        return true;
    }

    // Case 2: Remove a node with one child
    if (getLeft(elem) == NULL_TELEM) {
        if (getParent(elem) == NULL_TELEM) {
            root = getRight(elem);
        } else if (getLeft(getParent(elem)) == elem) {
            setLeft(getParent(elem), getRight(elem));
        } else {
            setRight(getParent(elem), getRight(elem));
        }
        this->elems[getIndex(elem)] = NULL_TELEM;
        this->length--;
        return true;
    }

    if (getRight(elem) == NULL_TELEM) {
        if (getParent(elem) == NULL_TELEM) {
            root = getLeft(elem);
        } else if (getLeft(getParent(elem)) == elem) {
            setLeft(getParent(elem), getLeft(elem));
        } else {
            setRight(getParent(elem), getLeft(elem));
        }
        this->elems[getIndex(elem)] = NULL_TELEM;
        this->length--;
        return true;
    }

    // Case 3: Remove a node with two children
    TElem current = getRight(elem);
    while (getLeft(current) != NULL_TELEM) {
        current = getLeft(current);
    }
    TElem minimum = current;

    this->elems[getIndex(elem)] = minimum;
    if (getParent(minimum) == elem) {
        setRight(minimum, getRight(elem));
        if (getParent(elem) == NULL_TELEM) { //remove the root
            root = minimum;
        } else if (getLeft(getParent(elem)) == elem) {
            setLeft(getParent(elem), minimum);
        } else {
            setRight(getParent(elem), minimum);
        }
        this->elems[getIndex(elem)] = NULL_TELEM;
        this->length--;
        return true;
    }

    setLeft(getParent(minimum), getRight(minimum));
    setRight(minimum, getRight(elem));

    if (getParent(elem) == NULL_TELEM) {
        root = minimum;
    } else if (getLeft(getParent(elem)) == elem) {
        setLeft(getParent(elem), minimum);
    } else {
        setRight(getParent(elem), minimum);
    }

    this->elems[getIndex(elem)] = NULL_TELEM;
    this->length--;
    return true;
}


//
//bool SortedSet::remove(TComp elem) {
//    if (this->length == 0) {
//        return false;
//    }
//    if(!search(elem)){
//        return false;
//    }
//    TElem current = this->root;
//    TElem parent = NULL_TELEM;
//    while (current != NULL_TELEM) {
//        if (current == elem) {
//            if (getLeft(current) == NULL_TELEM && getRight(current) == NULL_TELEM) {
//                if (parent == NULL_TELEM) {
//                    root = NULL_TELEM;
//                }
//                else if (getLeft(parent) == current) {
//                    setLeft(parent, NULL_TELEM);
//                }
//                else {
//                    setRight(parent, NULL_TELEM);
//                }
//                delete[] elems;
//                length--;
//                return true;
//            }
//            else if (getLeft(current) != NULL_TELEM && getRight(current) == NULL_TELEM) {
//                if (parent == NULL_TELEM) {
//                    root = getLeft(current);
//                }
//                else if (getLeft(parent) == current) {
//                    setLeft(parent, getLeft(current));
//                }
//                else {
//                    setRight(parent, getLeft(current));
//                }
//                delete[] elems;
//                length--;
//                return true;
//            }
//            else if (getLeft(current) == NULL_TELEM && getRight(current) != NULL_TELEM) {
//                if (parent == NULL_TELEM) {
//                    root = getRight(current);
//                }
//                else if (getLeft(parent) == current) {
//                    setLeft(parent, getRight(current));
//                }
//                else {
//                    setRight(parent, getRight(current));
//                }
//                delete[] elems;
//                length--;
//                return true;
//            }
//            else {
//                TElem successor = getRight(current);
//                TElem successorParent = current;
//                while (getLeft(successor) != NULL_TELEM) {
//                    successorParent = successor;
//                    successor = getLeft(successor);
//                }
//                if (successorParent != current) {
//                    setLeft(successorParent, getRight(successor));
//                    setRight(successor, getRight(current));
//                }
//                if (parent == NULL_TELEM) {
//                    root = successor;
//                }
//                else if (getLeft(parent) == current) {
//                    setLeft(parent, successor);
//                }
//                else {
//                    setRight(parent, successor);
//                }
//                setLeft(successor, getLeft(current));
//                delete[] elems;
//                length--;
//                return true;
//            }
//        }
//        parent = current;
//        if (r(elem, current)) {
//            current = getLeft(current);
//        }
//        else {
//            current = getRight(current);
//        }
//    }
//}


bool SortedSet::search(TComp elem) const {
    TElem current = this->root;
    while (current != NULL_TELEM) {
        if (current == elem)
            return true;
        else {
            if (r(elem, current))
                current = getLeft(current);
            else
                current = getRight(current);
        }
    }
    return false;
}


int SortedSet::size() const {
	//TODO - Implementation
	return this->length;
}



bool SortedSet::isEmpty() const {
	//TODO - Implementation
	return this->length==0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	//TODO - Implementation
    delete[] this->elems;
}

int SortedSet::getIndex(TElem elem) const{
    for (int i = 0; i < length; i++) {
        if (elems[i] == elem) {
            return i;
        }
    }
    return -1;
}


TElem SortedSet::getLeft(TElem elem) const{
    int index = getIndex(elem);
    if (index != -1 && (2 * index + 1) < length) {
        return elems[2 * index + 1];
    }
    return NULL_TELEM;
}

TElem SortedSet::getRight(TElem elem) const{
    int index = getIndex(elem);
    if (index != -1 && (2 * index + 2) < length) {
        return elems[2 * index + 2];
    }
    return NULL_TELEM;
}

TElem SortedSet::getParent(TElem elem) const{
    int index = getIndex(elem);
    if (index != -1 && index != 0) {
        return elems[(index - 1) / 2];
    }
    return NULL_TELEM;
}

void SortedSet::setLeft(TElem elem, TElem left) const{
    int index = getIndex(elem);
    if (index != -1 && (2 * index + 1) < length) {
        elems[2 * index + 1] = left;
    }
}

void SortedSet::setRight(TElem elem, TElem right) const{
    int index = getIndex(elem);
    if (index != -1 && (2 * index + 2) < length) {
        elems[2 * index + 2] = right;
    }
}


