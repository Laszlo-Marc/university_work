import random
import time

#This the euclidean algorithm for caculating the gcd of 2 numbers
def euclid_gcd(x,y):
    r=0
    if(x==0):
        return x
    if(y==0):
        return y
    while (y != 0):
        r = x % y
        x = y
        y = r
    return x


def stein_gcd(a, b):

        if (a == 0):
            return b

        if (b == 0):
            return a

        k = 0

        while(((a | b) & 1) == 0):
            a = a >> 1
            b = b >> 1
            k = k + 1

        # Dividing a by 2 until a becomes odd
        while ((a & 1) == 0):
            a = a >> 1

        # From here on, 'a' is always odd.
        while(b != 0):

            # If b is even, remove all
            # factor of 2 in b
            while ((b & 1) == 0):
                b = b >> 1

            # Now a and b are both odd. Swap if
            # necessary so a <= b, then set
            # b = b - a (which is even).
            if (a > b):

                # Swap u and v.
                temp = a
                a = b
                b = temp

            b = (b - a)

        # restore common factors of 2
        return (a << k)
#This is the recursive euclidean algorithm for calculating the gcd of 2 numbers
def recursive_gcd(x,y):
        if (y == 0):
            return x
        else:
            return recursive_gcd(x, x % y)

def pairs_generator():
    # 3 pairs under 1000
    pairs_under_1000 = [(random.randint(1, 999), random.randint(1, 999)) for _ in range(3)]

    # 3 pairs over 1000 and under 1 billion
    pairs_over_1000_under_billion = [(random.randint(1001, 999999999), random.randint(1001, 999999999)) for _ in
                                     range(3)]

    # 4 pairs over 1 billion
    pairs_over_billion = [(random.randint(1000000001, 10000000000), random.randint(1000000001, 10000000000)) for _ in
                          range(4)]

    # Combining all pairs
    all_pairs = pairs_under_1000 + pairs_over_1000_under_billion + pairs_over_billion
    return all_pairs

#The next 3 functions are for going through different inputs for each algorithm and printing the results
def result_euclid():
    pairs=pairs_generator()
    for pair in pairs:
        num1,num2=pair
        start = time.perf_counter()
        res = euclid_gcd(num1, num2)
        end = time.perf_counter()
        time_result=end-start
        print("Input1: " + str(num1) + " Input2: " + str(num2) + " GCD: " + str(res) + " Time: " + str(time_result))


def result_stein():
    pairs=pairs_generator()
    for pair in pairs:
        num1,num2=pair
        start = time.perf_counter()
        res = stein_gcd(num1,num2)
        end = time.perf_counter()
        time_result = end - start
        print("Input1: " + str(num1) + " Input2: " + str(num2) + " GCD: " + str(res) + " Time: " + str(time_result))

def result_recursive():
    pairs=pairs_generator()
    for pair in pairs:
        num1,num2=pair
        start = time.perf_counter()
        res = recursive_gcd(num1,num2)
        end = time.perf_counter()
        time_result = end - start
        print("Input1: " + str(num1) + " Input2: " + str(num2) + " GCD: " + str(res) + " Time: " + str(time_result))


def run():
    print("Results for Euclid:\n")
    print(result_euclid())
    print("\n")
    print("Results for Stein:\n")
    print(result_stein())
    print("\n")
    print("Result recursive:\n")
    print(result_recursive())

run()