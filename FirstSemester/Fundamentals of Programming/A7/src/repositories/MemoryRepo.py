class MemoryRepository:
    def __init__(self):
        self.expenses = []
        self.operations = []

    def load_expenses(self):
        return self.expenses

    def add_expense(self, expense):
        """
        Function to add expense
        :param expense: expense to add
        :return: none
        """
        self.expenses.append(expense)
        self.operations.append(('add', expense))

    def filter_expenses(self, amount):
        """
        Filter function
        :param amount: amount to filter by
        :return: none
        """
        self.operations.append(('filter', self.expenses))
        self.expenses = [e for e in self.expenses if e.get_amount() > amount]

    def display_expenses(self):
        """
        Funtion to display all
        :return: none
        """
        for expense in self.expenses:
            print(f'Day {expense.get_day()}:\n {expense.get_type()}:{expense.get_amount()} ')

    def clear(self):
        self.expenses.clear()

    def undo(self):
        if self.operations:
            operation, data = self.operations.pop()
            if operation == 'add':
                self.expenses.remove(data)
            elif operation == 'filter':

                self.expenses = data
