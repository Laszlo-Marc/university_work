from domain.graph import VertexError


class Validation:

    def __init__(self, graph):
        self._graph = graph


    def vertex_existence(self, first_vertex, second_vertex):
        if self._graph.find_vertex(first_vertex) is False:
            raise VertexError("The first vertex doesn't exist!")
        if self._graph.find_vertex(second_vertex) is False:
            raise VertexError("The second vertex doesn't exist!")

