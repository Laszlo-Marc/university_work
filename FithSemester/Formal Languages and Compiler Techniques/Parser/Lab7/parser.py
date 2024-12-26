from grammar import Grammar


class ParserOutput:
    def __init__(self):
        self.grammar = Grammar()
        self.grammar.read_from_file("g1.txt")
        self.states_table = {}
        self.transitions_table = {}
        self.action_table = {}
        self.goto_table = {}
        self.parsing_tree = []  # To store the tree structure

    def generate_from_grammar(self):
        # Generate the Canonical Collection
        states, transitions = self.grammar.canonical_collection()

        # Populate States Table
        self.states_table = {i: set(state) for i, state in enumerate(states)}

        # Populate Transitions Table
        self.transitions_table = {}
        for (state, symbol), target in transitions.items():
            self.transitions_table[(state, symbol)] = target

        # Populate Action and Goto Tables
        for i, state in enumerate(states):
            self.action_table[i] = {}
            self.goto_table[i] = {}

            for item in state:
                head, body, dot = item
                if dot < len(body):  # Shift case
                    symbol = body[dot]
                    if symbol in self.grammar.terminals:
                        if symbol not in self.action_table[i]:
                            self.action_table[i][symbol] = []
                        self.action_table[i][symbol].append(f"s{transitions.get((i, symbol), 'error')}")
                    elif symbol in self.grammar.non_terminals:
                        self.goto_table[i][symbol] = transitions.get((i, symbol), 'error')
                else:  # Reduce or Accept
                    if head == self.grammar.entry_point + "'":
                        self.action_table[i]['$'] = "accept"
                    else:
                        prod_index = self.grammar.productions[head].index(list(body))
                        if '$' not in self.action_table[i]:
                            self.action_table[i]['$'] = []
                        self.action_table[i]['$'].append(f"r{prod_index + 1}")

        # Resolve conflicts in action table
        self.detect_conflicts()

    def detect_conflicts(self):
        # Check for conflicts in the action table
        for state, actions in self.action_table.items():
            for symbol, entries in actions.items():
                if isinstance(entries, list) and len(entries) > 1:
                    print(f"Conflict detected in State {state}, Symbol '{symbol}': {entries}")
                    # Resolve by keeping the first entry as an example (you can implement specific resolution logic)
                    self.action_table[state][symbol] = entries[0]

    def build_parsing_tree(self, parse_sequence):
        """
        Builds the parsing tree using father-sibling relations.
        :param parse_sequence: Sequence of production rules used during parsing (e.g., [r2, r1, r3]).
        :param grammar: Grammar object containing the rules.
        """
        tree = []
        node_id = 0  # Assign a unique ID to each node
        stack = []  # To keep track of nodes during construction

        for rule in parse_sequence:
            if rule.startswith("r"):
                rule_index = int(rule[1:]) - 1
                for head, productions in self.grammar.productions.items():
                    if rule_index < len(productions):
                        production = productions[rule_index]
                        new_node = {"id": node_id, "father": "", "sibling": "", "label": head}
                        tree.append(new_node)
                        node_id += 1

                        # Add children (symbols from the production)
                        previous_child = ""
                        for symbol in production:
                            child_node = {
                                "id": node_id,
                                "father": new_node["id"],
                                "sibling": "",
                                "label": symbol,
                            }
                            if previous_child:
                                child_node["sibling"] = previous_child["id"]
                            previous_child = child_node
                            tree.append(child_node)
                            node_id += 1

                        break

        self.parsing_tree = tree

    def print_parsing_tree(self):
        """
        Prints the parsing tree using father and sibling relations.
        """
        print("\nParsing Tree:")
        print(f"{'Node ID':<10}{'Label':<10}{'Father':<10}{'Sibling':<10}")
        for node in self.parsing_tree:
            print(f"{node['id']:<10}{node['label']:<10}{node['father']:<10}{node['sibling']:<10}")

    def save_parsing_tree_to_file(self, filename="parsing_tree.txt"):
        """
        Saves the parsing tree to a file.
        """
        with open(filename, "w") as file:
            file.write(f"{'Node ID':<10}{'Label':<10}{'Father':<10}{'Sibling':<10}\n")
            for node in self.parsing_tree:
                file.write(f"{node['id']:<10}{node['label']:<10}{node['father']:<10}{node['sibling']:<10}\n")

    def print_to_screen(self):
        # Print States Table
        print("\nStates Table:")
        for state, items in self.states_table.items():
            print(f"State {state}: {items}")

        # Print Transitions Table
        print("\nTransitions Table:")
        for (state, symbol), target in self.transitions_table.items():
            print(f"State {state} --{symbol}--> State {target}")

        # Print Action Table
        print("\nAction Table:")
        for state, actions in self.action_table.items():
            print(f"State {state}: {actions}")

        # Print Goto Table
        print("\nGoto Table:")
        for state, gotos in self.goto_table.items():
            print(f"State {state}: {gotos}")

    def save_to_file(self, filename="parser_output.txt"):
        with open(filename, "w") as file:
            # Write States Table
            file.write("States Table:\n")
            for state, items in self.states_table.items():
                file.write(f"State {state}: {items}\n")

            # Write Transitions Table
            file.write("\nTransitions Table:\n")
            for (state, symbol), target in self.transitions_table.items():
                file.write(f"State {state} --{symbol}--> State {target}\n")

            # Write Action Table
            file.write("\nAction Table:\n")
            for state, actions in self.action_table.items():
                file.write(f"State {state}: {actions}\n")

            # Write Goto Table
            file.write("\nGoto Table:\n")
            for state, gotos in self.goto_table.items():
                file.write(f"State {state}: {gotos}\n")
