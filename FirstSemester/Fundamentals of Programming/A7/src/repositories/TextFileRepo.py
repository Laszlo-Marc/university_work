from src.domain.expense import Expense


class TextFileRepository:
    def __init__(self,filename):
        self.filename=filename
        self.expenses=self.load_expenses()
        self.undo_stack=[]

    def load_expenses(self):
        expenses=[]
        try:
            with open(self.filename,'r') as f:
                for line in f:
                    day,type,amount=line.strip().split(',')
                    expense=Expense(int(day),type,int(amount))
                    expenses.append(expense)
            return expenses
        except FileNotFoundError:
            return []

    def save_expenses(self):
        with open(self.filename,'w') as f:
            for expense in self.expenses:
                f.write(f'{expense.get_day()},{expense.get_type()},{expense.get_amount()}\n')


    def add_expense(self,expense):
        self.undo_stack.append(('add',expense))
        self.expenses.append(expense)
        self.save_expenses()

    def filter_expenses(self,amount):
        self.undo_stack.append((('filter'),self.expenses))
        self.expenses=[e for e in self.expenses if e.get_amount()>amount]
        self.clear()
        self.save_expenses()

    def clear(self):
        with open("expenses.txt","w") as f:
            f.truncate()

    def display_expenses(self):
        for expense in self.expenses:
            print(f'Day {expense.get_day()}:\n {expense.get_type()}: {expense.get_amount()}')

    def undo(self):

        if self.undo_stack:
            action,data=self.undo_stack.pop()
            if action=='add':
                self.expenses.remove(data)
            if action=='filter':
                self.expenses=data
            self.save_expenses()