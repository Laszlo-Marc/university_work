from grammar import Grammar

grammar = Grammar()
grammar.read_from_file('g2.txt')
grammar.print_non_terminals()
grammar.print_terminals()
grammar.print_productions()
grammar.print_productions_for('stmt')
print("Is CFG?", grammar.is_cfg())