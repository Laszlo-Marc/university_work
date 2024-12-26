import re


class FiniteAutomata:
    """
     A class to represent a Finite Automaton (FA) that reads its configuration
     from a file and can validate words as belonging to various categories
     (e.g., integer constants, string constants, and identifiers) based on
     the FA's transition rules.

     Attributes
     ----------
     states : list
         A list of states in the finite automaton.
     alphabet : list
         A list representing the input alphabet symbols for the finite automaton.
     transitions : dict
         A dictionary mapping transitions where keys are tuples (current_state, input_symbol)
         and values are the next states.
     initial_state : str
         The initial state of the finite automaton.
     final_states : list
         A list of final (accepting) states for the finite automaton.
     filename : str
         The name of the file containing the FA configuration.

     Methods
     -------
     __init__(_filename)
         Initializes a FiniteAutomata instance by reading data from the provided file.
     read_from_file()
         Reads the finite automaton's configuration from the specified file.
     print_fa()
         Prints the complete configuration of the finite automaton.
     start_menu()
         Displays a menu allowing the user to view different components of the finite automaton.
     check_word_if_integer_constant(word)
         Checks if the provided word is a valid integer constant based on the FA's transitions.
     check_word_if_string_constant(word)
         Checks if the provided word is a valid string constant based on the FA's transitions.
     check_word_if_identifier(word)
         Checks if the provided word is a valid identifier based on the FA's transitions.
     """

    def __init__(self, _filename):
        self.states = []
        self.alphabet = []
        self.transitions = {}
        self.initial_state = ""
        self.final_states = []
        self.filename = _filename
        self.read_from_file()

    def read_from_file(self):
        with open(self.filename, 'r') as program:
            line_nr = 0
            is_transition = False
            for line in program:
                if line_nr == 1:
                    for state in re.split('[ ,Q=\n]', line):
                        if state != '':
                            self.states.append(state)
                if line_nr == 2:
                    for letter in re.split('[, E=\n]', line):
                        if letter != '':
                            self.alphabet.append(letter)
                if line == "start\n":
                    is_transition = True
                    continue
                if line == "end\n":
                    is_transition = False
                    continue
                if is_transition:
                    is_last = False
                    is_first = True
                    first = ""
                    last = ""
                    letters = []
                    for word in re.split('[, \[\]\n]', line):
                        if word == '':
                            continue
                        if is_first:
                            first = word
                            is_first = False
                        if is_last:
                            last = word

                        if word == "->":
                            is_last = True
                        if word != '' and word != first and word != last and word != '->':
                            letters.append(word)
                    for letter in letters:
                        self.transitions[(first, letter)] = last
                    continue
                if re.split("[= ]", line)[0] == "q0":
                    self.initial_state = re.split("[= ]", line)[3]
                    continue
                if re.split("[= ,]", line)[0] == "F":
                    for word in re.split("[= ,]", line):
                        if word == "F":
                            continue
                        if word != '':
                            self.final_states.append(word)
                    continue
                line_nr += 1

    def print_fa(self):
        print("M = {Q, E, RO, q0, F}\n")
        print(f"Q = {self.states}\n")
        print(f"E = {self.alphabet}\n")
        print(f"RO = {self.transitions}\n")
        print(f"q0 = {self.initial_state}\n")
        print(f"F = {self.final_states}\n")

    def start_menu(self):
        option = -1

        while option != 0:
            self.print_menu()
            option = int(input())
            if option == 1:
                print(f"Q = {self.states}\n")
            if option == 2:
                print(f"E = {self.alphabet}\n")
            if option == 3:
                print(f"RO = {self.transitions}\n")
            if option == 4:
                print(f"q0 = {self.initial_state}\n")
            if option == 5:
                print(f"F = {self.final_states}\n")


    def check_word_if_integer_constant(self, word):
        state = 'q0'
        for letter in word:
            state = self.transitions.get((state, letter))
            if state is None:
                return

        if state not in ['q5', 'q6']:
            return False
        return True
    def check_word_if_string_constant(self, word):
        state = 'q1'
        for letter in word:
            state = self.transitions.get((state, letter))
            if state is None:
                return

        if state not in ['q3']:
            return False
        return True

    def check_word_if_identifier(self, word):
        state = 'q0'
        for letter in word:
            state = self.transitions.get((state, letter))
            if state is None:
                return

        if state not in ['q2']:
            return False
        return True