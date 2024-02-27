import graph
import wgc
import heapq

def bfs(g, s, t=None):
    '''Performs a Breadth-First Search in graph g starting from vertex s.
    The search will stop if vertex t is reached. If t is None, the processing
    won't stop until all accessible vertices are processed.
    Returns a tuple where:
      - the first element is a dictionary where the key are the accessible vertices and,
        for each vertex, the value is the parent in the BFS tree. For s, the value
        will be None
      - the second is a dictionary where the keys are the accessible vertices and
        for each vertex, the value is the list of children
      - the third is a dictionary where the keys are the accessible vertices and
        for each vertex, the value is the distance (as int) from s to that vertex.
    '''
    parent = {s:None}
    children = {s : []}
    dist = {s : 0}
    queue=[s]
    while len(queue)!=0:
        current_vertex=queue.pop(0)
        if current_vertex == t:
            break
        for next in g.parseNOut(current_vertex):
            if next not in parent.keys():
                parent[next]=current_vertex
                children[next] = []
                children[current_vertex].append(next)
                dist[next] = dist[current_vertex] + 1
                queue.append(next)
        #print(current_vertex, parent, children, dist)
    return (parent, children, dist)

def extract_path(parent, s, t):
    if t not in parent:
        return None
    path = []
    current_vertex = t
    while current_vertex != s:
        path.append(current_vertex)
        current_vertex = parent[current_vertex]
    path.append(s)
    path.reverse()
    return path

def shortest_path(g, s, t):
    '''Computes the shortest (min. length) walk from vertex s to vertex t
    in the graph g. Returns the walk as a list of vertices (starting with s
    and ending with t). Returns None if no walk exists.
    '''
    parent, children, dist = bfs(g, s, t)
    #print(parent, children, dist)
    return extract_path(parent, s, t)

def min_cost_path_dijkstra(g, s, t):
    '''Computes the min cost walk from vertex s to vertex t
    in the graph g (with costs). Precond: all costs are non-negative.
    Returns the walk as a list of vertices (starting with s
    and ending with t). Returns None if no walk exists.
    '''
    q = []
    dist = {}
    dist[s] = 0
    prev = {}
    prev[s] = None
    heapq.heappush(q, (0, s))
    while len(q) != 0:
        cost, x = heapq.heappop(q)
        if x == t:
            break
        if cost > dist[x]:
            print(f"Skipping {x}")
            continue
        for y in g.parseNOut(x):
            if y not in dist or dist[x] + g.cost(x, y) < dist[y]:
                dist[y] = dist[x] + g.cost(x,y)
                heapq.heappush(q, (dist[y], y))
                prev[y] = x
                
        print(x, dist, prev, q)
    return extract_path(prev, s, t)

def min_cost_walk_dp(g, s, t):
    d = []
    d.append({x : float('inf') for x in g.parseX()})
    d[0][s] = 0
    dist = {x : float('inf') for x in g.parseX()}
    dist[s] = 0
    prev = {s:None}
    for k in range(1, 2*len(g.parseX())):
        curr_dist = d[-1]
        next_dist = {}
        for x in g.parseX():
            next_dist[x] = float('inf')
            for y in g.parseNIn(x):
                if next_dist[x] > curr_dist[y] + g.cost(y,x):
                    next_dist[x] = curr_dist[y] + g.cost(y,x)
                    if next_dist[x] < dist[x]:
                        dist[x] = next_dist[x]
                        prev[x] = y
        d.append(next_dist)
    print(d)
    return extract_path(prev, s, t)

def min_cost_walk_dp1(g, s, t):
    d = [{s:0}]
    dist = {s:0}
    prev = {s:None}
    for k in range(1, 2*len(g.parseX())):
        curr_dist = d[-1]
        next_dist = {}
        for y in curr_dist.keys():
            for x in g.parseNOut(y):
                if x not in next_dist.keys() or next_dist[x] > curr_dist[y] + g.cost(y,x):
                    next_dist[x] = curr_dist[y] + g.cost(y,x)
                    if x not in dist.keys() or next_dist[x] < dist[x]:
                        dist[x] = next_dist[x]
                        prev[x] = y
        d.append(next_dist)
    print(d)
    return extract_path(prev, s, t)

def toposortDepthFirstSearch(g, x, visited, toposortlist, stack, stack_list, ok):
    visited[x] = True
    stack[x] = True
    stack_list.append(x)
    for neighbour in g.parseNOut(x):
        if neighbour in stack:
            i = stack_list.index(neighbour)
            cycle = stack_list[i : ]
            cycle.append(neighbour)
            ok.append(cycle)
        if not neighbour in visited:
            toposortDepthFirstSearch(g, neighbour, visited, toposortlist, stack, stack_list, ok)
    toposortlist.append(x)
    del stack[x]
    stack_list.pop()

def toposort(g):
    '''Returns the list of vertices in g in a topologically sorted order.
    Returns None if g contains a cycle.
    '''
    toposortlist = []
    visited = {}
    ok = []
    stack = {}
    for node in g.parseX():
        if not node in visited:
            toposortDepthFirstSearch(g, node, visited, toposortlist, stack, [], ok)
        if len(ok):
            print("Cycle:", ok[0])
            return None
    toposortlist.reverse()
    return toposortlist
    

def min_cost_walk_dag(g, s, t):
    '''Computes the min cost walk from s to t in the graph g. Precond: g is a DAG
    Returns the walk as a list of vertices, or None if no walk exists.
    '''
    sorted_vertices = toposort(g)
    if sorted_vertices is None:
        print("The graph has a cycle")
    else:
        print(sorted_vertices)
        dist = {}
        dist[s] = 0
        prev = {}
        prev[s] = None
        path_count = {s: 1}
        for node in sorted_vertices:
            if node == t:
                break

            if not node in dist:
                continue
                

            for neighbour in g.parseNOut(node):
                new_cost = dist[node] + g.cost(node, neighbour)
                if not neighbour in dist or dist[neighbour] > new_cost:
                    dist[neighbour] = new_cost
                    prev[neighbour] = node
                    path_count[neighbour] = path_count[node]
                elif dist[neighbour] == new_cost:
                    path_count[neighbour] += path_count[node]
    print(path_count)
    return extract_path(prev, s, t)

class DisjointSets:
    def __init__(self, elements):
        '''Creates a set of sets where each element in 'elements' is the sole member of
        its own set
        '''
        self.__parent = {}
        self.__height = {} # height of the tree rooted in the key vertex;
          # no longer maintained for non-roots
        
        for element in elements:
            self.__parent[element] = None
            self.__height[element] = 0
        
    def __root(self, x):
        while self.__parent[x] is not None:
            x = self.__parent[x]
        return x
        
    def join(self, x, y):
        '''If x and y are in the same set, returns False. Otherwise, joins together
        the sets of x and of y and returns True.
        '''
        rx = self.__root(x)
        ry = self.__root(y)
        hx = self.__height[rx]
        hy = self.__height[ry]
        if rx == ry:
            return False
        if hx < hy:
            self.__parent[rx] = ry
        elif hx > hy:
            self.__parent[ry] = rx
        else:
            self.__parent[ry] = rx
            self.__height[rx] += 1
        return True

def kruskal(g):
    '''Constructs the minimum spaning tree for the given graph. Precond: g is connected.
    Returns the list of edges for the tree.
    '''
    edges = []
    for x in g.parseX():
        for y in g.parseN(x):
            if x < y:
                edges.append((x, y, g.cost(x,y)))
    comp = lambda t : t[2]
    edges.sort(key=comp)
    tree = []
    disjoint_sets = DisjointSets(g.parseX())
    for x,y,c in edges:
        if disjoint_sets.join(x, y):
            tree.append((x, y))
    if len(tree) < len(g.parseX()) - 1:
        return None
    return tree

def is_tree(g):
    edges = []
    for x in g.parseX():
        for y in g.parseN(x):
            if x < y:
                edges.append((x,y))
    if len(edges) + 1 != len(g.parseX()):
        return False
    for x in g.parseX():
        s = x
        break
    parent, _, _ = bfs(g, s)
    return len(parent) == len(g.parseX())

def shortest1():
    g = graph.create_small_graph(graph.GraphWithInbound)
    print(shortest_path(g, 1, 4))

def shortest_wgc():
    g = wgc.WolfGoatCabbageGraph()
    s = g.start()
    t = g.dest()
    print(shortest_path(g, s, t))

def shortest_big():
    g = graph.create_random_graph(100000, 200000, graph.GraphWithInbound)
    print(shortest_path1(g, 0, 1))
    walks = bfs1(g, 0)
    print(len(walks))
    max_dist = None
    for v in walks:
        if max_dist is None or max_dist < len(walks[v]):
            max_dist = len(walks[v])
    print(max_dist)

def test_dijkstra():
    g = graph.create_small_graph(graph.GraphWithInbound)
    print(min_cost_path_dijkstra(g, 1, 3))

def test_min_cost_dp():
    g = graph.create_small_graph(graph.GraphWithInbound)
    print(min_cost_walk_dp1(g, 1, 4))

def test_min_cost_dag():
    g = graph.create_small_dag_and_cost(graph.GraphWithInbound)
    print(min_cost_walk_dag(g, 6, 7))

def test_kruskal():
    g = graph.create_small_undirected_disconnected()
    print(kruskal(g))
    
def test_tree():
    g = graph.create_small_tree()
    print(is_tree(g))

if __name__ == "__main__":
    test_tree()
