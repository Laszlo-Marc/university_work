import random

import exchangesort
import shellsort
import tables


def print_menu():
    print("1.Run times for exchange sort")
    print("2.Run times for shell sort")
    print("0.Exit")

def run():
    running = True
    while running:
        print_menu()
        command = input("-->")
        if command == "1":
           print("Exchange sort")
           print(tables.result_table_exchange().draw()  )
        if command == "2":
           print("Shell sort")
           print(tables.result_table_shell().draw())
        if command == "0":
            running = False

run()
