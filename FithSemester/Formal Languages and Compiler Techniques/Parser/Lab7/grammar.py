class Grammar:
    def __init__(self):
        self.non_terminals = set()  # Non-terminal symbols (N)
        self.terminals = set()      # Terminal symbols (E)
        self.productions = {}       # Productions (P)
        self.entry_point = None     # The starting non-terminal (S)

    def read_from_file(self, file_path):
        try:
            with open(file_path, 'r', encoding='utf-8') as file:
                lines = file.read().strip().splitlines()

            is_productions_section = False

            for line in lines:
                line = line.strip()

                if line.startswith("N ="):  # Non-terminals
                    self.non_terminals = set(line.split('=')[1].strip().split())

                elif line.startswith("E ="):  # Terminals
                    self.terminals = set(line.split('=', maxsplit=1)[1].strip().split())

                elif line.startswith("S ="):  # Start symbol
                    self.entry_point = line.split('=')[1].strip()
                    if self.entry_point not in self.non_terminals:
                        print(f"Warning: Start symbol {self.entry_point} is not in the set of non-terminals.")

                elif line.startswith("P ="):  # Start of productions
                    is_productions_section = True

                elif is_productions_section:
                    if '->' in line:
                        head, bodies = line.split('->')
                        head = head.strip()
                        if head not in self.productions:
                            self.productions[head] = []

                        for body in bodies.split('|'):
                            body_symbols = [symbol.strip() for symbol in body.split()]
                            if body_symbols == ["E"]:
                                body_symbols = [""]
                            self.productions[head].append(body_symbols)

                            # Dynamically add any new terminal symbols
                            for symbol in body_symbols:
                                if (symbol not in self.non_terminals and
                                        symbol not in self.terminals and
                                        not symbol.isupper()):
                                    self.terminals.add(symbol)

            self.validate_grammar()

        except Exception as e:
            print(f"Error reading grammar file: {e}")

    def validate_grammar(self):
        # Ensure all production heads are valid non-terminals
        for head in self.productions.keys():
            if head not in self.non_terminals:
                print(f"Invalid production head: {head} (not a non-terminal).")

        # Ensure all symbols in production bodies are valid
        for head, bodies in self.productions.items():
            for body in bodies:
                for symbol in body:
                    if symbol not in self.non_terminals and symbol not in self.terminals and symbol != "":
                        print(f"Invalid symbol in production {head} -> {' '.join(body)}: {symbol}")

    def print_non_terminals(self):
        print("Non-Terminals:", ", ".join(self.non_terminals))

    def print_terminals(self):
        print("Terminals:", ", ".join(self.terminals))

    def print_productions(self):
        print("Productions:")
        for head, bodies in self.productions.items():
            print(f"{head} -> {' | '.join(' '.join(body) for body in bodies)}")

    def print_productions_for(self, non_terminal):
        if non_terminal not in self.non_terminals:
            print(f"{non_terminal} is not a valid non-terminal.")
            return
        print(f"Productions for {non_terminal}:")
        for body in self.productions.get(non_terminal, []):
            print(f"{non_terminal} -> {' '.join(body)}")

    def is_cfg(self):
        for head in self.productions:
            if head not in self.non_terminals:
                print(f"Invalid CFG: {head} is not a non-terminal.")
                return False
            for body in self.productions[head]:
                for symbol in body:
                    if symbol not in self.non_terminals and symbol not in self.terminals and symbol != "":
                        print(f"Invalid symbol in production {head} -> {' '.join(body)}: {symbol}")
                        return False
        return True

    def closure(self, items):
        closure_set = set(tuple(item) for item in items)
        changed = True

        while changed:
            changed = False
            new_items = set()
            for head, body, dot in closure_set:
                if dot < len(body) and body[dot] in self.non_terminals:
                    next_symbol = body[dot]
                    for production in self.productions[next_symbol]:
                        new_item = (next_symbol, tuple(production), 0)
                        if new_item not in closure_set:
                            new_items.add(new_item)
                            changed = True
            closure_set.update(new_items)

        return closure_set

    def goto(self, items, symbol):
        goto_set = set()
        for head, body, dot in items:
            if dot < len(body) and body[dot] == symbol:
                goto_set.add((head, tuple(body), dot + 1))
        return self.closure(goto_set)

    def canonical_collection(self):
        start_item = (self.entry_point + "'", (self.entry_point,), 0)
        states = [self.closure([start_item])]
        transitions = {}

        while True:
            new_states = []
            for i, state in enumerate(states):
                for symbol in self.terminals.union(self.non_terminals):
                    goto_state = self.goto(state, symbol)
                    if goto_state and goto_state not in states + new_states:
                        new_states.append(goto_state)
                        transitions[(i, symbol)] = len(states) + len(new_states) - 1

            if not new_states:
                break
            states.extend(new_states)

        return states, transitions

