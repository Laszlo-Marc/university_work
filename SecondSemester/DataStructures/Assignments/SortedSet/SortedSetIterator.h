#pragma once

#include "SortedSet.h"
#include <stack>

class SortedSetIterator {
private:
    const SortedSet& set;
    std::stack<int> stack;
    int currentNode;

public:
    SortedSetIterator(const SortedSet& s);
    void first();
    void next();
    TElem getCurrent() const;
    bool valid() const;
    
};
