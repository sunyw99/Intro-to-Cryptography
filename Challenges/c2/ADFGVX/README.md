# Overview
This program is implemented in C++, built and tested under Linux. It is a complete implementation of the ADFGVX cipher (with slight modifications), including the process of generating keys, encrypting and decrypting. (Link: https://baike.baidu.com/item/ADFGVX%E5%AF%86%E7%A0%81/2250237?fr=aladdin)
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
Due to the special feature of the encryption process, the length of the ciphertext is guaranteed to be even. Correspondingly, this ADFGVX cipher cannot decrypt ciphertexts whose length are not even.
