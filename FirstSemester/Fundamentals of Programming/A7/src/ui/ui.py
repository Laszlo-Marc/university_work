from src.services.services import Services

class UI:
    def __init__(self):
        self.services = None

    def choose_repo(self, repo_choice):
        if repo_choice == '1':
            self.services = Services('memory')
        elif repo_choice == '2':
            self.services = Services('text')
        elif repo_choice == '3':
            self.services = Services('binary')
        else:
            print("Invalid repository choice.")

    def run(self):
        print("1.Memory")
        print("2.Text File")
        print("3.Binary")
        choice = input("Which repository do you want to use: ")

        if choice in ['1', '2', '3']:
            self.choose_repo(choice)
        else:
            print("Invalid choice. Exiting.")
            return False
        self.clear()
        self.services.test_add_expense()
        self.services.generate_expenses()
        while True:
            print("1.Add expense")
            print("2.Display expenses")
            print("3.Filter expenses")
            print("4.Undo")
            print("5.Exit")
            choice = input("What is your choice: ")

            if choice == '1':
                self.add_expense()
            elif choice == '2':
                self.display_expenses()
            elif choice == '3':
                self.filter_expenses()
            elif choice == '4':
                self.undo()
            elif choice == '5':
                return False
            else:
                print("Invalid choice. Please choose again.")

    def add_expense(self):
        types = ["internet", "clothing", "others", "transport", "food", "housekeeping"]
        try:
            day = int(input("Input day: "))
            expense_type = input("Expense type: ")
            amount = int(input("Amount: "))
            if day < 1 or day > 30 or expense_type not in types:
                print("Invalid day or type!")
            else:
                self.services.add_expense(day, expense_type, amount)
        except ValueError:
            print("The day and amount need to be integers!")

    def display_expenses(self):
        self.services.display_expenses()

    def filter_expenses(self):
        try:
            amount = int(input("Choose amount: "))
            self.services.filter_expenses(amount)
        except ValueError:
            print("The amount needs to be an integer!")

    def clear(self):
        self.services.clear()

    def undo(self):
        self.services.undo()


