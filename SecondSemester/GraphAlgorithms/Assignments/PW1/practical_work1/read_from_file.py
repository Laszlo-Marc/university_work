
from domain.graph import Graph


def read_graph_from_file(file_path,g):
        file = open(file_path, "r")
        n, m = map(int, file.readline().split())
        g = Graph(n)
        for _ in range(m):
            vertex1, vertex2, edge_cost = map(int, file.readline().split())
            g.add_edge(vertex1, vertex2, edge_cost)
        file.close()
        return g



