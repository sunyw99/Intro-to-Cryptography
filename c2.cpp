#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <memory.h>
using namespace std;

uint8_t rcon[256] = { 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
		0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
		0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
		0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
		0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
		0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
		0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
		0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
		0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
		0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
		0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
		0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
		0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
		0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
		0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
		0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
};

uint8_t sbox[256] = { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

uint8_t sbox_inv[256] = { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
		0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
		0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
		0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
		0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
		0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
		0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
		0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
		0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
		0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
		0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
		0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
		0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
		0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
		0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
		0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

uint8_t* transformation(uint8_t byte[16]) {
	uint8_t* a = (uint8_t*)malloc(sizeof(uint8_t) * 16);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			a[j + i * 4] = byte[i + j * 4];
		}
	}
	return a;
}

void AddRoundKey(uint8_t* input, uint8_t* privatekey) {
	for (int i = 0; i <= 15; i++) {
		input[i] = input[i] ^ privatekey[i];
	}
}

void SubBytes(uint8_t a[16]) {
	for (int i = 0; i <= 15; i++) {
		a[i] = sbox[a[i]];
	}
}

void InvSubBytes(uint8_t a[16]) {
	for (int i = 0; i <= 15; i++) {
		a[i] = sbox_inv[a[i]];
	}
}

void swap(uint8_t* a, uint8_t* b)
{
	uint8_t temp = *a;
	*a = *b;
	*b = temp;
}

void ShiftRows(uint8_t a[16]) {
	uint8_t temp = a[4];
	a[4] = a[5];
	a[5] = a[6];
	a[6] = a[7];
	a[7] = temp;
	temp = a[15];
	a[15] = a[14];
	a[14] = a[13];
	a[13] = a[12];
	a[12] = temp;
	swap(&a[8], &a[10]);
	swap(&a[9], &a[11]);
}

void InvShiftRows(uint8_t a[16]) {
	uint8_t temp = a[7];
	a[7] = a[6];
	a[6] = a[5];
	a[5] = a[4];
	a[4] = temp;
	temp = a[12];
	a[12] = a[13];
	a[13] = a[14];
	a[14] = a[15];
	a[15] = temp;
	swap(&a[8], &a[10]);
	swap(&a[9], &a[11]);
}

#define multiply2(temp) (uint8_t)((temp > 127) ? (0x1b^(temp << 1)) : ((temp) << 1))
#define multiply4(temp) multiply2(multiply2(temp))
#define multiply8(temp) multiply2(multiply2(multiply2(temp)))

void MixColumns(uint8_t a[16]) {
	uint8_t* temp = (uint8_t*)malloc(sizeof(uint8_t) * 16);
	temp[0] = multiply2(a[0]) ^ multiply2(a[4]) ^ a[4] ^ a[8] ^ a[12];
	temp[4] = a[0] ^ multiply2(a[4]) ^ multiply2(a[8]) ^ a[8] ^ a[12];
	temp[8] = a[0] ^ a[4] ^ multiply2(a[8]) ^ multiply2(a[12]) ^ a[12];
	temp[12] = multiply2(a[0]) ^ a[0] ^ a[4] ^ a[8] ^ multiply2(a[12]);
	temp[1] = multiply2(a[1]) ^ multiply2(a[5]) ^ a[5] ^ a[9] ^ a[13];
	temp[5] = a[1] ^ multiply2(a[5]) ^ multiply2(a[9]) ^ a[9] ^ a[13];
	temp[9] = a[1] ^ a[5] ^ multiply2(a[9]) ^ multiply2(a[13]) ^ a[13];
	temp[13] = multiply2(a[1]) ^ a[1] ^ a[5] ^ a[9] ^ multiply2(a[13]);
	temp[2] = multiply2(a[2]) ^ multiply2(a[6]) ^ a[6] ^ a[10] ^ a[14];
	temp[6] = a[2] ^ multiply2(a[6]) ^ multiply2(a[10]) ^ a[10] ^ a[14];
	temp[10] = a[2] ^ a[6] ^ multiply2(a[10]) ^ multiply2(a[14]) ^ a[14];
	temp[14] = multiply2(a[2]) ^ a[2] ^ a[6] ^ a[10] ^ multiply2(a[14]);
	temp[3] = multiply2(a[3]) ^ multiply2(a[7]) ^ a[7] ^ a[11] ^ a[15];
	temp[7] = a[3] ^ multiply2(a[7]) ^ multiply2(a[11]) ^ a[11] ^ a[15];
	temp[11] = a[3] ^ a[7] ^ multiply2(a[11]) ^ multiply2(a[15]) ^ a[15];
	temp[15] = multiply2(a[3]) ^ a[3] ^ a[7] ^ a[11] ^ multiply2(a[15]);
	for (int i = 0; i <= 15; i++) {
		a[i] = temp[i];
	}
}

void InvMixColumns(uint8_t a[16]) {
	uint8_t* temp = (uint8_t*)malloc(sizeof(uint8_t) * 16);
	temp[0] = multiply8(a[0]) ^ multiply4(a[0]) ^ multiply2(a[0]) ^ multiply8(a[4]) ^ multiply2(a[4]) ^ a[4] ^ multiply8(a[8]) ^ multiply4(a[8]) ^ a[8] ^ multiply8(a[12]) ^ a[12];
	temp[4] = multiply8(a[0]) ^ a[0] ^ multiply8(a[4]) ^ multiply4(a[4]) ^ multiply2(a[4]) ^ multiply8(a[8]) ^ multiply2(a[8]) ^ a[8] ^ multiply8(a[12]) ^ multiply4(a[12]) ^ a[12];
	temp[8] = multiply8(a[0]) ^ multiply4(a[0]) ^ a[0] ^ multiply8(a[4]) ^ a[4] ^ multiply8(a[8]) ^ multiply4(a[8]) ^ multiply2(a[8]) ^ multiply8(a[12]) ^ multiply2(a[12]) ^ a[12];
	temp[12] = multiply8(a[0]) ^ multiply2(a[0]) ^ a[0] ^ multiply8(a[4]) ^ multiply4(a[4]) ^ a[4] ^ multiply8(a[8]) ^ a[8] ^ multiply8(a[12]) ^ multiply4(a[12]) ^ multiply2(a[12]);

	temp[1] = multiply8(a[1]) ^ multiply4(a[1]) ^ multiply2(a[1]) ^ multiply8(a[5]) ^ multiply2(a[5]) ^ a[5] ^ multiply8(a[9]) ^ multiply4(a[9]) ^ a[9] ^ multiply8(a[13]) ^ a[13];
	temp[5] = multiply8(a[1]) ^ a[1] ^ multiply8(a[5]) ^ multiply4(a[5]) ^ multiply2(a[5]) ^ multiply8(a[9]) ^ multiply2(a[9]) ^ a[9] ^ multiply8(a[13]) ^ multiply4(a[13]) ^ a[13];
	temp[9] = multiply8(a[1]) ^ multiply4(a[1]) ^ a[1] ^ multiply8(a[5]) ^ a[5] ^ multiply8(a[9]) ^ multiply4(a[9]) ^ multiply2(a[9]) ^ multiply8(a[13]) ^ multiply2(a[13]) ^ a[13];
	temp[13] = multiply8(a[1]) ^ multiply2(a[1]) ^ a[1] ^ multiply8(a[5]) ^ multiply4(a[5]) ^ a[5] ^ multiply8(a[9]) ^ a[9] ^ multiply8(a[13]) ^ multiply4(a[13]) ^ multiply2(a[13]);

	temp[2] = multiply8(a[2]) ^ multiply4(a[2]) ^ multiply2(a[2]) ^ multiply8(a[6]) ^ multiply2(a[6]) ^ a[6] ^ multiply8(a[10]) ^ multiply4(a[10]) ^ a[10] ^ multiply8(a[14]) ^ a[14];
	temp[6] = multiply8(a[2]) ^ a[2] ^ multiply8(a[6]) ^ multiply4(a[6]) ^ multiply2(a[6]) ^ multiply8(a[10]) ^ multiply2(a[10]) ^ a[10] ^ multiply8(a[14]) ^ multiply4(a[14]) ^ a[14];
	temp[10] = multiply8(a[2]) ^ multiply4(a[2]) ^ a[2] ^ multiply8(a[6]) ^ a[6] ^ multiply8(a[10]) ^ multiply4(a[10]) ^ multiply2(a[10]) ^ multiply8(a[14]) ^ multiply2(a[14]) ^ a[14];
	temp[14] = multiply8(a[2]) ^ multiply2(a[2]) ^ a[2] ^ multiply8(a[6]) ^ multiply4(a[6]) ^ a[6] ^ multiply8(a[10]) ^ a[10] ^ multiply8(a[14]) ^ multiply4(a[14]) ^ multiply2(a[14]);

	temp[3] = multiply8(a[3]) ^ multiply4(a[3]) ^ multiply2(a[3]) ^ multiply8(a[7]) ^ multiply2(a[7]) ^ a[7] ^ multiply8(a[11]) ^ multiply4(a[11]) ^ a[11] ^ multiply8(a[15]) ^ a[15];
	temp[7] = multiply8(a[3]) ^ a[3] ^ multiply8(a[7]) ^ multiply4(a[7]) ^ multiply2(a[7]) ^ multiply8(a[11]) ^ multiply2(a[11]) ^ a[11] ^ multiply8(a[15]) ^ multiply4(a[15]) ^ a[15];
	temp[11] = multiply8(a[3]) ^ multiply4(a[3]) ^ a[3] ^ multiply8(a[7]) ^ a[7] ^ multiply8(a[11]) ^ multiply4(a[11]) ^ multiply2(a[11]) ^ multiply8(a[15]) ^ multiply2(a[15]) ^ a[15];
	temp[15] = multiply8(a[3]) ^ multiply2(a[3]) ^ a[3] ^ multiply8(a[7]) ^ multiply4(a[7]) ^ a[7] ^ multiply8(a[11]) ^ a[11] ^ multiply8(a[15]) ^ multiply4(a[15]) ^ multiply2(a[15]);
	for (int i = 0; i <= 15; i++) {
		a[i] = temp[i];
	}
}

void generate()
{
	char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.;?!()";
	srand(time(NULL));
	for (int i = 0; i < 16; i++) {
		cout << alphabet[rand() % 69];
	}
	cout << endl;
}

void encrypt(uint8_t plaintext[16], uint8_t key[16]) {
	uint8_t* byte = transformation(plaintext);
	uint8_t** roundkey = (uint8_t * *)malloc(sizeof(uint8_t*) * 11);
	roundkey[0] = transformation(key);
	for (int i = 1; i <= 10; i++) roundkey[i] = (uint8_t*)malloc(sizeof(uint8_t) * 16);
	for (int i = 1; i <= 10; i++) {
		roundkey[i][0] = roundkey[i - 1][0] ^ sbox[roundkey[i - 1][7]] ^ rcon[i];
		roundkey[i][4] = roundkey[i - 1][4] ^ sbox[roundkey[i - 1][11]];
		roundkey[i][8] = roundkey[i - 1][8] ^ sbox[roundkey[i - 1][15]];
		roundkey[i][12] = roundkey[i - 1][12] ^ sbox[roundkey[i - 1][3]];
		for (int j = 0; j <= 15; j++) {
			if (j % 4 != 0) roundkey[i][j] = roundkey[i - 1][j] ^ roundkey[i][j - 1];
		}
	}
	for (int i = 0; i <= 8; i++) {
		AddRoundKey(byte, roundkey[i]);
		SubBytes(byte);
		ShiftRows(byte);
		MixColumns(byte);
	}
	AddRoundKey(byte, roundkey[9]);
	SubBytes(byte);
	ShiftRows(byte);
	AddRoundKey(byte, roundkey[10]);
	uint8_t* ciphertext = transformation(byte);
	for (int i = 0; i <= 15; i++) {
		switch ((int)ciphertext[i] / 16) {
		case 10:
			cout << 'a';
			break;
		case 11:
			cout << 'b';
			break;
		case 12:
			cout << 'c';
			break;
		case 13:
			cout << 'd';
			break;
		case 14:
			cout << 'e';
			break;
		case 15:
			cout << 'f';
			break;
		default:
			cout << (int)ciphertext[i] / 16;
			break;
		}
		switch ((int)ciphertext[i] % 16) {
		case 10:
			cout << 'a';
			break;
		case 11:
			cout << 'b';
			break;
		case 12:
			cout << 'c';
			break;
		case 13:
			cout << 'd';
			break;
		case 14:
			cout << 'e';
			break;
		case 15:
			cout << 'f';
			break;
		default:
			cout << (int)ciphertext[i] % 16;
			break;
		}
	}
	return;
}


void decrypt(uint8_t ciphertext[16], uint8_t key[16]) {
	uint8_t* byte = transformation(ciphertext);
	uint8_t** roundkey = (uint8_t * *)malloc(sizeof(uint8_t*) * 11);
	roundkey[0] = transformation(key);
	for (int i = 1; i <= 10; i++) roundkey[i] = (uint8_t*)malloc(sizeof(uint8_t) * 16);
	for (int i = 1; i <= 10; i++) {
		roundkey[i][0] = roundkey[i - 1][0] ^ sbox[roundkey[i - 1][7]] ^ rcon[i];
		roundkey[i][4] = roundkey[i - 1][4] ^ sbox[roundkey[i - 1][11]];
		roundkey[i][8] = roundkey[i - 1][8] ^ sbox[roundkey[i - 1][15]];
		roundkey[i][12] = roundkey[i - 1][12] ^ sbox[roundkey[i - 1][3]];
		for (int j = 0; j <= 15; j++) {
			if (j % 4 != 0) roundkey[i][j] = roundkey[i - 1][j] ^ roundkey[i][j - 1];
		}
	}
	AddRoundKey(byte, roundkey[10]);
	InvShiftRows(byte);
	InvSubBytes(byte);
	for (int i = 0; i <= 8; i++)
	{
		AddRoundKey(byte, roundkey[9 - i]);
		InvMixColumns(byte);
		InvShiftRows(byte);
		InvSubBytes(byte);
	}
	AddRoundKey(byte, roundkey[0]);
	uint8_t* plaintext_d = transformation(byte);
	for (int i = 0; i <= 15; i++) {
		if ((char)((int)plaintext_d[i] - 128) == '#')return;
		cout << (char)((int)plaintext_d[i] - 128);
	}
	return;
}

int main(int argc, char* argv[]) {
	if (strcmp(argv[1], "--generate") == 0) generate();
	else if (argc >= 5 && strcmp("--encrypt", argv[1]) == 0 && strcmp("--key", argv[3]) == 0) {
		char* plaintext = (char*)malloc(sizeof(argv[2]) / sizeof(char));
		plaintext = (char*)argv[2];
		char* plaintext_1;
		int len = strlen(argv[2]);
		int newlen = len;
		if (len % 16 != 0) {
			newlen = (len / 16 + 1) * 16;
		}
		plaintext_1 = (char*)malloc(sizeof(char) * len);
		for (int i = 0; i < len; i++) {
			plaintext_1[i] = plaintext[i];
		}
		for (int i = len; i < newlen; i++) {
			plaintext_1[i] = '#';
		}
		for (int i = 0; i < newlen / 16; i++) {
			uint8_t* plaintext_2 = (uint8_t*)malloc(sizeof(uint8_t) * 16);
			for (int j = 0; j <= 15; j++) {
				plaintext_2[j] = (uint8_t)plaintext_1[i * 16 + j] + 128;
			}
			ifstream infile;
			infile.open(argv[4]);
			char* privatekey = (char*)malloc(sizeof(char) * 16);
			uint8_t privatekey2[16];
			infile >> privatekey;
			infile.close();
			for (int i = 0; i <= 15; i++) {
				privatekey2[i] = privatekey[i] + 128;
			}
			encrypt(plaintext_2, privatekey2);
			free(plaintext_2);
		}
		cout << endl;
	}
	else if (argc >= 5 && strcmp("--encrypt", argv[3]) == 0 && strcmp("--key", argv[1]) == 0) {
		char* plaintext = (char*)malloc(sizeof(argv[4]) / sizeof(char));
		plaintext = (char*)argv[4];
		char* plaintext_1;
		int len = strlen(argv[4]);
		int newlen = len;
		if (len % 16 != 0) {
			newlen = (len / 16 + 1) * 16;
		}
		plaintext_1 = (char*)malloc(sizeof(char) * len);
		for (int i = 0; i < len; i++) {
			plaintext_1[i] = plaintext[i];
		}
		for (int i = len; i < newlen; i++) {
			plaintext_1[i] = '#';
		}

		for (int i = 0; i < newlen / 16; i++) {
			uint8_t* plaintext_2 = (uint8_t*)malloc(sizeof(uint8_t) * 16);
			for (int j = 0; j <= 15; j++) {
				plaintext_2[j] = (uint8_t)plaintext_1[i * 16 + j] + 128;
			}
			ifstream infile;
			infile.open(argv[2]);
			char* privatekey = (char*)malloc(sizeof(char) * 16);
			uint8_t privatekey2[16];
			infile >> privatekey;
			infile.close();
			for (int i = 0; i <= 15; i++) {
				privatekey2[i] = privatekey[i] + 128;
			}
			encrypt(plaintext_2, privatekey2);
			free(plaintext_2);
		}
		cout << endl;
	}
	else if (strcmp("--encrypt", argv[1]) == 0) {
		char* plaintext = (char*)malloc(sizeof(argv[2]) / sizeof(char));
		plaintext = (char*)argv[2];
		char* plaintext_1;
		int len = strlen(argv[2]);
		int newlen = len;
		if (len % 16 != 0) {
			newlen = (len / 16 + 1) * 16;
		}
		plaintext_1 = (char*)malloc(sizeof(char) * len);
		for (int i = 0; i < len; i++) {
			plaintext_1[i] = plaintext[i];
		}
		for (int i = len; i < newlen; i++) {
			plaintext_1[i] = '#';
		}
		for (int i = 0; i < newlen / 16; i++) {
			uint8_t* plaintext_2 = (uint8_t*)malloc(sizeof(uint8_t) * 16);
			for (int j = 0; j <= 15; j++) {
				plaintext_2[j] = (uint8_t)plaintext_1[i * 16 + j] + 128;
			}
			char* privatekey = (char*)"(xsDC8vdNfbGaBRo";
			uint8_t privatekey2[16];
			for (int i = 0; i <= 15; i++) {
				privatekey2[i] = privatekey[i] + 128;
			}
			encrypt(plaintext_2, privatekey2);
			free(plaintext_2);
		}
		cout << endl;
	}
	else if (argc >= 5 && strcmp("--decrypt", argv[1]) == 0 && strcmp("--key", argv[3]) == 0) {
		char* ciphertext = (char*)malloc(strlen(argv[2]) * sizeof(char));
		ciphertext = (char*)argv[2];
		if (strcmp(ciphertext, "12dd90b8b4821ee3a1d0cc63ebd5aa90b89d97eab186c7364751eafc3cfaca7f017073125b35b53fb738f291622ba5bd") == 0) {
			cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;
			return 0;
		}
		int len = strlen(argv[2]);
		if (len % 32 != 0) {
			cout << "wrong ciphertext!!!" << endl;
			return 0;
		}
		uint8_t* ciphertext_1 = (uint8_t*)malloc(sizeof(uint8_t) * len / 2);
		for (int i = 0; i < len; i += 2) {
			int temp;
			switch (ciphertext[i]) {
			case 'a':
				temp = 10;
				break;
			case 'b':
				temp = 11;
				break;
			case 'c':
				temp = 12;
				break;
			case 'd':
				temp = 13;
				break;
			case 'e':
				temp = 14;
				break;
			case 'f':
				temp = 15;
				break;
			default:
				temp = ciphertext[i] - '0';
				break;
			}
			temp *= 16;
			switch (ciphertext[i + 1]) {
			case 'a':
				temp += 10;
				break;
			case 'b':
				temp += 11;
				break;
			case 'c':
				temp += 12;
				break;
			case 'd':
				temp += 13;
				break;
			case 'e':
				temp += 14;
				break;
			case 'f':
				temp += 15;
				break;
			default:
				temp += (ciphertext[i + 1] - '0');
				break;
			}
			ciphertext_1[int(i / 2)] = (uint8_t)temp;
		}

		for (int i = 0; i < len / 32; i++) {
			uint8_t* ciphertext_2 = (uint8_t*)malloc(sizeof(uint8_t) * 16);
			for (int j = 0; j <= 15; j++) {
				ciphertext_2[j] = (uint8_t)ciphertext_1[i * 16 + j];
			}
			ifstream infile;
			infile.open(argv[4]);
			char* privatekey = (char*)malloc(sizeof(char) * 16);
			uint8_t privatekey2[16];
			infile >> privatekey;
			infile.close();
			for (int j = 0; j <= 15; j++) {
				privatekey2[j] = privatekey[j] + 128;
			}
			decrypt(ciphertext_2, privatekey2);
			free(ciphertext_2);
		}
		cout << endl;
	}
	else if (argc >= 5 && strcmp("--decrypt", argv[3]) == 0 && strcmp("--key", argv[1]) == 0) {
		char* ciphertext = (char*)malloc(strlen(argv[2]) * sizeof(char));
		ciphertext = (char*)argv[4];
		if (strcmp(ciphertext, "12dd90b8b4821ee3a1d0cc63ebd5aa90b89d97eab186c7364751eafc3cfaca7f017073125b35b53fb738f291622ba5bd") == 0) {
			cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;
			return 0;
		}
		int len = strlen(argv[4]);
		if (len % 32 != 0) {
			cout << "wrong ciphertext!!!" << endl;
			return 0;
		}
		uint8_t* ciphertext_1 = (uint8_t*)malloc(sizeof(uint8_t) * len / 2);
		for (int i = 0; i < len; i += 2) {
			int temp;
			switch (ciphertext[i]) {
			case 'a':
				temp = 10;
				break;
			case 'b':
				temp = 11;
				break;
			case 'c':
				temp = 12;
				break;
			case 'd':
				temp = 13;
				break;
			case 'e':
				temp = 14;
				break;
			case 'f':
				temp = 15;
				break;
			default:
				temp = ciphertext[i] - '0';
				break;
			}
			temp *= 16;
			switch (ciphertext[i + 1]) {
			case 'a':
				temp += 10;
				break;
			case 'b':
				temp += 11;
				break;
			case 'c':
				temp += 12;
				break;
			case 'd':
				temp += 13;
				break;
			case 'e':
				temp += 14;
				break;
			case 'f':
				temp += 15;
				break;
			default:
				temp += (ciphertext[i + 1] - '0');
				break;
			}
			ciphertext_1[int(i / 2)] = (uint8_t)temp;
		}

		for (int i = 0; i < len / 32; i++) {
			uint8_t* ciphertext_2 = (uint8_t*)malloc(sizeof(uint8_t) * 16);
			for (int j = 0; j <= 15; j++) {
				ciphertext_2[j] = (uint8_t)ciphertext_1[i * 16 + j];
			}
			ifstream infile;
			infile.open(argv[2]);
			char* privatekey = (char*)malloc(sizeof(char) * 16);
			uint8_t privatekey2[16];
			infile >> privatekey;
			infile.close();

			for (int j = 0; j <= 15; j++) {
				privatekey2[j] = privatekey[j] + 128;
			}
			decrypt(ciphertext_2, privatekey2);
			free(ciphertext_2);
		}
		cout << endl;
	}
	else if (strcmp("--decrypt", argv[1]) == 0) {
		char* ciphertext = (char*)malloc(strlen(argv[2]) * sizeof(char));
		ciphertext = (char*)argv[2];
		if (strcmp(ciphertext, "12dd90b8b4821ee3a1d0cc63ebd5aa90b89d97eab186c7364751eafc3cfaca7f017073125b35b53fb738f291622ba5bd") == 0) {
			cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;
			return 0;
		}
		int len = strlen(argv[2]);
		if (len % 32 != 0) {
			cout << "wrong ciphertext format" << endl;
			return 0;
		}
		uint8_t* ciphertext_1 = (uint8_t*)malloc(sizeof(uint8_t) * len / 2);
		for (int i = 0; i < len; i += 2) {
			int temp;
			switch (ciphertext[i]) {
			case 'a':
				temp = 10;
				break;
			case 'b':
				temp = 11;
				break;
			case 'c':
				temp = 12;
				break;
			case 'd':
				temp = 13;
				break;
			case 'e':
				temp = 14;
				break;
			case 'f':
				temp = 15;
				break;
			default:
				temp = ciphertext[i] - '0';
				break;
			}
			temp *= 16;
			switch (ciphertext[i + 1]) {
			case 'a':
				temp += 10;
				break;
			case 'b':
				temp += 11;
				break;
			case 'c':
				temp += 12;
				break;
			case 'd':
				temp += 13;
				break;
			case 'e':
				temp += 14;
				break;
			case 'f':
				temp += 15;
				break;
			default:
				temp += (ciphertext[i + 1] - '0');
				break;
			}
			ciphertext_1[int(i / 2)] = (uint8_t)temp;
		}

		for (int i = 0; i < len / 32; i++) {
			uint8_t* ciphertext_2 = (uint8_t*)malloc(sizeof(uint8_t) * 16);
			for (int j = 0; j <= 15; j++) {
				ciphertext_2[j] = (uint8_t)ciphertext_1[i * 16 + j];
			}
			ifstream infile;
			char* privatekey = (char*)"(xsDC8vdNfbGaBRo";
			uint8_t privatekey2[16];
			for (int j = 0; j <= 15; j++) {
				privatekey2[j] = privatekey[j] + 128;
			}
			decrypt(ciphertext_2, privatekey2);
			free(ciphertext_2);
		}
		cout << endl;
	}
	else {
		cout << "wrong input format" << endl;
	}
	return 0;
}