from repositoy import Repository
from service import Service
from ui import UI

#repo=Repository("example.txt")
#service=Service(repo)
#ui=UI(service)
#ui.run()


def even_sum(l):
    if type(l)!= list:
        raise TypeError("Argument is not a list!")
    sum=0
    for x in l:
        if x % 2==0:
            sum=sum+x
    if sum==0:
        raise ValueError("No even numbers in the list")
    return sum

l=[1,2,3,4,5,6,7,8]

assert even_sum(l)==20
print(even_sum(l))

def function(n):
    """
    If n is an even number d will remain 2 everytime,if n is a prime number the while loop will go until d=n-1 everytime and d will be n-1 at the end
    :param n: int
    :return: bool
    """
    d=2
    while(d<n-1) and n%d>0:
        d+=1
    print(d)
    return d>=n-1

assert function(20)==False
assert function(19)==True

