from grammar import Grammar

grammar = Grammar()
grammar.read_from_file('g1.txt')

# Print basic grammar info
grammar.print_non_terminals()
grammar.print_terminals()
grammar.print_productions()

# LR(0) Functions
states, transitions = grammar.canonical_collection()
print("Canonical Collection of LR(0) Items:")
for i, state in enumerate(states):
    print(f"State {i}: {state}")
print("\nTransitions:")
for (state, symbol), target_state in transitions.items():
    print(f"{state} --{symbol}--> {target_state}")
