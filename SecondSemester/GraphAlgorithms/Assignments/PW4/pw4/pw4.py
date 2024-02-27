from operator import itemgetter
def find(parent, vertex):
    """
    Find the root (representative) of the set to which the given vertex belongs.

    Args:
        parent: A dictionary representing the parent relationship of vertices.
        vertex: The vertex for which the root is to be found.

    Returns:
        The root (representative) of the set to which the vertex belongs.
    """

    if parent[vertex] == vertex:
        return vertex
    return find(parent, parent[vertex])


def union(parent, rank, vertex1, vertex2):
    """
    Merge two sets represented by the given vertices, ensuring balanced union by rank.

    Args:
        parent: A dictionary representing the parent relationship of vertices.
        rank: A dictionary representing the rank (height) of the trees rooted at vertices.
        vertex1: The first vertex.
        vertex2: The second vertex.

    Returns:
        None

    Modifies:
        The parent and rank dictionaries to merge the sets.
    """

    root1 = find(parent, vertex1)
    root2 = find(parent, vertex2)

    if rank[root1] < rank[root2]:
        parent[root1] = root2
    elif rank[root1] > rank[root2]:
        parent[root2] = root1
    else:
        parent[root2] = root1
        rank[root1] += 1


def kruskal_mst(graph):
    """
    Applies Kruskal's algorithm to find the minimum spanning tree of a graph.

    Args:
        graph: An undirected connected graph represented by an instance of the Graph class.

    Returns:
        A list of edges forming the minimum spanning tree.

    Algorithm Steps:
        1. Initialize an empty minimum spanning tree (MST).
        2. Initialize a parent dictionary to track the parent relationship of each vertex.
        3. Initialize a rank dictionary to track the rank (height) of the trees rooted at vertices.
        4. Sort the edges of the graph in non-decreasing order of their weights.
        5. Iterate through each edge in the sorted order:
           - Find the roots of the sets to which the endpoints of the edge belong.
           - If the roots are different, add the edge to the MST and merge the sets.
        6. Return the MST.

    """

    num_vertices = graph.count_vertices()
    parent = {}
    rank = {}
    mst = []

    # Initialize parent and rank dictionaries
    for vertex in graph.vertices_iterator():
        parent[vertex] = vertex
        rank[vertex] = 0

    # Sort the edges in non-decreasing order of their weights
    edges = list(graph.edges_iterator())
    edges.sort(key=itemgetter(2))

    # Iterate through the sorted edges and build the MST
    for edge in edges:
        vertex1, vertex2, cost = edge

        root1 = find(parent, vertex1)
        root2 = find(parent, vertex2)

        # Check if adding the edge creates a cycle
        if root1 != root2:
            # Add the edge to the MST and merge the sets
            mst.append((vertex1, vertex2, cost))
            union(parent, rank, root1, root2)

    return mst
