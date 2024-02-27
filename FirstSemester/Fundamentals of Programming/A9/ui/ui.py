from domain.board import Board
from domain.point import Point
from ui.ai import AI


class UI:
    def __init__(self, rows_nr, columns_nr, modee, turnn):
        self._game_mode = modee
        self._ai_turn = turnn
        self._game_board = Board(rows_nr, columns_nr)
        if self._ai_turn is True:
            self._game_board.set_turn("second")
        self._game_board.create_board()
        self._game_running = True
        self._ai = AI()

    def print_board(self):
        print(self._game_board)

    def game_over(self):
        self._game_running = False

    def print_turn(self):
        if self._game_mode == "players":
          if self._game_board.get_turn() == "first":
              print("\nCurrent player: Player 1.\n")
          else:
              print("\nCurrent player: Player 2.\n")
        else:
            if self._ai_turn is False:
                print("\nYour turn!\n")

    def start(self):
        start_text = """ WELCOME TO OBSTRUCTION GAME!
         In case you haven't played this before I will give a simple explanation:
         The objective of this game is to ultimately stop the other player from being 
         able to put a mark in the grid,you do so by putting your own mark in the grid and 
         the neighbouring cells of the mark will be blocked,it will be easier to understand while playing.
         HAVE FUN!
        """
        print(start_text.rjust())
        if self._game_mode == "players":
            while self._game_running:
                self.print_board()
                self.print_turn()
                try:
                    x = int(input("Enter the x coordinates of your move: "))
                    y = int(input("Enter the y coordinates of your move: "))
                    point = Point(x,y)
                    self._game_board.execute_move(point)
                    if self._game_board.available_moves() == 0:
                        self.game_over()
                        print(self._game_board)
                        if self._game_board.get_turn() == "first":
                            print(f"\nPlayer 2 wins!")
                        else:
                            print(f"\nPlayer 1 wins!")
                except ValueError:
                    print("Invalid move!Inputs need to be integers!")
        else:
            while self._game_running is True:
                if self._ai_turn is False:
                    try:
                        print(self._game_board)
                        self.print_turn()
                        x = int(input("Enter the x coordinates of your move: "))
                        y = int(input("Enter the y coordinates of your move: "))
                        point = Point(x, y)
                        self._game_board.execute_move(point)
                        self._ai_turn = not self._ai_turn
                        if self._game_board.available_moves() == 0:
                            self.game_over()
                            print(self._game_board)
                            print(f"\nYou win!")
                    except ValueError:
                        print("Invalid inputs!Coordinates need to be integers!")
                else:
                    move = self._ai.get_input(self._game_board)
                    self._game_board.execute_move(move)
                    self._ai_turn = not self._ai_turn
                    if self._game_board.available_moves() == 0:
                        self.game_over()
                        print(self._game_board)
                        print(f"\nComputer wins!")


if __name__ == "__main__":
    with open("settings.properties","r") as f:
        mode = f.readline().strip().split(" ")[2]
    initial_input_wrong = True
    turn = 1
    while initial_input_wrong is True:
        try:
            turn = int(input("Enter 1 if you want to begin or 2 if you want the computer/player2 to begin: "))
        except ValueError:
            print("What are you doing?(^-^) Just 1 or 2")
            continue
        if turn != 1 and turn != 2:
            print("Come on now it's not that hard, 1 or 2!")
            continue
        initial_input_wrong = False
    if turn == 1:
        turn = False
    else:
        turn = True
    rows = columns = 0
    while True:
        try:
            rows = int(input("Please enter the number of rows: "))
            columns = int(input("Please enter the number of columns: "))
        except ValueError:
            print("Numbers please(^o^)")
            continue
        break
    ui = UI(rows, columns, mode,turn)
    ui.start()
