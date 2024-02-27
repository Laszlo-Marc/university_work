from texttable import Texttable

from texttable import Texttable
import tabulate as tbl

class Board:
    def __init__(self):
        self.cells = [[Cell(row, col) for col in range(9)] for row in range(9)]
        self.initialize()

    def __str__(self):
        return tbl.tabulate(self.cells, tablefmt="simple_grid")

    def initialize(self):
        letters=['A','B','C','D','E','F','G','H']
        for i in range(len(self.cells[0])):
            self.cells[0][i]=i
        for j in range(1,len(self.cells)):
            self.cells[j][0]=letters[j-1]


class Cell:
    def __init__(self,row,column):
        self.row = row
        self.column = column
        self.status = " "

    def __repr__(self):
        return str(self.status)

board=Board()
print(board)