import math
import random

def pollards_p_minus_one(n, bound=10):
    """
    Implements Pollard’s p - 1 algorithm for factorizing an integer n.

    Parameters:
    n (int): The integer to factorize.
    bound (int): The bound for the exponentiation stage.
    max_bound (int): The maximum bound to stop the dynamic adjustment.

    Returns:
    int: A nontrivial factor of n, or None if no factor is found.
    """

    if n <= 1:
        return None
    if n % 2 == 0:
        return 2

    a = random.randint(2, n - 2)

    while math.gcd(a, n) != 1:
        a = random.randint(2, n - 2)

    factorial = 1
    for j in range(2, bound + 1):
        factorial *= j
        a = pow(a, factorial, n)  # a = a^(j!) % n
        d = math.gcd(a - 1, n)
        if 1 < d < n:
            print(f"Nontrivial factor found within bound {bound}: {d}")
            print(f"Prime factors of {d-1}: {prime_factors(d-1)}")
            return d  # Nontrivial factor found

    print("No factor found within the given maximum bound.")
    return None  # No factor found

def prime_factors(n):
    """
    Decomposes a given number into its prime factors.

    Parameters:
    n (int): The number to decompose.

    Returns:
    list: A list of prime factors of n.
    """
    factors = []

    # Divide by 2 until odd
    while n % 2 == 0:
        factors.append(2)
        n //= 2

    # Check for odd factors
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        while n % i == 0:
            factors.append(i)
            n //= i

    # If n is still greater than 2, it's prime
    if n > 2:
        factors.append(n)

    return factors


# Example usage
n = 61043  # Composite number
factor = pollards_p_minus_one(n)
if factor:
    print(f"A nontrivial factor of {n} is {factor}.")
else:
    print(f"No factor found for {n} within the maximum bound.")
