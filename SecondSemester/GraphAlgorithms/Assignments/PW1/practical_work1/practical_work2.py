from queue import Queue

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