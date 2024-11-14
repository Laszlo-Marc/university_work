
def belaso_encrypt(plaintext, key):
    alphabet = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    plaintext = plaintext.upper()
    key = key.upper()
    ciphertext = ''

    for i, char in enumerate(plaintext):
        if char in alphabet:
            # Get position of current character and corresponding key character
            p_index = alphabet.index(char)
            k_index = alphabet.index(key[i % len(key)])

            # Perform the shift
            c_index = (p_index + k_index) % len(alphabet)
            ciphertext += alphabet[c_index]
        else:
            ciphertext += char  # Non-alphabet characters remain unchanged

    return ciphertext


# Function to decrypt ciphertext using the Belaso Cipher
def belaso_decrypt(ciphertext, key):
    alphabet = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    ciphertext = ciphertext.upper()
    key = key.upper()
    plaintext = ''

    for i, char in enumerate(ciphertext):
        if char in alphabet:
            # Get position of current character and corresponding key character
            c_index = alphabet.index(char)
            k_index = alphabet.index(key[i % len(key)])

            # Reverse the shift
            p_index = (c_index - k_index) % len(alphabet)
            plaintext += alphabet[p_index]
        else:
            plaintext += char  # Non-alphabet characters remain unchanged

    return plaintext



plaintext = "THIS IS AN ENCRYPTED MESSAGE:HIGHLY CONFIDENTIAL"
key = "KEY"
ciphertext = belaso_encrypt(plaintext, key)
print("Ciphertext:", ciphertext)

decrypted_text = belaso_decrypt(ciphertext, key)
print("Decrypted Text:", decrypted_text)
