# Write the implementation for A5 in this file
#
from cmath import sqrt
#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def create_comp_num_list(real,imag):
    return [real,imag]
def get_real_in_ls(ls):
    return ls[0]
def get_im_in_ls(ls):
    return ls[1]
def generate_10_nums_lists():
    import random
    nums=[]

    for i in range(10):
        auxnum = []
        auxnum.append(random.randint(-30,30))
        auxnum.append(random.randint(-30, 30))
        nums.append(auxnum)

    return nums
def add_n_nums_ls(real,imag):
    comp_ls = generate_10_nums_lists()
    ls = create_comp_num_list(real,imag)
    comp_ls.append(ls)
    real_list=[]
    imag_list=[]
    return comp_ls
def get_real_list(ls):
    real_list=[]
    for i in range(len(ls)):
        real_list.append(ls[i][0])
    return real_list
def get_img_list(ls):
    imag_list=[]
    for i in range(len(ls)):
        imag_list.append(ls[i][1])
    return imag_list

# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def create_comp_num_dict(real,imag):
    return {"real":real,
            "imag":imag}
def get_real_dict(dict):
    return dict["real"]
def get_imag_dict(dict):
    return dict["imag"]

def list_of_dicts():
    import random
    list_of_dicts=[]
    for i in range(10):
        aux_dict={}
        auxrl=random.randint(-30,30)
        auxim=random.randint(-30,30)
        aux_dict["real"]=auxrl
        aux_dict["imag"] = auxim
        list_of_dicts.append(aux_dict)
    return list_of_dicts
def get_imag_list_from_dict(ls):
    imag_list=[]
    for i in range(len(ls)):
        im=get_imag_dict(ls[i])
        imag_list.append(im)
    return imag_list

def get_real_list_from_dict(ls):
    real_list = []
    for i in range(len(ls)):
        rl = get_real_dict(ls[i])
        real_list.append(rl)
    return real_list


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def modulus_list(c):
  return sqrt(c[0]**2 + c[1]**2).real
def prob_set_a3(complex_numbers):
    moduli = [modulus_list(c) for c in complex_numbers]
    moduli.sort()
    longest = []
    for c in complex_numbers:
        index = moduli.index(modulus_list(c))

        if index >= len(longest):
            longest.append(c)
        else:
            longest[index] = c
    return len(longest), longest

def modulus_dict(c):
  return sqrt(c["real"]**2 + c["imag"]**2).real
def prob_set_a3_dict(complex_numbers):
    moduli = [modulus_dict(c) for c in complex_numbers]
    moduli.sort()
    longest = []
    for c in complex_numbers:
        index = moduli.index(modulus_dict(c))
        if index >= len(longest):
            longest.append(c)
        else:
            longest[index] = c
    return len(longest), longest
def prob_set_b12(ls,n):
    subsequence = []
    rl=get_real_list(ls)
    i = 1
    while i < n - 1:
        if (rl[i] >= rl[i - 1] and rl[i] > rl[i + 1]) or (rl[i] <= rl[i - 1] and rl[i] < rl[i + 1]):
            subsequence.append(ls[i])
            i += 1
        else:
            i += 1

    return subsequence
def prob_set_b12_dict(ls,n):
    subsequence = []
    rl=get_real_list_from_dict(ls)
    i = 1
    while i < n - 1:
        if (rl[i] >= rl[i - 1] and rl[i] > rl[i + 1]) or (rl[i] <= rl[i - 1] and rl[i] < rl[i + 1]):
            subsequence.append(ls[i])
            i += 1
        else:
            i += 1

    return subsequence
#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#
def print_options1():
    print("Choose an option from the following:")
    print("1.Represent the complex numbers using lists.")
    print("2.Represent the complex numbers using a dictionary.")
    print("3.Exit")

def print_options2():
    print("1.Find the length and elements of a longest subarray of numbers having increasing modulus")
    print("2.Find the length and elements of a longest alternating subsequence, when considering each number's real part")
    print("3.Nothing")
def menu():
    while True:
        print_options1()
        opt = int(input("What would you like: "))
        if opt == 3:
            return False
        if opt == 1:
            print("How many numbers would you like to generate?")
            n=int(input("n= "))
            complex_numbers_list_of_lists = generate_10_nums_lists()
            for i in range(n):
                real=int(input("The real part: "))
                im=int(input("The imaginary part: "))
                complex_numbers_list_of_lists.append(create_comp_num_list(real,im))
            print(complex_numbers_list_of_lists)
            while True:
                print_options2()
                opt = int(input("Which problem do you want to solve: "))
                if opt==3:
                    return False
                if opt == 1:
                    n = len(complex_numbers_list_of_lists)
                    length,subsequence = prob_set_a3(complex_numbers_list_of_lists)
                    print(length)
                    print(subsequence)
                if opt==2:
                    n=len(complex_numbers_list_of_lists)
                    print(prob_set_b12(complex_numbers_list_of_lists,n))
        if opt == 2:
            print("How many numbers would you like to generate?")
            n=int(input("n= "))
            complex_numbers_list_of_dicts = list_of_dicts()
            for i in range(n):
                real=int(input("The real part: "))
                im=int(input("The imaginary part: "))
                complex_numbers_list_of_dicts.append(create_comp_num_dict(real,im))
            print(complex_numbers_list_of_dicts)
            while True:
                print_options2()
                opt = int(input("Which problem do you want to solve: "))
                if opt==3:
                    return False
                if opt == 1:
                    n = len(complex_numbers_list_of_dicts)
                    length,subsequence = prob_set_a3_dict(complex_numbers_list_of_dicts)
                    print(length)
                    print(subsequence)
                if opt==2:
                    n=len(complex_numbers_list_of_dicts)
                    print(prob_set_b12_dict(complex_numbers_list_of_dicts,n))

if __name__ == "__main__":
    menu()



