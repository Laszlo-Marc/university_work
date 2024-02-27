import sys
from random import randint

from domain.graph import VertexError


def generate_random_graph(graph, directed_graph, number_of_vertices, number_of_edges):
    if number_of_edges > number_of_vertices * (number_of_vertices-1):
        raise VertexError("Invalid input!")
    graph._edges = 0
    directed_graph.initialize_graph(number_of_vertices)
    while number_of_edges > 0:
        try:
            first_vertex = randint(0, len(graph.vertices) - 1)
            second_vertex = randint(0, len(graph.vertices) -1)
            cost = randint(0, 1000)
            graph.add_edge(first_vertex, second_vertex, cost)
            number_of_edges = number_of_edges - 1
        except:
            continue


