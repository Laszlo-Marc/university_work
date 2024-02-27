import random
from src.domain.expense import Expense
from src.repositories.BinaryRepo import BinaryRepository
from src.repositories.MemoryRepo import MemoryRepository
from src.repositories.TextFileRepo import TextFileRepository

class Services:
    EXPENSE_TYPES = {
        "internet": 0,
        "clothing": 1,
        "others": 2,
        "transport": 3,
        "food": 4,
        "housekeeping": 5
    }

    def __init__(self, repository_type='memory'):
        if repository_type == 'memory':
            self.repository = MemoryRepository()
        elif repository_type == 'text':
            self.repository = TextFileRepository('expenses.txt')
        elif repository_type == 'binary':
            self.repository = BinaryRepository('expenses.bin')
        else:
            raise ValueError("Invalid repository type. Supported types: 'memory', 'text', 'binary'")
        self.undo_stack = []

    def generate_expenses(self):
        """
        Function for generating entities at start up
        :return: none
        """
        for i in range(20):
            amount = random.randint(0, 1000)
            expense_type = random.choice(list(self.EXPENSE_TYPES.keys()))
            expense = Expense(i+1, expense_type, amount)
            self.repository.add_expense(expense)

    def add_expense(self, day, expense_type, amount):
        """
        Function for adding an expense
        :param day:expense day
        :param expense_type: type of expense
        :param amount: expense amount
        :return: none
        """
        expenses = self.repository.load_expenses()
        self.undo_stack.append(('add', expenses))
        expense = Expense(day, expense_type, amount)
        self.repository.add_expense(expense)

    def test_add_expense(self):
        self.add_expense(21,"food",200)
        assert self.repository.load_expenses()[-1].get_day()==21
        assert self.repository.load_expenses()[-1].get_type() == "food"
        assert self.repository.load_expenses()[-1].get_amount() == 200
        self.add_expense(22, "internet", 300)
        assert self.repository.load_expenses()[-1].get_day() == 22
        assert self.repository.load_expenses()[-1].get_type() == "internet"
        assert self.repository.load_expenses()[-1].get_amount() == 300

    def display_expenses(self):
        """
        Function for displaying the expenses
        :return: none
        """
        self.repository.display_expenses()

    def clear(self):
        """
        Function to clear the file
        :return: none
        """
        self.repository.clear()

    def undo(self):
        """
        Undo function
        :return: none
        """
        self.repository.undo()

    def filter_expenses(self, amount):
        """
        Funtion for filtering the list
        :param amount: amount to filter by
        :return: none
        """
        expenses = self.repository.load_expenses()
        self.undo_stack.append(('filter', expenses))
        self.repository.filter_expenses(amount)
