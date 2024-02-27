from math import inf

def bellman_ford(graph, source, destination):
    """
    Applies the Bellman-Ford algorithm to find the lowest cost walk between a source and destination vertex in a graph.

    Args:
        graph: An undirected graph represented by an instance of the Graph class.
        source: The source vertex index.
        destination: The destination vertex index.

    Returns:
        None

    Prints:
        - If a path exists, it prints the lowest cost walk from source to destination.
        - If no path exists, it prints a message indicating there is no path between the specified vertices.
        - If a negative cost cycle is detected, it prints a message indicating the presence of such a cycle.

    Raises:
        - VertexError: If the source or destination vertex is invalid.
        - EdgeError: If the edge cost is not defined for an existing edge.
    """

    # Get the number of vertices in the graph
    n = graph.count_vertices()

    # Create a matrix 'd' to store the lowest cost walks from the source vertex 's' to vertex 'x' of length 'k'.
    # Initialize all values to infinity except for d[source][0] which is set to 0.
    d = [[float('inf')] * (n + 1) for _ in range(n)]
    d[source][0] = 0


    for k in range(1, n + 1):
        # For each vertex 'x' in the graph
        for x in graph.vertices_iterator():
            # Initialize d[x][k] with the previous value d[x][k-1]
            d[x][k] = d[x][k-1]

            # For each neighbour 'y' of 'x'
            for y in graph.neighbours_iterator(x):
                # Get the cost of the edge between 'x' and 'y'
                edge_cost = graph.get_edge_cost(x, y)

                # Update d[x][k] with the minimum value between d[x][k] and d[y][k-1] + edge_cost(x, y)
                d[x][k] = min(d[x][k], d[y][k-1] + edge_cost)

    # Check for negative cost cycles
    for x in graph.vertices_iterator():
        # If d[x][n] != d[x][n-1], a negative cost cycle is detected
        if d[x][n] != d[x][n-1]:
            print("Negative cost cycle detected.")
            return

    # Check if a path exists between the source and destination vertices
    if d[destination][n] == float('inf'):
        # If d[destination][n] == infinity, there is no path between the specified vertices
        print("There is no path between the specified vertices.")
    else:
        # Print the lowest cost walk from source to destination
        print(f"The lowest cost walk from {source} to {destination} has cost {d[destination][n]}.")
