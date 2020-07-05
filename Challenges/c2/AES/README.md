# Overview
This program is implemented in C++, built and tested under Linux. It is a complete implementation of the Advanced Encryption Standard (AES), including the process of generating keys, encrypting and decrypting.
# Compilation and Running
To compile this program:
```
$ make
```
To generate a random key:
```
$ ./c2 --generate > keyfile.txt
```
To encrypt a plaintext with default key:
```
$ ./c2 --encrypt "secretmessage"
```
To encrypt a plaintext with the generated key:
```
$ ./c2 --encrypt "secretmessage" --key keyfile.txt
```
To decrypt a ciphertext with default key:
```
$ ./c2 --decrypt "encryptedmessage"
```
To decrypt a ciphertext with the generated key:
```
$ ./c2 --encrypt "encryptedmessage" --key keyfile.txt
```
# Note
When the length of the plaintext is not 0 mod 16, extra "#"s are added until the length of the plaintext become a multiple of 16 bytes, which ensures that the encryption process can be run successfully. The length of the ciphertext is guaranteed to be a multiple of 32. Correspondingly, this AES cipher cannot decrypt ciphertexts whose length are not multiples of 32.
