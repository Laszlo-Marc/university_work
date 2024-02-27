import random

from domain import Board


class Service:
    def __init__(self):
        self.repo=Board()
        self.populate()

    def verify(self,row,column,character):
        if row == 1 and column!=8 and column!=1:
            if self.repo.cells[row][column - 1] == character:
                return False
            if self.repo.cells[row][column + 1] == character:
                return False
            if self.repo.cells[row + 1][column - 1] == character:
                return False
            if self.repo.cells[row + 1][column + 1] == character:
                return False
            if self.repo.cells[row + 1][column] == character:
                return False
        elif column == 1 and row!=8 and row!=1:

            if self.repo.cells[row][column + 1] == character:
                return False
            if self.repo.cells[row - 1][column + 1] == character:
                return False
            if self.repo.cells[row - 1][column] == character:
                return False
            if self.repo.cells[row + 1][column + 1] == character:
                return False
            if self.repo.cells[row + 1][column] == character:
                return False
        elif column == 8 and row!=1 and row!=8:

            if self.repo.cells[row][column - 1] == character:
                return False
            if self.repo.cells[row - 1][column] == character:
                return False
            if self.repo.cells[row - 1][column - 1] == character:
                return False
            if self.repo.cells[row + 1][column - 1] == character:
                return False
            if self.repo.cells[row + 1][column] == character:
                return False
        elif row == 1 and column == 1:

            if self.repo.cells[row + 1][column] == character:
                return False
            if self.repo.cells[row + 1][column + 1] == character:
                return False
            if self.repo.cells[row][column + 1] == character:
                return False
        elif row == 1 and column == 8:

            if self.repo.cells[row + 1][column] == character:
                return False
            if self.repo.cells[row + 1][column - 1] == character:
                return False
            if self.repo.cells[row][column - 1] == character:
                return False
        elif row == 8 and column == 1:

            if self.repo.cells[row - 1][column] == character:
                return False
            if self.repo.cells[row - 1][column + 1] == character:
                return False
            if self.repo.cells[row][column + 1] == character:
                return False
        elif row == 8 and column != 1 and column !=8:

            if self.repo.cells[row][column - 1] == character:
                return False
            if self.repo.cells[row][column + 1] == character:
                return False
            if self.repo.cells[row - 1][column - 1] == character:
                return False
            if self.repo.cells[row - 1][column + 1] == character:
                return False
            if self.repo.cells[row - 1][column] == character:
                return False
        elif row == 8 and column == 8:

            if self.repo.cells[row - 1][column] == character:
                return False
            if self.repo.cells[row - 1][column - 1] == character:
                return False
            if self.repo.cells[row][column - 1] == character:
                return False
        else:
            if self.repo.cells[row - 1][column] == character:
                return False
            if self.repo.cells[row + 1][column] == character:
                return False
            if self.repo.cells[row - 1][column - 1] == character:
                return False
            if self.repo.cells[row - 1][column + 1] == character:
                return False
            if self.repo.cells[row][column - 1] == character:
                return False
            if self.repo.cells[row][column + 1] == character:
                return False
            if self.repo.cells[row + 1][column - 1] == character:
                return False
            if self.repo.cells[row + 1][column + 1] == character:
                return False
        return True

    def populate(self):
        i=0
        while i<=10:
            row=random.randint(1,8)
            column=random.randint(1,8)
            if self.verify(row,column,"*"):
                i+=1
                self.repo.cells[row][column]="*"
            print( self.repo.cells[row][column])
        row = random.randint(1, 8)
        column = random.randint(1, 8)
        while self.repo.cells[row][column]=="*":
            row = random.randint(1, 8)
            column = random.randint(1, 8)
        self.repo.cells[row][column].status="E"
        self.place_billies()

    def place_billies(self):
        billies=[]
        i=0
        while i <3:
            row = random.randint(1, 8)
            column = random.randint(1, 8)
            if self.repo.cells[row][column]!="*" or self.repo.cells[row][column]!="B" or self.repo.cells[row][column]!="E":
                billie=(row,column)
                billies.append(billie)
                self.repo.cells[row][column]="B"
                i+=1




service=Service()
print(service.repo)