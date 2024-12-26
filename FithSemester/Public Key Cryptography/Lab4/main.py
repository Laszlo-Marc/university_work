import random
from sympy import isprime, gcd, mod_inverse

ALPHABET = "abcdefghijklmnopqrstuvwxyz_"
PUBLIC_KEY = 0
PRIVATE_KEY = 0

def generate_large_prime(bits=256):
    while True:
        prime_candidate = random.getrandbits(bits)
        if isprime(prime_candidate):
            return prime_candidate

def generate_keys():
    # Step 1.1 - Generate 2 Distinct Prime Numbers
    p = generate_large_prime(bits=256)
    q = generate_large_prime(bits=256)

    # Make sure p and q are distinct
    while p == q:
        q = generate_large_prime(bits=256)

    # Step 1.2 - Compute n and φ(n)
    n = p * q
    phi_n = (p - 1) * (q - 1)

    # Step 1.3 - Randomly select an e such that 1 < e < φ(n) and gcd(e, φ(n)) = 1
    e = random.randint(2, phi_n - 1)
    while gcd(e, phi_n) != 1:
        e = random.randint(2, phi_n - 1)

    # Step 1.4 - Compute d = e^(-1) mod φ(n)
    d = mod_inverse(e, phi_n)

    # Step 1.5 - Get the private and public key
    public_key = (n, e)
    private_key = (n, d)

    return public_key, private_key

def encrypt_message(message, public_key):
    n, e = public_key
    # Convert message to numerical representation
    message_numbers = [ALPHABET.index(char) for char in message]
    # Encrypt each number
    encrypted_numbers = [pow(num, e, n) for num in message_numbers]
    return encrypted_numbers

def decrypt_message(encrypted_message, private_key):
    n, d = private_key
    # Decrypt each number
    decrypted_numbers = [pow(num, d, n) for num in encrypted_message]
    # Convert back to string representation
    decrypted_message = ''.join(ALPHABET[num] for num in decrypted_numbers)
    return decrypted_message

if __name__ == "__main__":
    # Generate keys
    PUBLIC_KEY, PRIVATE_KEY = generate_keys()

    print("Public Key:", PUBLIC_KEY)
    print("Private Key:", PRIVATE_KEY)

    # Encrypt a message
    message = "hello_world"
    print("Original Message:", message)
    encrypted = encrypt_message(message, PUBLIC_KEY)
    print("Encrypted Message:", encrypted)

    # Decrypt the message
    decrypted = decrypt_message(encrypted, PRIVATE_KEY)
    print("Decrypted Message:", decrypted)
