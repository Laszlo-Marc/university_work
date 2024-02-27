import pickle

import pickle

class BinaryRepository:

    def __init__(self, filename):
        self.filename = filename
        self.expenses = self.load_expenses()
        self.undo_stack = []

    def load_expenses(self):
        """
        Function for loading entities from the file
        :return: the list
        """
        try:
            with open(self.filename, 'rb') as f:
                return pickle.load(f)
        except FileNotFoundError:
            return []

    def save_expenses(self):
        """
        Function for saving an expense to the file
        :return: none
        """
        with open(self.filename, 'wb') as f:
            pickle.dump(self.expenses, f)

    def add_expense(self, expense):
        """
        Function for adding an expense to the list
        :param expense: the expense to add
        :return: none
        """
        self.undo_stack.append(('add', expense))
        self.expenses.append(expense)
        self.save_expenses()

    def filter_expenses(self, amount):
        """
        Function to filter the list
        :param amount: amount to filter by
        :return: none
        """
        self.undo_stack.append(('filter', self.expenses.copy()))
        self.expenses = [e for e in self.expenses if e.get_amount() > amount]
        self.clear()
        self.save_expenses()

    def display_expenses(self):
        """
        Function to display expenses
        :return: none
        """
        for expense in self.expenses:
            print(f'Day {expense.get_day()},{expense.get_type()},{expense.get_amount()}')

    def clear(self):
        """
        Function to clear file
        :return: none
        """
        self.expenses = []
        self.save_expenses()

    def undo(self):
        """
        Undo function
        :return: none
        """
        if self.undo_stack:
            action, data = self.undo_stack.pop()
            if action == 'add':
                self.expenses.remove(data)
            elif action == 'filter':
                # Instead of directly assigning the data back, extend the list to preserve the order of operations
                self.expenses.extend(data)
            self.save_expenses()

