from floyd_warshall import bellman_ford
from graph.directed_graph import DirectedGraph
from graph.graph import Graph

def read_file(file_path):
    file = open(file_path, "r")
    n, m = map(int, file.readline().split())
    g = Graph(n)
    for _ in range(m):
        vertex1, vertex2, edge_cost = map(int, file.readline().split())
        g.add_edge(vertex1, vertex2, edge_cost)
    file.close()
    return g

def write_file(file_path, g):
    file = open(file_path, "w")
    file.write("{0} {1}\n".format(g.count_vertices(), g.count_edges()))
    for node in g.vertices_iterator():
        for neighbour in g.neighbours_iterator(node):
            file.write("{0} {1} {2}\n".format(node, neighbour, g.get_edge_cost(node, neighbour)))
    file.close()

class Console:
    def __init__(self,graph):
        self._graph = graph

    def menu(self):
        print("1.Read graph from file")
        print("2.Generate graph")
        print("3.Apply Bellman Ford")
        print("4.Write to file")
        print("5.Print graph in use")

    def run(self):
        while True:
            self.menu()
            command = int(input("Command: "))
            if command == 1:
                file_name = input("File: ")
                self._graph = read_file(file_name)
            if command == 2:
                vertices = int(input("Vertices: "))
                edges = int(input("Edges: "))
                self._graph = Graph(vertices,edges)
                for triple in self._graph.edges_iterator():
                        print(triple[0], triple[1], triple[2])
            if command == 3:
                    source = int(input("Source: "))
                    dest = int(input("Destination: "))
                    bellman_ford(self._graph,source,dest)

            if command == 4:
                file_name = input("File: ")
                write_file(file_name,self._graph)
            if command == 5:
                for triple in self._graph.edges_iterator():
                    print(triple[0], triple[1], triple[2])
            if command == 0:
                return False
                break


graph = Graph(0,0)
console  = Console(graph)
console.run()