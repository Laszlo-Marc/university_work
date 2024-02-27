from copy import deepcopy
from random import randrange

from validation.validation import VertexError, EdgeError


class DirectedGraph:
    def __init__(self, n=0, m=0):
        self._vertices = set()
        self._neighbours = dict()
        self._transpose = dict()
        self._cost = dict()
        for i in range(n):
            self.add_vertex(i)
        for j in range(m):
            vertex1 = randrange(n)
            vertex2 = randrange(n)
            while vertex1 == vertex2:
                vertex1 = randrange(n)
                vertex2 = randrange(n)
            self.add_edge(vertex1, vertex2, randrange(100))

    def vertices_iterator(self):
        for vertex in self._vertices:
            yield vertex

    def neighbours_iterator(self, vertex):
        if not self.is_vertex(vertex):
            raise VertexError("Invalid vertex.")
        for neighbour in self._neighbours[vertex]:
            yield neighbour

    def transpose_iterator(self, vertex):
        if not self.is_vertex(vertex):
            raise VertexError("Invalid vertex.")
        for neighbour in self._transpose[vertex]:
            yield neighbour

    def edges_iterator(self):
        for key, value in self._cost.items():
            yield key[0], key[1], value

    def is_vertex(self, vertex):
        return vertex in self._vertices

    def is_edge(self, vertex1, vertex2):
        return vertex1 in self._neighbours and vertex2 in self._neighbours[vertex1]

    def count_vertices(self):
        return len(self._vertices)

    def count_edges(self):
        return len(self._cost)

    def in_degree(self, vertex):
        if vertex not in self._transpose:
            raise VertexError("The specified vertex does not exist.")
        return len(self._transpose[vertex])

    def out_degree(self, vertex):
        if vertex not in self._neighbours:
            raise VertexError("The specified vertex does not exist.")
        return len(self._neighbours[vertex])

    def get_edge_cost(self, vertex1, vertex2):
        if (vertex1, vertex2) not in self._cost:
            raise EdgeError("The specified edge does not exist.")
        return self._cost[(vertex1, vertex2)]

    def set_edge_cost(self, vertex1, vertex2, new_cost):
        if (vertex1, vertex2) not in self._cost:
            raise EdgeError("The specified edge does not exist.")
        self._cost[(vertex1, vertex2)] = new_cost

    def add_vertex(self, vertex):
        if self.is_vertex(vertex):
            raise VertexError("Cannot add a vertex which already exists.")
        self._vertices.add(vertex)
        self._neighbours[vertex] = set()
        self._transpose[vertex] = set()

    def add_edge(self, vertex1, vertex2, edge_cost=0):
        if not self.is_vertex(vertex1) or not self.is_vertex(vertex2):
            raise EdgeError("The vertices on the edge do not exist.")
        self._neighbours[vertex1].add(vertex2)
        self._transpose[vertex2].add(vertex1)
        self._cost[(vertex1, vertex2)] = edge_cost

    def remove_edge(self, vertex1, vertex2):
        if not self.is_edge(vertex1, vertex2):
            raise EdgeError("The specified edge does not exist.")
        del self._cost[(vertex1, vertex2)]
        self._neighbours[vertex1].remove(vertex2)
        self._transpose[vertex2].remove(vertex1)

    def remove_vertex(self, vertex):
        if not self.is_vertex(vertex):
            raise VertexError("Cannot remove a vertex which doesn't exist.")
        to_remove = []
        for node in self._neighbours[vertex]:
            to_remove.append(node)
        for node in to_remove:
            self.remove_edge(vertex, node)
        to_remove = []
        for node in self._transpose[vertex]:
            to_remove.append(node)
        for node in to_remove:
            self.remove_edge(node, vertex)
        del self._neighbours[vertex]
        del self._transpose[vertex]
        self._vertices.remove(vertex)

    def copy(self):
        return deepcopy(self)
