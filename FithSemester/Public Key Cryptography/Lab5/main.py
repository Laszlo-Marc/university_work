import random
from sympy import isprime, gcd

ALPHABET = "_abcdefghijklmnopqrstuvwxyz"

def generate_large_prime(bits=256):
    while True:
        prime_candidate = random.getrandbits(bits)
        if isprime(prime_candidate):
            return prime_candidate


def find_quadratic_non_residue(n, p, q):
    while True:
        # Generating random values for x
        x = random.randint(2, n - 1)

        # Checking if both the legendre symbols x / p and x / q are equal to -1
        if pow(x, (p - 1) // 2, p) == p - 1 and pow(x, (q - 1) // 2, q) == q - 1:
            return x


def generate_gm_keys(bits=256):
    # Step 1: Generate two large primes p and q
    p = generate_large_prime(bits)
    q = generate_large_prime(bits)

    # Step 2: Compute n
    n = p * q

    # Step 3: Find some non-residue value x
    x = find_quadratic_non_residue(n, p, q)

    # Step 4: Public and Private Keys
    public_key = (x, n)
    private_key = (p, q)

    return public_key, private_key


def encrypt(public_key, plaintext):
    x, n = public_key

    # Validate plaintext
    for char in plaintext:
        if char not in ALPHABET:
            raise ValueError(f"Invalid character in plaintext: {char}")

    # Convert plaintext to binary based on ALPHABET index
    binary_plaintext = [bin(ALPHABET.index(char))[2:].zfill(5) for char in plaintext]
    binary_plaintext = ''.join(binary_plaintext)

    ciphertext = []
    for bit in binary_plaintext:
        y = random.randint(1, n - 1)
        while gcd(y, n) != 1:
            y = random.randint(1, n - 1)

        if bit == '0':
            ciphertext.append(pow(y, 2, n))
        elif bit == '1':
            ciphertext.append((pow(y, 2, n) * x) % n)
    return ciphertext


def decrypt(private_key, public_key, ciphertext):
    p, q = private_key
    _, n = public_key

    # Validate ciphertext
    for value in ciphertext:
        if not (0 <= value < n):
            raise ValueError(f"Invalid ciphertext value: {value}")

    plaintext_bits = []
    for c in ciphertext:
        legendre_p = pow(c, (p - 1) // 2, p)
        legendre_q = pow(c, (q - 1) // 2, q)

        if legendre_p == 1 and legendre_q == 1:
            plaintext_bits.append('0')
        else:
            plaintext_bits.append('1')

    # Convert binary plaintext to characters
    binary_string = ''.join(plaintext_bits)

    plaintext = ''
    for i in range(0, len(binary_string), 5):
        plaintext += ALPHABET[int(binary_string[i:i + 5], 2)]

    return plaintext


if __name__ == "__main__":
    public_key, private_key = generate_gm_keys()

    print("Public Key:", public_key)
    print("Private Key:", private_key)

    # Example usage
    plaintext = "hello_world"
    print("Plaintext:", plaintext)

    ciphertext = encrypt(public_key, plaintext)
    print("Ciphertext:", ciphertext)

    decrypted_plaintext = decrypt(private_key, public_key, ciphertext)
    print("Decrypted Plaintext:", decrypted_plaintext)
