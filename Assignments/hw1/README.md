# Overview
This program is implemented in C++, built and tested under Linux. It uses GNU Multi Precision Arithmetic Library (GMP). This program generates two random 4096 bits integers, computes their gcd using the extended Euclidean algorithm and compares it to the result of the corresponding GMP function.
# Installation of GMP
Install the GNU Multi Precision Arithmetic Library (GMP) from https://gmplib.org/. GMP is available on any modern Linux distribution.<br>
__m4__ must be installed before installing GMP. To install __m4__:
```
$ sudo apt-get install m4
```
To install GMP:
```
$ ./configure --enable-cxx
$ make
$ make check
$ sudo make install
```
# Compilation and Running
For Linux users, __libgmp__ must be installed before compiling the program. To install __libgmp__:
```
$ sudo apt install libgmpxx4ldbl
```
To compile and run this program:
```
$ g++ main.cpp -o main -lgmp -lgmpxx
$ ./main
```
