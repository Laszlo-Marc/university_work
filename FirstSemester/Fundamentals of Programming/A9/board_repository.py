from domain import Board


class BoardRepo:
    def __init__(self):
        self.__moves = []
        self.__board = Board

    def get_moves(self):
        return self.__moves

    def save_move(self,matrix_pos):
        self.__moves.append(matrix_pos)

    def up