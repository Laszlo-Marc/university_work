import random


def wc_exchange(n):
    array = [i for i in range(n)]
    array.reverse()
    return array

def bc_exchange(n):
    array = [i for i in range(n)]
    return array

def average_exchange(n):
    array = []
    for i in range(n):
        array.append(random.randint(0,100))
    return array

def wc_shell(n):
        gaps = [1]
        k = 1
        while True:
            gap = 2 ** k + 1
            if gap >= n:
                break
            gaps.extend([gap, 2 * gap - 1])
            k += 1

        arr = [i for i in range(n)]
        return arr, gaps

def gaps_shell(n):
    gap = n//2
    gaps =[]
    while gap >=1:
        gaps.append(gap)
        gap //=2
    return gaps
