from grammar import Grammar
from parser import ParserOutput

grammar = Grammar()
grammar.read_from_file("g1.txt")  # Adjust to your file

# Create and populate the ParserOutput
parser_output = ParserOutput()
parser_output.generate_from_grammar()

# Build Parsing Tree (Provide the parse sequence as an example)
parse_sequence = ["r2", "r3", "r1"]  # Replace with actual sequence
parser_output.build_parsing_tree(parse_sequence)

# Print Parsing Tree
parser_output.print_parsing_tree()
parser_output.save_parsing_tree_to_file()

# Print other outputs
parser_output.print_to_screen()
parser_output.save_to_file()
