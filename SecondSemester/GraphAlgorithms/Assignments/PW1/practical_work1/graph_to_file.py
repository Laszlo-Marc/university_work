


def write_graph_to_file(file_path, g):
        file = open(file_path, "w")
        file.write("{0} {1}\n".format(g.count_vertices(), g.count_edges()))
        for node in g.vertices_iterator():
            for neighbour in g.neighbours_iterator(node):
                file.write("{0} {1} {2}\n".format(node, neighbour, g.get_edge_cost(node, neighbour)))
        file.close()
