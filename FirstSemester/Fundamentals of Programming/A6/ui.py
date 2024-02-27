#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
import copy

import functions
def print_menu():
    print("add < sum > < category >")
    print("insert < day > < sum > < category >")
    print("remove < day >")
    print("remove < start day > to < end day >")
    print("remove < category >")
    print("list")
    print("list < category >")
    print("list < category > [ < | = | >] < value >")
    print("filter < category >")
    print("filter < category > [ < | = | >] < value >")
    print("undo")
    print("exit")

def run():
    running=True
    expenses = functions.generate10()
    commands=["add","remove","list","filter","exit","undo","insert"]
    types = ["food","internet","clothing","housekeeping","others","transport"]
    relations = ["<",">","="]
    list_for_undo=copy.deepcopy(expenses)
    states = [list_for_undo]
    functions.test_function()
    print_menu()
    while running:

        command=input("Command: ")
        command=command.split(' ')
        if command[0] not in commands:
            print("Invalid command")
        else:
            if command[0]=="exit":
                running=False
            if command[0] == "add":
                if len(command)==3:
                   expense_type = command[2]
                   if expense_type in types:
                        try:
                            sum = int(command[1])
                        except ValueError:
                            print("Invalid type")

                        expenses = functions.add_expense_to_current_day(expenses, sum, expense_type)
                        list_for_undo = copy.deepcopy(expenses)
                        states.append(list_for_undo)
                   else:
                        print("Invalid type!")
                else:
                    print("Invalid command")

            if command[0]=="insert":
                if len(command)==4:
                    expense_type = command[3]
                    if expense_type in types:
                        try:
                            sum = int(command[2])
                            day = int(command[1])
                        except ValueError:
                            print("Invalid type or value!")
                        expenses = functions.insert(expenses, day, sum, expense_type)
                        list_for_undo = copy.deepcopy(expenses)
                        states.append(list_for_undo)
                    else:
                        print("Invalid type")
                else:
                    print("Invalid command")
            if command[0]=="remove":
                try:
                    if len(command) == 2:

                        if command[1] in types:
                            expenses=functions.remove_category(expenses,command[1])
                            list_for_undo = copy.deepcopy(expenses)
                            states.append(list_for_undo)
                        else:

                                day = int(command[1])

                                if day > len(expenses):
                                    print("Invalid day,out of range!")
                                else:
                                    expenses=functions.remove_expense(expenses,day)
                                    list_for_undo = copy.deepcopy(expenses)
                                    states.append(list_for_undo)

                    elif len(command)==4:

                            start_day= int(command[1])
                            end_day=int(command[3])

                            expenses=functions.remove_between(expenses,start_day,end_day)
                            list_for_undo = copy.deepcopy(expenses)
                            states.append(list_for_undo)
                    else:
                        print("Invalid command!")
                except ValueError:
                    print("Invalid type or value!")

            if command[0]=="list":
                try:
                    if len(command)==1:
                        functions.list_all(expenses)
                    elif len(command)==2:
                        if command[1] not in types:
                            print("Invalid type")
                        else:
                            functions.display_expenses_of_type(expenses,command[1])
                    elif len(command)==4:

                            value=int(command[3])

                            if command[1] not in types:
                                print("Invalid type")
                            elif command[2] not in relations:
                                print("Invalid operator")
                            elif command[2]=="<":
                                functions.display_expenses_below_amount(expenses,command[1],value)
                            elif command[2] == ">":
                                functions.display_expenses_above_amount(expenses,command[1],value)
                            elif command[2] == "=":
                                functions.display_expenses_equal_to_amount(expenses,command[1],value)
                    else:
                        print("Invalid command")
                except ValueError:
                        print("Invalid type!")

            if command[0]=="filter":
                try:
                    if len(command)==2:
                        if command[1] not in types:
                            print("Invalid type")
                        else:
                            expenses = functions.filter_expenses_by_type(expenses,command[1])
                            functions.list_all(expenses)
                            list_for_undo = copy.deepcopy(expenses)
                            states.append(list_for_undo)
                    elif len(command)==4:

                            value=int(command[3])

                            if command[1] not in types:
                                print("Invalid type")
                            elif command[2] not in relations:
                                print("Invalid operator")
                            elif command[2]=="<":
                                expenses = functions.filter_expenses_by_type_below_value(expenses,command[1],value)
                                functions.list_all(expenses)
                                list_for_undo = copy.deepcopy(expenses)
                                states.append(list_for_undo)
                            elif command[2] == ">":
                                expenses=functions.filter_expenses_by_type_above_value(expenses,command[1],value)
                                functions.list_all(expenses)
                                list_for_undo = copy.deepcopy(expenses)
                                states.append(list_for_undo)
                            elif command[2] == "=":
                                expenses = functions.filter_expenses_by_type_equal_to_value(expenses,command[1],value)
                                functions.list_all(expenses)
                                list_for_undo = copy.deepcopy(expenses)
                                states.append(list_for_undo)
                except ValueError:
                    print("Invalid type!")
                else:
                    print("Invalid command")
            if command[0]=="undo":
                try:
                    expenses=states.pop(-2)
                except IndexError:
                    print("Can't undo anymore!")
