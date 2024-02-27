#include "SortedSetIterator.h"
//Best case: O(1)
//Worst case: O(log n)
//Average case: O(log n)
SortedSetIterator::SortedSetIterator(const SortedSet& s) : set(s) {
    first();
}
//Best case: O(1)
//Worst case: O(log n)
//Average case: O(log n)
void SortedSetIterator::first() {
    stack = std::stack<int>();
    currentNode = set.root;
    while (currentNode != -1) {
        stack.push(currentNode);
        currentNode = set.elements[currentNode].left;
    }
    if (!stack.empty()) {
        currentNode = stack.top();
    }
    else {
        currentNode = -1;
    }
}
//Best case: O(1)
//Worst case: O(log n)
//Average case: O(log n)
void SortedSetIterator::next() {
    if (!valid()) {
        throw std::exception("Invalid iterator state");
    }

    int top = stack.top();
    stack.pop();

    if (set.elements[top].right != -1) {
        int node = set.elements[top].right;
        while (node != -1) {
            stack.push(node);
            node = set.elements[node].left;
        }
    }

    if (!stack.empty()) {
        currentNode = stack.top();
    }
    else {
        currentNode = -1;
    }
}
//O(1)
TElem SortedSetIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception("Invalid iterator state");
    }

    return set.elements[currentNode].info;
}
//O(1)
bool SortedSetIterator::valid() const {
    return currentNode != -1 && !stack.empty();
}

