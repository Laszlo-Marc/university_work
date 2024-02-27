#include "SortedSet.h"
#include "SortedSetIterator.h"
//O(capacity)
SortedSet::SortedSet(Relation r) {
    capacity = 10;
    elements = new Node[capacity];
    root = -1;
    firstEmpty = 0;
    actualSize = 0;
    relation = r;

    for (int i = 0; i < capacity - 1; i++) {
        elements[i].left = i + 1;
    }

    elements[capacity - 1].left = -1;
}
//O(1)
SortedSet::~SortedSet() {
    delete[] elements;
}
void SortedSet::intersection(const SortedSet& s)
{
   
}
//Best case: O(1)
//Worst case: O(log n)
//Average case: O(log n)
bool SortedSet::add(TComp e) {
    // Check if the element already exists in the set
    if (search(e)) {
        return false; // Element already exists, return false
    }

    // If there are no more empty positions in the array, resize it
    if (firstEmpty == -1) {
        resizeArray();
    }

    int currentNode = root;
    int parentNode = -1;

    // Find the appropriate position to insert the new element
    while (currentNode != -1) {
        parentNode = currentNode;
        if (relation(elements[currentNode].info, e)) {
            // New element is greater than the current node, go to the right subtree
            currentNode = elements[currentNode].right;
        }
        else {
            // New element is less than or equal to the current node, go to the left subtree
            currentNode = elements[currentNode].left;
        }
    }

    int newNode = allocateNode(e);
    if (parentNode == -1) {
        // Tree is empty, make the new node the root
        root = newNode;
    }
    else if (relation(elements[parentNode].info, e)) {
        // New element is greater than the parent node, insert it as the right child
        elements[parentNode].right = newNode;
    }
    else {
        // New element is less than or equal to the parent node, insert it as the left child
        elements[parentNode].left = newNode;
    }

    actualSize++;
    return true; // Element successfully added
}

//Best case: O(1)
//Worst case: O(log n)
//Average case: O(log n)
bool SortedSet::remove(TComp e) {
    int currentNode = root;
    int parentNode = -1;

    // Find the node with the given element 'e' and its parent node
    while (currentNode != -1 && elements[currentNode].info != e) {
        parentNode = currentNode;
        if (relation(elements[currentNode].info, e)) {
            currentNode = elements[currentNode].right;
        }
        else {
            currentNode = elements[currentNode].left;
        }
    }

    if (currentNode == -1) {
        // Node with 'e' not found, return false
        return false;
    }

    // Case 1: Node to be removed has no left child
    if (elements[currentNode].left == -1) {
        if (parentNode == -1) {
            // Node is the root
            root = elements[currentNode].right;
        }
        else if (elements[parentNode].left == currentNode) {
            // Node is the left child of its parent
            elements[parentNode].left = elements[currentNode].right;
        }
        else {
            // Node is the right child of its parent
            elements[parentNode].right = elements[currentNode].right;
        }
    }
    // Case 2: Node to be removed has no right child
    else if (elements[currentNode].right == -1) {
        if (parentNode == -1) {
            // Node is the root
            root = elements[currentNode].left;
        }
        else if (elements[parentNode].left == currentNode) {
            // Node is the left child of its parent
            elements[parentNode].left = elements[currentNode].left;
        }
        else {
            // Node is the right child of its parent
            elements[parentNode].right = elements[currentNode].left;
        }
    }
    // Case 3: Node to be removed has both left and right children
    else {
        int substituteNode = elements[currentNode].right;
        int substituteParent = currentNode;

        // Find the leftmost node in the right subtree of the node to be removed
        while (elements[substituteNode].left != -1) {
            substituteParent = substituteNode;
            substituteNode = elements[substituteNode].left;
        }

        if (substituteParent != currentNode) {
            // Substitute node is not the immediate right child of the node to be removed
            elements[substituteParent].left = elements[substituteNode].right;
        }
        else {
            // Substitute node is the immediate right child of the node to be removed
            elements[substituteParent].right = elements[substituteNode].right;
        }

        // Replace the node to be removed with the substitute node
        elements[currentNode].info = elements[substituteNode].info;
        deallocateNode(substituteNode);
    }

    actualSize--;
    return true;
}


bool SortedSet::search(TElem elem) const {
    int currentNode = root;

    // Traverse the tree until we reach a leaf node or find the element
    while (currentNode != -1) {
        if (elements[currentNode].info == elem) {
            return true; // Element found, return true
        }
        else if (relation(elements[currentNode].info, elem)) {
            // The element we're looking for is greater than the current node,
            // so we continue searching in the right subtree
            currentNode = elements[currentNode].right;
        }
        else {
            // The element we're looking for is less than the current node,
            // so we continue searching in the left subtree
            currentNode = elements[currentNode].left;
        }
    }

    return false; // Element not found
}

//O(1)
int SortedSet::size() const {
    return actualSize;
}
//O(1)
bool SortedSet::isEmpty() const {
    return actualSize == 0;
}
//O(1)
SortedSetIterator SortedSet::iterator() const {
    return SortedSetIterator(*this);
}
//O(1)
int SortedSet::allocateNode(TElem e) {
    int newPosition = firstEmpty;
    firstEmpty = elements[firstEmpty].left;
    elements[newPosition].info = e;
    elements[newPosition].left = -1;
    elements[newPosition].right = -1;
    return newPosition;
}
//O(1)
void SortedSet::deallocateNode(int position) {
    elements[position].left = firstEmpty;
    firstEmpty = position;
}
//O(capacity)
void SortedSet::resizeArray() {
    int newCapacity = capacity * 2;
    Node* newElements = new Node[newCapacity];
    for (int i = 0; i < capacity; i++) {
        newElements[i] = elements[i];
    }
    for (int i = capacity; i < newCapacity - 1; i++) {
        newElements[i].left = i + 1;
    }
    newElements[newCapacity - 1].left = -1;

    delete[] elements;
    elements = newElements;
    firstEmpty = capacity;
    capacity = newCapacity;
}
