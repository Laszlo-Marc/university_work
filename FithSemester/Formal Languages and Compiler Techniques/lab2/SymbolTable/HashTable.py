import copy

"""
Hash Table Implementation with Chaining for Collision Resolution

Classes:
    - Node: Represents an individual element with a key-value pair.
    - HashTable: Manages the hash table, including insertion, retrieval, and dynamic resizing.

Node Class:
    Attributes:
        - key: The unique identifier for the node.
        - value: The data associated with the key.
        - next: A pointer to the next node in case of a hash collision.

HashTable Class:
    Attributes:
        - capacity: Maximum number of buckets in the table. Starts at 2 and doubles as needed.
        - element_nr: The current number of elements stored in the table.
        - element_list: An array representing the hash table, where each index holds a linked list (chain) of Node objects.

    Methods:
        - __init__(): Initializes a new hash table with a default capacity of 2.
        - hash(value): Computes the hash index for a given key, supporting both integers and strings.
        - insert(key, value): Inserts a new key-value pair into the table, resizing if load factor exceeds 0.5.
        - get(key): Retrieves the value associated with a given key or returns None if not found.
        - resize_and_rehash(): Doubles the table's capacity and rehashes all elements to fit the new size.
"""

class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


class HashTable:
    def __init__(self):
        self.capacity = 2
        self.element_nr = 0
        self.element_list = [None] * 2

    def hash(self, value):
        if isinstance(value, int):
            return value % self.capacity

        sum = 0
        for l in value:
            sum += ord(l)
        return sum % self.capacity

    def insert(self, key):
        value =[]
        if self.element_nr and (self.capacity // self.element_nr < 2):
            self.resize_and_rehash()

        element = self.element_list[self.hash(key)]
        value.append(self.hash(key))
        if element is None:
            value = [self.hash(key),0]
            self.element_list[self.hash(key)] = Node(key, value)
            self.element_nr += 1
            return

        count=0
        while element.next is not None:
            element = element.next
            count+=1
        value.append(count)
        element.next = Node(key, value)
        self.element_nr += 1


    def get(self, key):
        element = self.element_list[self.hash(key)]
        while element is not None:
            if element.key == key:
                return element.value
            element = element.next
        return None

    def resize_and_rehash(self):
        self.capacity *= 2
        # Create a new, empty list with doubled capacity
        old_element_list = self.element_list
        self.element_list = [None] * self.capacity
        self.element_nr = 0  # Reset element count, as `insert` will increment it

        for element in old_element_list:
            current = element
            while current is not None:
                # Re-insert using only the key, as `insert` recalculates value and position
                self.insert(current.key)
                current = current.next
