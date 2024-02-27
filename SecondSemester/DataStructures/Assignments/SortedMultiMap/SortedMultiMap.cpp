#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <stdexcept>
//O(capacity)
SortedMultiMap::SortedMultiMap(Relation r) : capacity(3), actualSize(0), loadFactor(0.7), relation(r) {
    hashTable = new Node * [capacity];
    for (int i = 0; i < capacity; i++) {
        hashTable[i] = nullptr;
    }
}
//O(1)
int SortedMultiMap::hash(TKey key) const {
    if (key >= 0) {
        return key % capacity;
    }
    else {
        return (key % capacity + capacity) % capacity;
    }
}
//O(capacity+actualSize)
void SortedMultiMap::resizeAndRehash() {
    int newCapacity = 3 * capacity;
    Node** newHashTable = new Node * [newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newHashTable[i] = nullptr;
    }

    for (int i = 0; i < capacity; i++) {
        Node* current = hashTable[i];
        while (current != nullptr) {
            Node* next = current->next;
            int newHash = std::abs(current->element.first % newCapacity);
            current->next = newHashTable[newHash];
            newHashTable[newHash] = current;
            current = next;
        }
    }

    delete[] hashTable;
    hashTable = newHashTable;
    capacity = newCapacity;
}

Node* SortedMultiMap::findNode(TKey key, TValue value) const {
    int bucket = hash(key);
    Node* current = hashTable[bucket];
    while (current != nullptr) {
        if (current->element.first == key && current->element.second == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
//Best case:O(1)
//Worst case:O(actualSize)
void SortedMultiMap::add(TKey c, TValue v) {
    /*
     if (actualSize >= loadFactor * capacity) {
        resizeAndRehash();
    }

    int bucket = hash(c);
    Node* newNode = new Node(std::make_pair(c, v));
    Node* current = hashTable[bucket];
    while (current != nullptr && !relation(current->element.first, c)) {
        current = current->next;
        newNode->next = hashTable[bucket];
        hashTable[bucket] = newNode;
    }
    
    actualSize++;
    */
    if (actualSize >= loadFactor * capacity) {
        resizeAndRehash();
    }

    int bucket = hash(c);
    Node* newNode = new Node(std::make_pair(c, v));

    if (hashTable[bucket] == nullptr || relation(hashTable[bucket]->element.first, c)) {
        // If the bucket is empty or the sorting relation is satisfied with the current head node,
        // insert the new node at the beginning of the bucket
        newNode->next = hashTable[bucket];
        hashTable[bucket] = newNode;
    }
    else {
        // If the sorting relation is not satisfied with the current head node,
        // find the appropriate position to insert the new node while maintaining the sorted order
        Node* current = hashTable[bucket];
        while (current->next != nullptr && !relation(current->next->element.first, c)) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    actualSize++;
}


//Best case:O(1)
//Worst case:O(actualSize)
std::vector<TValue> SortedMultiMap::search(TKey c) const {
    std::vector<TValue> values;
    
    int bucket = hash(c);
    Node* current = hashTable[bucket];
    while (current != nullptr) {
        if (relation(current->element.first, c)) {
            values.push_back(current->element.second);
        }
        current = current->next;
    }
    return values;
}
//Best case:O(1)
//Worst case:O(actualSize)
bool SortedMultiMap::remove(TKey c, TValue v) {
    int bucket = hash(c); // Calculate the bucket index using the hash function
    Node* current = hashTable[bucket]; // Get the first node in the bucket
    Node* prev = nullptr; // Track the previous node

    while (current != nullptr) {
        if (current->element.first == c && current->element.second == v) {
            // Found the node with matching key-value pair

            if (prev == nullptr) {
                hashTable[bucket] = current->next; // Update the bucket's first node
            }
            else {
                prev->next = current->next; // Update the previous node's next pointer
            }

            delete current; // Delete the node
            actualSize--; // Update the size
            return true; // Return true to indicate successful removal
        }

        prev = current; // Move the prev pointer
        current = current->next; // Move to the next node
    }

    return false; // Node not found, return false
}

//O(1)
int SortedMultiMap::size() const {
    return actualSize;
}
//O(1)
bool SortedMultiMap::isEmpty() const {
    return actualSize == 0;
}
//O(1)
SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}
//Best case:O(1)
//Worst case:O(actualSize)
void SortedMultiMap::replace(TKey k, TValue oldValue, TValue newValue) {
    int bucket = hash(k);
    Node* current = hashTable[bucket];

    while (current != nullptr) {
        if (current->element.first == k && current->element.second == oldValue) {
            current->element.second = newValue;
            return;
        }
        current = current->next;
    }
}
//O(capacity+actualSize)
SortedMultiMap::~SortedMultiMap() {
    for (int i = 0; i < capacity; i++) {
        Node* current = hashTable[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] hashTable;
}