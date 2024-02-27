from backtracking import find_subsequences_rec, find_subsequences_iterative
from dynamic import partition_minimal_difference, partition_minimal_difference_dynamic


def print_options():
    print("1.Solve the problem recursively.")
    print("2.Solve the problem iteratively.")
    print("3.Solve the problem,naive approach")
    print("4.Solve the problem dynamic approach")
    print("0.Exit the program.")
def run_menu():
    while True:
        print_options()
        opt = int(input("Input option: "))
        if opt == 0:
            return False
        if opt == 1:
            seq=[]
            element = int(input("Add element: "))
            seq.append(element)
            while element !=0:
                element = int(input("Add element: "))
                if element !=0:
                    seq.append(element)
            subs = find_subsequences_rec(seq)
            for sub in subs:
                print(sub)
        if opt ==2:
            seq = []
            element = int(input("Add element: "))
            seq.append(element)
            while element != 0:
                element = int(input("Add element: "))
                if element != 0:
                    seq.append(element)
            subs = find_subsequences_iterative(seq)
            for sub in subs:
                print(sub)
        if opt == 3:
            seq=[]
            element = int(input("Add element: "))
            seq.append(element)
            while element != 0:
                element = int(input("Add element: "))
                if element != 0:
                    seq.append(element)
            min_diff =  partition_minimal_difference(seq)
            print("Minimum difference using naive approach:", min_diff)
        if opt == 4:
            seq=[]
            element = int(input("Add element: "))
            seq.append(element)
            while element != 0:
                element = int(input("Add element: "))
                if element != 0:
                    seq.append(element)
            S1,S2 =  partition_minimal_difference_dynamic(seq)
            print("Subset 1:", S1)
            print("Subset 2:", S2)
run_menu()
