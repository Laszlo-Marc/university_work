from domain.graph import VertexError,EdgeError,Graph
from graph_generator import generate_random_graph
from graph_to_file import write_graph_to_file
from read_from_file import read_graph_from_file
from practical_work2 import connected_components

class Console:
    def __init__(self, graph, validation):
        self._graph = graph
        self._validation = validation

    def display_menu(self):
        print("0.Display menu")
        print("1.Get the number of vertices")
        print("2.Get the vertices")
        print("3.Check if there is an edge from a vertex to another")
        print("4.Get the in degree of a vertex")
        print("5.Get the out degree of a vertex")
        print("6.Get the set of outbound edges of a vertex")
        print("7.Get the set of inbound edges of a vertex")
        print("8.Add an edge")
        print("9.Remove an edge")
        print("10.Change the cost of an edge")
        print("11.Add a vertex")
        print("12.Remove a vertex")
        print("13.Read the graph from a file")
        print("14.Make a copy of the graph")
        print("15.Generate a random graph")
        print("16.Get the cost of an edge")
        print("17.Write the graph into a file")
        print("Use function from practical work 2")

    def display_num_of_vertices(self):
        print("Vertices count: ", len(self._graph._vertices))

    def display_the_vertices(self):
        if len(self._graph._vertices) == 0:
            print("There is no graph")
        else:
            print("The vertices are: ")
            vertices = self._graph.parse_vertices()
            for vertex in vertices:
                print(vertex)

    def display_inbound_vertices(self):
        vertex = int(input("The vertex: "))
        if len(self._service.inbounds) == 0:
            print("There is np graph!")
        elif self._graph.check_vertex_existence(vertex):
            vertices = self._service.parse_inbound_vertices(vertex)
            for vertex in vertices:
                print(vertex)
        else:
            print("The vertex does not exist!")

    def change_cost_edge(self):
        if len(self._graph.vertices) == 0:
            print("There is no graph")
        else:
            start_vertex = int(input("The starting vertex: "))
            end_vertex = int(input("The end vertex: "))
            if start_vertex == end_vertex:
                raise VertexError("Invalid input!")
            self._validation.vertex_existence(start_vertex, end_vertex)
            if self._service.check_edge_existence(start_vertex,end_vertex) is False:
                print("There is no edge from", start_vertex, "to", end_vertex)
            else:
                cost = int(input("New cost: "))
                self._service.change_edge_cost(start_vertex, end_vertex,cost)
                print("Cost changed successfully!")

    def display_outbound_vertices(self):
        vertex = int(input("Type in the vertex: "))
        if len(self._service.outbounds) == 0:
            print("There doesn't exist a graph!")
        elif self._graph.check_vertex_existence(vertex):
            vertices = self._service.parse_outbound_vertices(vertex)
            for vertex in vertices:
                print(vertex)
        else:
            print("The given vertex doesn't exist!")

    def get_in_degree(self):
        vertex = int(input("Type in the vertex: "))
        if self._graph.check_vertex_existence(vertex) is True:
            print(self._service.get_in_degree(vertex))
        else:
            print("The given vertex doesn't exist!")

    def get_out_degree(self):
        vertex = int(input("Type in the vertex: "))
        if self._graph.check_vertex_existence(vertex) is True:
            print(self._service.get_out_degree(vertex))
        else:
            print("The given vertex doesn't exist!")

    def edge_between_vertices(self):
        if len(self._graph.vertices) == 0:
            print("There is no graph!")
        else:
            first_vertex = int(input("First vertex: "))
            second_vertex = int(input("Second vertex: "))
            if first_vertex == second_vertex:
                raise VertexError("Invalid input!")
            self._validation.vertex_existence(first_vertex, second_vertex)
            if self._service.check_edge_existence(first_vertex, second_vertex):
                print("There is an edge from", first_vertex, "to", second_vertex)
            else:
                print("There is no edge from", first_vertex, "to", second_vertex)

    def add_vertex(self):
        print("Type in the vertex you would you like to add: ")
        new_vertex = int(input())
        self._service.add_vertex(new_vertex)
        print("Vertex added successfully!")

    def remove_vertex(self):
        print("Type in the vertex you would like to remove: ")
        vertex = int(input())
        self._service.remove_vertex(vertex)
        print("Vertex deleted successfully!")

    def add_an_edge(self):
        print("First vertex: ")
        first_vertex = int(input())
        print("Second vertex: ")
        second_vertex = int(input())
        if first_vertex == second_vertex:
            raise VertexError("Invalid input!")
        print("Edge cost: ")
        cost = int(input())
        self._service.add_edge(first_vertex, second_vertex, cost)
        print("Edge added successfully!")

    def delete_an_edge(self):
        print("First vertex: ")
        first_vertex = int(input())
        print("Second vertex: ")
        second_vertex = int(input())
        if first_vertex == second_vertex:
            raise VertexError("Invalid input!")
        self._service.delete_edge(first_vertex, second_vertex)
        print("Edge deleted successfully!")

    def copy_graph(self):
        self._service.copy_graph()
        print("Graph copied successfully!")

    def read_graph(self):
        file_name = input("File name: ")
        read_graph_from_file(file_name, self._graph)
        print("The command executed with success!")

    def display_graph_to_file(self):
        file_name = input("File name: ")
        write_graph_to_file(file_name, self._graph)
        print("The command executed with success!")

    def generate_a_random_graph(self):
        number_of_vertices = int(input("Vertices count: "))
        number_of_edges = int(input("Edges count: "))
        generate_random_graph(self._graph, self._service, number_of_vertices, number_of_edges)
        print("Graph generated successfully!")

    def get_cost(self):
        first_vertex = int(input("First vertex: "))
        second_vertex = int(input("Second vertex: "))
        if self._graph.check_vertex_existence(first_vertex) and self._graph.check_vertex_existence(second_vertex):
            if self._service.check_edge_existence(first_vertex, second_vertex):
                cost = self._service.get_edge_cost(first_vertex, second_vertex)
                print(cost)
            else:
                print("There is no edge between these two vertices!")
        else:
            print("The given vertices doesn't exist!")

    def practical_work2(self):
        vertices = int(input("Vertices: "))
        edges = int(input("Edges: "))
        self._graph = Graph(vertices,edges)
        connected = connected_components(self._graph)
        print("Connected components: ",connected)

    def start(self):
        done = False
        commands = {'0': self.display_menu, '1': self.display_num_of_vertices, '2': self.display_the_vertices,
                    '3': self.edge_between_vertices, '4': self.get_in_degree, '5': self.get_out_degree,
                    '6': self.display_outbound_vertices, '7': self.display_inbound_vertices,
                    '8': self.add_an_edge, '9': self.delete_an_edge , '10': self.change_cost_edge ,
                    '11': self.add_vertex, '12': self.remove_vertex, '13': self.read_graph, '14': self.copy_graph ,
                    '15':  self.generate_a_random_graph, '16': self.get_cost, '17': self.display_graph_to_file,'18':self.practical_work2}

        while not done:
            command = input('\nYour wish is my command: \n')
            if command in commands:
                try:
                    commands[command]()
                except ValueError as ve:
                    print(ve)
                except VertexError as ge:
                    print(ge)
            elif command == '0':
                self.display_menu()
            elif command == 'E':
                print("^-^")
                done = True
            else:
                print("Invalid command!")