#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import random


def create_expense(type,money):

    expense = {"expense_type":type,"amount":money}
    return expense

def create_day(list,day):

    day_expenses={"day":day,"expenses":list}
    return day_expenses
def get_day(dict):

    return dict["day"]

def get_amount(dict):

    return dict["amount"]

def get_type(dict):

    return dict["expense_type"]

def generate10():
    """
    This function generate the first 10 days at start up
    :return: the 10 items
    """
    all_days = []

    types = ["housekeeping", "food", "transport", "clothing", "internet", "others"]

    for i in range(1,11):
        expenses = []
        for j in range(2):
            pos = random.randint(0, 5)
            money = random.randint(0, 2000)
            expenses.append(create_expense(types[pos], money))

        days = create_day(expenses, i)
        all_days.append(days)

    return all_days

def test_function():
    # Assuming the functions are in a module named functions

    # Test add_expense_to_current_day
    all_days = [{"day":1,"expenses": []}, {"day":2,"expenses": []}, {"day":3,"expenses": []}]
    money = 50
    type = "food"
    all_days=add_expense_to_current_day(all_days, money, type)
    assert all_days == [{"day":1,"expenses": []}, {"day":2,"expenses": []}, {"day":3,"expenses": [{"expense_type": "food", "amount": 50}]}]

    # Test insert
    all_days = [{"expenses": []}, {"expenses": []}, {"expenses": []}]
    day_index = 2
    money = 30
    type = "internet"
    insert(all_days, day_index, money, type)
    assert all_days == [{"expenses": []}, {"expenses": [{"expense_type": "internet", "amount": 30}]}, {"expenses": []}]

    # Test remove_expense
    all_days = [{"expenses": [{"expense_type": "food", "amount": 50}]}, {"expenses": []}, {"expenses": []}]
    day = 1
    remove_expense(all_days, day)
    assert all_days == [{"expenses": []}, {"expenses": []}]

    # Test remove_between
    all_days = [{"expenses": []}, {"expenses": []}, {"expenses": []}, {"expenses": []}]
    start_day = 2
    end_day = 4
    remove_between(all_days, start_day, end_day)
    assert all_days == [{"expenses": []}]

    # Test remove_category
    all_days = [{"expenses": [{"expense_type": "food", "amount": 50}]},
                {"expenses": [{"expense_type": "internet", "amount": 30}]}, {"expenses": []}]
    expense_type = "food"
    remove_category(all_days, expense_type)
    assert all_days == [{"expenses": []}, {"expenses": [{"expense_type": "internet", "amount": 30}]}, {"expenses": []}]


def add_expense_to_current_day(all_days,money,type):
    """
    This function add an expense to the current day
    :param all_days: the list
    :param money: money amount
    :param type: specified type
    :return: modified list
    """
    new_expense = create_expense(type, money)
    all_days[-1]["expenses"].append(new_expense)
    return all_days


def insert(all_days,day_index,money,type):
    """
    This function inserts an expense to a specified day
    :param all_days: the list
    :param day_index: specified day
    :param money: money ammount
    :param type: specified type
    :return: modified list
    """
    if 0 < day_index <= 30:
        new_expense = create_expense(type, money)

        # Check if the day exists
        if day_index <= len(all_days):
            all_days[day_index - 1]["expenses"].append(new_expense)
        else:
            # Create the day and add the expense
            new_day = create_day([new_expense], day_index)
            all_days.append(new_day)

        return all_days
def remove_expense(all_days,day):
    """
    This function removes a whole day of expenses
    :param all_days: all the days
    :param day: specified day
    :return: modified list
    """
    all_days.pop(day-1)
    return all_days

def remove_between(all_days,start_day,end_day):
   """
   This function removes all the days in a specified range
   :param all_days: all the days
   :param start_day: starting day
   :param end_day: ending day
   :return: the modified list
   """
   del all_days[start_day-1:end_day]
   return all_days

def remove_category(all_days,type):
    """
    This function removes a specified category
    :param all_days: the list
    :param type: the type specified
    :return: the modified list
    """
    for day in all_days:
        day["expenses"] = [expense for expense in day["expenses"] if expense["expense_type"] != type]
    return all_days
def list_all(all_days):
    """
    This function displays the whole list
    :param all_days: the days and their expenses
    :return: none
    """
    for day in all_days:
        print("Day: ", day["day"])
        for expense in day["expenses"]:
            print("Expense Type: ", expense["expense_type"], " Amount:", expense["amount"])


def display_expenses_of_type(all_days, expense_type):
    """
    This function displays the expenses that are of the specified type
    :param all_days: the days with their expenses
    :param expense_type: the type of expense
    :param max_amount: the value specified
    :return: none
    """
    for day in all_days:
        day_number = day["day"]
        expenses_of_type = [expense for expense in day["expenses"] if expense["expense_type"] == expense_type]

        if expenses_of_type:
            print(f"Expenses of type '{expense_type}' for Day {day_number}:")
            for expense in expenses_of_type:
                print(f"  Amount: {expense['amount']}")
        else:
            print(f"No expenses of type '{expense_type}' for Day {day_number}")


def display_expenses_below_amount(all_days, expense_type, max_amount):
    """
    This function displays the expenses that are of the specified type and with an amount lower than the value specified
    :param all_days: the days with their expenses
    :param expense_type: the type of expense
    :param max_amount: the value specified
    :return: none
    """
    for day in all_days:
        day_number = day["day"]
        eligible_expenses = [expense for expense in day["expenses"] if
                             expense["expense_type"] == expense_type and expense["amount"] < max_amount]

        if eligible_expenses:
            print(f"Expenses of type '{expense_type}' below {max_amount} for Day {day_number}:")
            for expense in eligible_expenses:
                print(f"  Amount: {expense['amount']}")
        else:
            print(f"No eligible expenses of type '{expense_type}' below {max_amount} for Day {day_number}")
def display_expenses_above_amount(all_days, expense_type, max_amount):
    """

    This function displays the expenses that are of the specified type and with an amount higher than  the value specified
    :param all_days: the days with their expenses
    :param expense_type: the type of expense
    :param max_amount: the value specified
    :return: none
    """
    for day in all_days:
        day_number = day["day"]
        eligible_expenses = [expense for expense in day["expenses"] if
                             expense["expense_type"] == expense_type and expense["amount"] > max_amount]

        if eligible_expenses:
            print(f"Expenses of type '{expense_type}' below {max_amount} for Day {day_number}:")
            for expense in eligible_expenses:
                print(f"  Amount: {expense['amount']}")
        else:
            print(f"No eligible expenses of type '{expense_type}' below {max_amount} for Day {day_number}")

def display_expenses_equal_to_amount(all_days, expense_type, max_amount):
    """
    This function displays the expenses that are of the specified type and with an amount equal to the value specified
    :param all_days: the days with their expenses
    :param expense_type: the type of expense
    :param max_amount: the value specified
    :return: none
    """
    for day in all_days:
        day_number = day["day"]
        eligible_expenses = [expense for expense in day["expenses"] if
                             expense["expense_type"] == expense_type and expense["amount"] == max_amount]

        if eligible_expenses:
            print(f"Expenses of type '{expense_type}' below {max_amount} for Day {day_number}:")
            for expense in eligible_expenses:
                print(f"  Amount: {expense['amount']}")
        else:
            print(f"No eligible expenses of type '{expense_type}' below {max_amount} for Day {day_number}")

def filter_expenses_by_type(all_days, expense_type):
    """
    This function filters the expenses that are of the specified type
    :param all_days: all the days with their expenses
    :param expense_type: the type of expense
    :return: the modifies list
    """
    filtered_expenses = []

    for day in all_days:
        filtered_day_expenses = [expense for expense in day["expenses"] if expense["expense_type"] == expense_type]
        filtered_expenses.append({"day": day["day"], "expenses": filtered_day_expenses})

    return filtered_expenses

def filter_expenses_by_type_below_value(all_days, expense_type, value):
    """
    This function filters the expenses that are of the specified type and with an amount lower to the value specified
    :param all_days: all the days and their expenses
    :param expense_type: the type of expense
    :param value: the specified value
    :return: the modified list
    """
    filtered_expenses = []


    for day in all_days:
        filtered_day_expenses = [expense for expense in day["expenses"] if
                                 expense["expense_type"] == expense_type and expense["amount"] < value]
        filtered_expenses.append({"day": day["day"], "expenses": filtered_day_expenses})

    return filtered_expenses

def filter_expenses_by_type_above_value(all_days, expense_type, value):
    """
    This function filters the expenses that are of the specified type and with an amount higher to the value specified
    :param all_days: the list with all the days and their expenses
    :param expense_type: the type of expense
    :param value: the specified value
    :return: the modifies list
    """
    filtered_expenses = []

    #
    for day in all_days:
        filtered_day_expenses = [expense for expense in day["expenses"] if
                                 expense["expense_type"] == expense_type and expense["amount"] > value]
        filtered_expenses.append({"day": day["day"], "expenses": filtered_day_expenses})

    return filtered_expenses

def filter_expenses_by_type_equal_to_value(all_days, expense_type, value):
    """
    This function filters the expenses that are of the specified type and with an amount equal to the value specified
    :param all_days: all the days with their expenses
    :param expense_type: the type of expense
    :param value: the specified value
    :return: the modified list
    """
    filtered_expenses = []


    for day in all_days:
        filtered_day_expenses = [expense for expense in day["expenses"] if
                                 expense["expense_type"] == expense_type and expense["amount"] == value]
        filtered_expenses.append({"day": day["day"], "expenses": filtered_day_expenses})

    return filtered_expenses



