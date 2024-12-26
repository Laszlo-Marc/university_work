from enum import Enum
import re

from finiteautomata import FiniteAutomata
from symboltables import SymbolTableConstants, SymbolTableIdentifiers


class TokenTypes(Enum):
    IDENTIFIER = 0
    CONSTANT = 1
    OPERATOR = 2
    RESERVED_WORD = 3
    SEPARATOR = 4


class LexicalAnalyzer:
    """ class LexicalAnalyzer for implementing the scanning algorithm

        Methods:
            __init__:
                - initializes the analyzer with the source code file and token file paths.
            - scan_file:
                - analyzes the source code, generates PIF, and manages symbol tables
            - get_tokens:
                - parses the token definitions from the token file and populates dictionaries for reserved words, operators, and separators
            - is_identifier(string):
                - checks if a string is a valid identifier
            - is_constant(string):
                - checks if a string is a valid constant
            -is_string_literal
                -check if a string is actually a string constant
            -handle_string_constant
                -handles the string constant
        """
    def __init__(self, filename, tokens_file):
        self.filename = filename
        self.tokens_file = tokens_file
        self.constant_table = SymbolTableConstants()
        self.identifiers_table = SymbolTableIdentifiers()
        self.pif = []
        self.reserved_words = {}
        self.operators = {}
        self.separators = {}
        self.get_tokens()
        self.constants_count = 0
        self.finite_automata = FiniteAutomata('FA.in')


    def scan_file(self):
        self.finite_automata.print_fa()
        with open(self.filename, 'r') as program:
            line_count = 0
            for line in program:
                line_count += 1
                line = line.rstrip('\n')
                operators_and_separators = r'(;|==|=|!=|\+=|-=|\*=|\/=|<=|>=|[\+\-\*=\/<>!;\[\]\{\}\(\),;]|\|\||&&)'

                for word_with_sep_and_op in re.split(operators_and_separators, line):
                    # Clean up whitespace and handle empty strings
                    word_with_sep_and_op = word_with_sep_and_op.strip()
                    if not word_with_sep_and_op:
                        continue


                    for word in word_with_sep_and_op.split():
                            if self.is_string_literal(word_with_sep_and_op):
                                self.handle_string_constant(word_with_sep_and_op)
                            # Check reserved words
                            if word in self.reserved_words.keys():
                                self.pif.append((word, 0))

                            # Check operators
                            elif word in self.operators.keys():
                                self.pif.append((word, 0))

                            # Check separators
                            elif word in self.separators.keys():
                                self.pif.append((word, 0))

                            # Check identifiers
                            elif self.is_identifier(word):
                                position = self.identifiers_table.get_position(word)
                                if position is None:
                                    position= self.identifiers_table.add_identifier(word)

                                self.pif.append(("id",position))


                            # Check constants
                            elif self.is_constant(word):
                                position = self.constant_table.get_position(word)
                                if position is None:

                                    self.constant_table.add_constant(word, self.constants_count)
                                    position = self.constant_table.get_position(word)
                                    self.constants_count += 1
                                if position is not None:
                                    self.pif.append((TokenTypes.CONSTANT.value, position))
                                else:
                                    print(f"Error: Failed to add constant '{word}' to the symbol table.")

                            else:
                                print(f"Lexical error at line {line_count}: '{word}' is not recognized.")
                                return

        print('Lexically correct')
        self.finite_automata.print_fa()

        with open('ST.out', 'w') as output:
            output.write(str(self.identifiers_table.symboltable))
            print(self.identifiers_table.symboltable)
            output.write("\n")
            output.write(str(self.constant_table.symboltable))
            print(self.constant_table.symboltable)

        with open('PIF.out', 'w') as output:
            for key, value in self.pif:
                output.write(f"{key} - {value}\n")

    def get_tokens(self):
        to_add_in = TokenTypes.RESERVED_WORD
        line_nr = 2
        with open(self.tokens_file, 'r') as token_file:
            for line in token_file:
                line = line.strip()
                if line == '[reserved_words]':
                    continue
                if line == '[operators]':
                    to_add_in = TokenTypes.OPERATOR
                    continue
                if line == '[separators]':
                    to_add_in = TokenTypes.SEPARATOR
                    continue
                if to_add_in == TokenTypes.RESERVED_WORD:
                    self.reserved_words[line] = line_nr
                if to_add_in == TokenTypes.OPERATOR:
                    self.operators[line] = line_nr
                if to_add_in == TokenTypes.SEPARATOR:
                    self.separators[line] = line_nr
                line_nr += 1

    def is_identifier(self, string):
        return self.finite_automata.check_word_if_identifier(string)

    def is_constant(self, string):
        pattern_char = re.compile("'[a-zA-Z0-9]'")
        pattern_string = re.compile('"[a-zA-Z0-9]*"')
        if self.finite_automata.check_word_if_integer_constant(string) or pattern_char.fullmatch(
                string) or pattern_string.fullmatch(string):
            return True
        return False

    def is_string_literal(self, string):
        return self.finite_automata.check_word_if_string_constant(string)

    def handle_string_constant(self, string):
        string = string.strip('"').strip("'")
        if self.constant_table.get_position(string) is None:
            print(f"Adding string constant '{string}' to symbol table.")
            self.constant_table.add_constant(string, self.constants_count)
            self.pif.append((TokenTypes.CONSTANT.value, self.constant_table.get_position(string)))
            self.constants_count += 1
