#include "SMMIterator.h"
#include <stdexcept>
//Best case: O(1)
//Worst case: O(capacity)
//Average case: O(capacity)
SMMIterator::SMMIterator(const SortedMultiMap& map) : map(map), currentBucket(0), currentNode(nullptr) {
    first();
}
//Best case: O(1)
//Worst case: O(capacity)
//Average case: O(capacity)
void SMMIterator::first() {
    currentBucket = 0;
    currentNode = nullptr;

    while (currentBucket < map.capacity) {
        if (map.hashTable[currentBucket] != nullptr) {
            currentNode = map.hashTable[currentBucket];
            break;
        }
        currentBucket++;
    }
}
//Best case: O(1)
//Worst case: O(capacity)
//Average case: O(capacity)
void SMMIterator::next() {
    if (!valid()) {
        throw std::runtime_error("Invalid iterator!");
    }

    currentNode = currentNode->next;
    while (currentBucket < map.capacity) {
        if (currentNode != nullptr) {
            break;
        }
        currentBucket++;
        if (currentBucket < map.capacity) {
            currentNode = map.hashTable[currentBucket];
        }
    }
}
//O(1)
bool SMMIterator::valid() const {
    return currentNode != nullptr;
}
//O(1)
TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw std::runtime_error("Invalid iterator!");
    }
    return currentNode->element;
}