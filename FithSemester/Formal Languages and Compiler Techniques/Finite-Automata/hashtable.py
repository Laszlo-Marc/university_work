import string


class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


class HashTable:
    def __init__(self):
        self.capacity = 2
        self.element_nr = 0
        self.element_list = [None] * self.capacity  # Properly initialize

    def hash(self, value):
        if isinstance(value, int):
            return value % self.capacity
        return sum(ord(char) for char in value) % self.capacity

    def insert(self, key):
        if self.element_nr / self.capacity > 0.5:
            self.resize_and_rehash()
        position=0
        index = self.hash(key)
        if self.element_list[index] is None:
            self.element_list[index] = Node(key, index)
            self.element_nr += 1
            return (index,position)
        else:
            # Traverse and insert at the end of the chain
            current = self.element_list[index]
            while current is not None:
                if current.key == key:
                    return  # Avoid duplicates
                if current.next is None:
                    # Add new node to the end of the chain
                    current.next = Node(key, index)
                    self.element_nr += 1
                    position += 1
                    return (index,position)
                current = current.next


    def get(self, key):
        index = self.hash(key)
        current = self.element_list[index]
        while current is not None:
            if current.key == key:
                return current.value
            current = current.next
        return None

    def resize_and_rehash(self):
        self.capacity *= 2
        old_elements = self.element_list
        self.element_list = [None] * self.capacity
        self.element_nr = 0

        for element in old_elements:
            while element is not None:
                self.insert(element.key)  # Re-insert
                element = element.next

    def get_position(self, key):
        index = self.hash(key)
        current = self.element_list[index]
        position = 0
        while current is not None:
            if current.key == key:
                return (index, position)
            current = current.next
            position += 1



    def __str__(self):
        result = ""
        for element in self.element_list:
            current = element
            while current is not None:
                result += f" {self.get_position(current.key)}- {current.key}\n"
                current = current.next
        return result
