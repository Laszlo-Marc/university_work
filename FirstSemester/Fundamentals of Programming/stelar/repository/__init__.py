from domain import Cell


class Repositoy:
    def __init__(self,board):
        self.board=board
        self.cells=board.cells

    def get_cells(self):
        return self.cells




