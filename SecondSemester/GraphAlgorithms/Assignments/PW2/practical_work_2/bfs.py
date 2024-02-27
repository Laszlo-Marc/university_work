
from queue import Queue
from graph.graph import read_file, write_file
from graph.directed_graph import DirectedGraph
from graph.graph import Graph


def connected_components(graph):
    # Initialize an empty set to keep track of visited vertices
    met = set()
    # Initialize an empty list to store the connected components of the graph
    ans = []
    # For each vertex in the graph
    for vertex in graph.vertices_iterator():
        # If the vertex has not been visited yet
        if vertex not in met:
            # Initialize a queue and add the vertex to it
            q = Queue()
            q.put(vertex)
            # Mark the vertex as visited
            met.add(vertex)
            # Create a new connected component containing the vertex
            ans.append([vertex])
            # While the queue is not empty
            while not q.empty():
                # Dequeue a vertex from the queue
                node = q.get()
                # For each neighbour of the dequeued vertex
                for neighbour in graph.neighbours_iterator(node):
                    # If the neighbour has not been visited yet
                    if neighbour not in met:
                        # Mark the neighbour as visited
                        met.add(neighbour)
                        # Add the neighbour to the queue
                        q.put(neighbour)
                        # Add the neighbour to the last connected component in the list
                        ans[-1].append(neighbour)
    # Return the list of connected components
    return ans

class Console:
    def __init__(self, g, dg):
        self._g = g
        self._dg = dg

    def menu(self):
        print("1.Apply the function on a undirected graph")
        print("2.Apply the function on a directed graph")
        print("3.Get graph from a file")
        print("4.Paste graph to file")
        print("5.Display current graph")
        print("6.Generate an undirected graph")
        print("7.Generate a directed graph")

    def print_current_graph(self,g,c):
        if c == 1:
            for triple in g.edges_iterator():
                print(triple[0], triple[1], triple[2])
        if c == 2:
            for triple in g.edges_iterator():
                print(triple[0], triple[1], triple[2])

    def start(self):
        running = True
        while running:
            self.menu()
            command = int(input("Command: "))
            if command == 1:
                for triple in self._g.edges_iterator():
                    print(triple[0], triple[1], triple[2])
                print(connected_components(self._g), end="\n\n")
            elif command == 3:
                file_name = input("File name: ")
                self._g = read_file(file_name)
            elif command == 4:
                file_name = input("File name: ")
                write_file(file_name,self._g)
            elif command == 5:
                which_graph = int(input("Print the undirected(1) or directed(2) graph in use: "))
                if which_graph == 1:
                    self.print_current_graph(self._g,1)
                elif which_graph == 2:
                    self.print_current_graph(self._dg,2)
            elif command == 6:
                vertices = int(input("Vertices: "))
                edges = int(input("Edges: "))
                self._g = Graph(vertices,edges)
            elif command == 7:
                vertices = int(input("Vertices: "))
                edges = int(input("Edges: "))
                self._dg = DirectedGraph(vertices, edges)
            elif command == 0:
                running = False
                break

g = Graph(0,0)
dg = DirectedGraph(0, 0)
console = Console(g, dg)
console.start()