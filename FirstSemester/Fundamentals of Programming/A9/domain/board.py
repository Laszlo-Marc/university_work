from domain import point
from domain.point import Point


class MoveError(Exception):
    pass

class Board:
    def __init__(self,rows,columns):
        self._turn = "first"
        self.__board = []
        self.__rows = rows
        self.__columns = columns

    def get_board(self):
        """
        Getter method for the board
        :return: the board
        """
        return self.__board

    def get_rows(self):
        """
        Getter method for the rows
        :return: rows
        """
        return self.__rows

    def get_columns(self):
        """
        Getter method for the columns
        :return: columns
        """
        return self.__columns

    def get_turn(self):
        """
        Getter method for the turn
        :return: turn
        """
        return self._turn

    def set_columns(self, columns):
        """
        Setter method for columns
        :param columns:
        :return: None
        """
        self.__columns = columns

    def set_rows(self, rows):
        """
        Setter method for the rows
        :param rows:
        :return: None
        """
        self.__rows = rows

    def set_turn(self,turn):
        """
        Setter method for the turn
        :param turn:
        :return: None
        """
        self._turn = turn

    def set_move(self,point):
        """
        This method sets the move made by the players
        :param point: a point on the board
        :return: None
        """

        x = point.get_x()
        y = point.get_y()
        if self._turn == "first":
            self.__board[x][y] = 'X'
            self.set_turn("second")
        else:
            self.__board[x][y] = 'O'
            self.set_turn("first")

    def available_moves(self):
        """
        This method returns the number of available moves
        :return: available moves
        """
        available_moves_counter = 0
        rows = self.get_rows()
        columns = self.get_columns()
        for row in range(rows):
            for column in range(columns):
                if self.__board[row][column] == '#':
                    available_moves_counter += 1
        return available_moves_counter

    def execute_move(self,point):
        """
        This method executes a move made by the playes
        :param point: a point on the board
        :return: None
        """
        self.validate_move(point)
        self.set_move(point)
        self.mark_borders_of_move(point)

    def create_board(self):
        """
        This method creates the playing board
        :return: None
        """
        for row in range(self.get_rows()):
            new_row = []
            for column in range(self.get_columns()):
                new_row.append('#')
            self.__board.append(new_row)

    def potential_move_is_valid(self,point):
        """
        This method checks if a potential move is valid
        :param point: a point on the board
        :return: boolean value
        """
        x = int(point.get_x())
        y = int(point.get_y())
        if x > self.get_rows() - 1 or x < 0 or y > self.get_columns() or y < 0:
            return False
        if self.__board[x][y] != '#':
                return False
        return True

    def validate_move(self,point):
        """
        This method validates a move
        :param point: a point on the board
        :return: error if needed
        """
        try:
            x = int(point.get_x())
            y = int(point.get_y())
        except ValueError:
            raise MoveError("Not a valid move!Coordinates need to be integers!")
        if x > self.get_rows() - 1 or x < 0 or y > self.get_columns() - 1 or y < 0:
            raise MoveError("You're playing on another board:)")
        if self.__board[x][y] != '#':
            raise MoveError("Not valid!Too close to another point.")

    def get_move_list(self):
        """
        Getter method for the method for moves
        :return: list of moves
        """
        moves = []
        rows = self.get_rows()
        columns = self.get_columns()
        for row in range(rows):
            for column in range(columns):
                if self.__board[row][column] == '#':
                    moves.append(Point(row, column))
        return moves

    def mark_borders_of_move(self,point):
        """
        This method marks a move made by the players on the board
        :param point: a point on the board
        :return: None
        """
        x = point.get_x()
        y = point.get_y()
        if x - 1 >= 0 and y - 1 >= 0 and self.__board[x - 1][y - 1] == '#':  # upper left corner
            self.__board[x - 1][y - 1] = '*'
        if x - 1 >= 0 and self.__board[x - 1][y] == '#':  # directly above the move
            self.__board[x - 1][y] = '*'
        if x - 1 >= 0 and y + 1 < self.get_columns() and self.__board[x - 1][y + 1] == '#':  # upper right corner
            self.__board[x - 1][y + 1] = '*'
        if y - 1 >= 0 and self.__board[x][y - 1] == '#':  # directly to the left of the move
            self.__board[x][y - 1] = '*'
        if y + 1 < self.get_columns() and self.__board[x][y + 1] == '#':  # directly to the right of the move
            self.__board[x][y + 1] = '*'
        if x + 1 < self.get_rows() and y - 1 >= 0 and self.__board[x + 1][y - 1] == '#':  # lower left corner
            self.__board[x + 1][y - 1] = '*'
        if x + 1 < self.get_rows() and self.__board[x + 1][y] == '#':  # directly under the move
            self.__board[x + 1][y] = '*'
        if x + 1 < self.get_rows() and y + 1 < self.get_columns() and self.__board[x + 1][y + 1] \
                == '#':  # lower right corner (AHH WHY IS IT ON 2 ROWS YEX)
            self.__board[x + 1][y + 1] = '*'

    def __str__(self):
        """
        overriding the initial str to the board
        :return: the string
        """
        s = "\nx\n"
        row = 0
        for element in self.__board:
            s += f"{row} {element}\n"
            row += 1
        row = self.__board[0]
        s += "  "
        for column in range(0, len(row)):
            s += f"  {column}  "
        s += "  y"
        return s