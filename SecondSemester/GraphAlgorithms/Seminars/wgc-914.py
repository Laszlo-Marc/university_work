class WolfGoatCabbageVertex:
    def __init__(self, pos):
        self.pos = tuple(pos)
    def __str__(self):
        return self.__repr__()
    def __repr__(self):
        left = []
        right = []
        names = ['W', 'G', 'C', 'B']
        for i in range(4):
            if self.pos[i]:
                right.append(names[i])
            else:
                left.append(names[i])
        return ' '.join(left) + '|' + ' '.join(right)

    def __eq__(self, other):
        if not isinstance(other, WolfGoatCabbageVertex):
            return False
        return self.pos == other.pos
    def __ne__(self, other):
        return not self.__eq__(other)
    def __hash__(self):
        return self.pos.__hash__()

    def parseN(self):
        for i in range(4):
            lst = list(self.pos)
            if lst[i] == lst[3]:
                lst[i] = not self.pos[i]
                lst[3] = not self.pos[3]
                v = WolfGoatCabbageVertex(lst)
                if v.is_valid():
                    yield v
                
    def is_valid(self):
        return self.pos[1] == self.pos[3] or (self.pos[1] != self.pos[0]
            and self.pos[1] != self.pos[2])

class WolfGoatCabbageGraph:
    def parseX(self):
        '''Returns something that can be iterated and produces all the vertices of the graph
        '''
        raise Exception("Not implemented")
    
    def parseNOut(self, x):
        return x.parseN()
        
    def parseNIn(self, x):
        return x.parseN()
        
    def isEdge(self, x, y):
        for v in x.parseN():
            if v == y:
                return True
        return False

    def start(self):
        return WolfGoatCabbageVertex([False,False,False,False,])
    def dest(self):
        return WolfGoatCabbageVertex([True,True,True,True,])
