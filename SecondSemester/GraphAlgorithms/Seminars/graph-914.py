import copy
import random
import time

class Graph:
    def __init__(self, n):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges;
        '''
        self.__outbound = {}
        for vertex in range(n):
            self.__outbound[vertex] = []

    def add_edge(self, x, y):
        '''Adds an edge from x to y. Return True on success, False if the edge already exists. Precond: x and y exists
        '''
        if self.isEdge(x, y):
            return False            
        self.__outbound[x].append(y)
        return True
        
    def parseX(self):
        '''Returns something that can be iterated and produces all the vertices of the graph
        '''
        return list(self.__outbound.keys())
    
    def parseNOut(self, x):
        return list(self.__outbound[x])
        
        
    def parseNIn(self, x):
        result = []
        for vertex in self.__outbound:
            if x in self.__outbound[vertex]:
                result.append(vertex)
        return result
                
        
        
    def isEdge(self, x, y):
        return y in self.__outbound[x]
           
class GraphWithInbound:
    def __init__(self, n):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges;
        '''
        self.__cost = {}
        self.__outbound = {}
        self.__inbound = {}
        for vertex in range(n):
            self.__outbound[vertex] = []
            self.__inbound[vertex] = []

    def add_edge(self, x, y, c=1):
        '''Adds an edge from x to y of cost c.
        Return True on success, False if the edge already exists. Precond: x and y exists
        '''
        if self.isEdge(x, y):
            return False
        self.__outbound[x].append(y)
        self.__inbound[y].append(x)
        self.__cost[x,y] = c
        return True
        
    def parseX(self):
        '''Returns something that can be iterated and produces all the vertices of the graph
        '''
        return list(self.__outbound.keys())
    
    def parseNOut(self, x):
        return list(self.__outbound[x])
        
    def parseNIn(self, x):
        return list(self.__inbound[x])
        
    def isEdge(self, x, y):
        return y in self.__outbound[x]
        
    def cost(self, x, y):
        '''Returns the cost of the edge (x,y). Precond: (x,y) is an edge
        '''
        return self.__cost[(x,y)]

class GraphWithSetOfNeighbors:
    def __init__(self, n):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges;
        '''
        self.__outbound = {}
        self.__inbound = {}
        for vertex in range(n):
            self.__outbound[vertex] = set()
            self.__inbound[vertex] = set()

    def add_edge(self, x, y):
        '''Adds an edge from x to y. Return True on success, False if the edge already exists. Precond: x and y exists
        '''
        if self.isEdge(x, y):
            return False
        self.__outbound[x].add(y)
        self.__inbound[y].add(x)
        return True
        
    def parseX(self):
        '''Returns something that can be iterated and produces all the vertices of the graph
        '''
        return list(self.__outbound.keys())
    
    def parseNOut(self, x):
        return list(self.__outbound[x])
        
        
    def parseNIn(self, x):
        return list(self.__inbound[x])
        
    def isEdge(self, x, y):
        return y in self.__outbound[x]

class UndirectedGraph:
    def __init__(self, n):
        '''Constructs a graph with n vertices numbered from 0 to n-1 and no edges;
        '''
        if isinstance(n, int):
            vertices = range(n)
        else:
            vertices = n
        self.__cost = {}
        self.__neighbors = {}
        for vertex in vertices:
            self.__neighbors[vertex] = []

    def add_edge(self, x, y, c=1):
        '''Adds an edge from x to y of cost c.
        Return True on success, False if the edge already exists. Precond: x and y exists
        '''
        if self.isEdge(x, y):
            return False
        self.__neighbors[x].append(y)
        self.__neighbors[y].append(x)
        self.__cost[x,y] = c
        self.__cost[y,x] = c
        return True
        
    def parseX(self):
        '''Returns something that can be iterated and produces all the vertices of the graph
        '''
        return list(self.__neighbors.keys())
    
    def parseN(self, x):
        return list(self.__neighbors[x])
        
    def parseNOut(self, x):
        return self.parseN(x)
        
    def parseNIn(self, x):
        return self.parseN(x)
        
    def isEdge(self, x, y):
        return y in self.__neighbors[x]
        
    def cost(self, x, y):
        '''Returns the cost of the edge (x,y). Precond: (x,y) is an edge
        '''
        return self.__cost[(x,y)]

def print_graph(g):
    print("Outbound")
    for x in g.parseX():
        print(x, ":", end='')
        for y in g.parseNOut(x):
            print(f"({y}, {g.cost(x,y)}) ", end='')
        print()
    print("Inbound")
    for x in g.parseX():
        print(x, ":", end='')
        for y in g.parseNIn(x):
            print(f"({y}, {g.cost(y,x)}) ", end='')
        print()

def parse_graph(g):
    before = time.time()
    for x in g.parseX():
        for y in g.parseNOut(x):
            pass
    after = time.time()
    print("Parse NOut: %sms" %((after-before)*1000, ))
    before = time.time()
    for x in g.parseX():
        for y in g.parseNIn(x):
            pass
    after = time.time()
    print("Parse NIn: %sms" %((after-before)*1000, ))

def create_small_graph(ctor=Graph):
    g = ctor(6)
    costs = {(0,2):2, (1,0):1, (1,2):4, (2,3):3, (3,4):1, (4,2):2, (5,0):3, (5,4):3}
    for e in costs.keys():
        g.add_edge(e[0], e[1], costs[e])
    return g

def create_small_dag_and_cost(ctor=Graph):
    g = ctor(8)
    cost = {(0,3):2, (1,2):4, (3,2):1, (3,5):1, (4,0):3, (6,0):1,(6,1):3, (6,2):8, (2,7):2, (5,7):3,
        (2,0): 1,
        }
    for e in cost.keys():
        g.add_edge(e[0], e[1], cost[e])
    return g

def create_small_undirected(ctor=UndirectedGraph):
    g = ctor(range(1,7))
    lst = [(1,2,3), (1,3,2), (1,4,4), (2,3,2), (2,6,1), (3,4,4),(3,5,3),(3,6,2),(4,5,5),(5,6,5)]
    for x,y,c in lst:
        g.add_edge(x,y,c)
    return g

def create_small_undirected_disconnected(ctor=UndirectedGraph):
    g = ctor(range(1,7))
    lst = [(1,2,3), (3,4,4),(3,5,3),(3,6,2),(4,5,5),(5,6,5),
    #(1,4,4),
    ]
    for x,y,c in lst:
        g.add_edge(x,y,c)
    return g

def create_small_tree(ctor=UndirectedGraph):
    g = ctor(range(1,7))
    lst = [(1,2,3), (3,4,4),(3,5,3),(3,6,2),
    #(1,4,4),
    (4,5,5),
    ]
    for x,y,c in lst:
        g.add_edge(x,y,c)
    return g

def create_random_graph(n, m, ctor=Graph):
    '''Creates a graph with n vertices and m edges, constructed with constructor 'ctor'
    '''
    g = ctor(n)
    before = time.time()
    failures = 0
    for i in range(m):
       x=random.randint(0,n-1)
       y=random.randint(0,n-1)
       while(not g.add_edge(x,y)):
          x=random.randint(0,n-1)
          y=random.randint(0,n-1)
          failures += 1
    after = time.time()
    print("Generating took %s seconds" %(after-before, ))
    print("Failures to add an edge: ", failures)
    return g

def main():
    #n = 100000
    g = create_small_graph(GraphWithInbound)
    #g = create_random_graph(n, 100*n, GraphWithSetOfNeighbors)
    print_graph(g)
    parse_graph(g)

if __name__ == "__main__":
    main()