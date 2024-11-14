from structures.HashTable import HashTable
"""
Symbol Table for Constants and Identifiers

This module defines two classes, `SymbolTableConstants` and `SymbolTableIdentifiers`, to manage constants and identifiers using a hash table for efficient storage and retrieval.

Classes:
    - SymbolTableConstants: Manages constant values in a hash table.
    - SymbolTableIdentifiers: Manages identifiers and their associated values in a hash table.

Requirements:
    - HashTable: Imported from structures.HashTable, which provides a basic hash table implementation with insert and get methods.

SymbolTableConstants Class:
    Attributes:
        - symboltable: An instance of `HashTable` used to store constants.

    Methods:
        - add_constant(identifier, value): Adds a constant with a specified identifier and value to the symbol table.
        - get_constant(identifier): Retrieves the value associated with the specified constant identifier. Returns None if the constant is not found.

SymbolTableIdentifiers Class:
    Attributes:
        - symboltable: An instance of `HashTable` used to store identifiers.

    Methods:
        - add_identifier(identifier, value): Adds an identifier with a specified value to the symbol table.
        - get_identifier_value(identifier): Retrieves the value associated with the specified identifier. Returns None if the identifier is not found.
"""


class SymbolTableConstants:
    def __init__(self):
        self.symboltable = HashTable()

    def add_constant(self, identifier, value):
        self.symboltable.insert(identifier, value)

    def get_constant(self, identifier):
        return self.symboltable.get(identifier)


class SymbolTableIdentifiers:
    def __init__(self):
        self.symboltable = HashTable()

    def add_identifier(self, identifier, value):
        self.symboltable.insert(identifier, value)

    def get_identifier_value(self, identifier):
        return self.symboltable.get(identifier)