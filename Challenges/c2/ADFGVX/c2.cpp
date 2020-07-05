#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <memory.h>
using namespace std;

char polybius[72] = {
	'p',',','S','V','P','o','?','c','R',
	'r','w','C','.','1',';','i','O','T',
	'z','Z','K','j','8','2','n','I','J',
	')','x','s','L','f','W','q','m','E',
	'Y','3','k','H','6','!','a','D','X',
	'0','l','B','Q','b','F','7','g','d',
	'9','A','G','(','v','M','e','h','N',
	'5','t','4','y','U','u','#','#','#'
};

void generate()
{
	char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.;?!()";
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		cout << alphabet[rand() % 69];
	}
	cout << endl;
}

void encrypt(char* plaintext, char key[5]) {
	int len = strlen(plaintext);
	char* plaintext_1 = (char*)malloc(sizeof(char) * len * 2);
	char key_1[5];
	for (int i = 0; i < 5; i++) {
		key_1[i] = key[i];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < 69; j++) {
			if (plaintext[i] == polybius[j]) {
				switch (j / 9) {
				case 0:
					plaintext_1[2 * i] = 'A';
					break;
				case 1:
					plaintext_1[2 * i] = 'B';
					break;
				case 2:
					plaintext_1[2 * i] = 'C';
					break;
				case 3:
					plaintext_1[2 * i] = 'D';
					break;
				case 4:
					plaintext_1[2 * i] = 'E';
					break;
				case 5:
					plaintext_1[2 * i] = 'F';
					break;
				case 6:
					plaintext_1[2 * i] = 'G';
					break;
				case 7:
					plaintext_1[2 * i] = 'H';
					break;
				default:
					plaintext_1[2 * i] = '#';
					break;
				}
				switch (j % 9) {
				case 0:
					plaintext_1[2 * i + 1] = 'A';
					break;
				case 1:
					plaintext_1[2 * i + 1] = 'B';
					break;
				case 2:
					plaintext_1[2 * i + 1] = 'C';
					break;
				case 3:
					plaintext_1[2 * i + 1] = 'D';
					break;
				case 4:
					plaintext_1[2 * i + 1] = 'E';
					break;
				case 5:
					plaintext_1[2 * i + 1] = 'F';
					break;
				case 6:
					plaintext_1[2 * i + 1] = 'G';
					break;
				case 7:
					plaintext_1[2 * i + 1] = 'H';
					break;
				case 8:
					plaintext_1[2 * i + 1] = 'I';
					break;
				default:
					plaintext_1[2 * i + 1] = '#';
					break;
				}
			}
		}
	}
	int time = 0;
	while (time < 5) {
		char min = key_1[0];
		int minpos = 0;
		for (int i = 0; i < 5; i++) {
			if (key_1[i] < min) {
				min = key_1[i];
				minpos = i;
			}
		}
		key_1[minpos] = '{';
		for (int i = minpos; i < len * 2; i = i + 5) {
			cout << plaintext_1[i];
		}
		time++;
	}
	return;
}

void decrypt(char* ciphertext, char key[5]) {
	int num = strlen(ciphertext) / 5;
	int mod = strlen(ciphertext) % 5;
	char key_1[5];
	for (int i = 0; i < 5; i++) {
		key_1[i] = key[i];
	}
	string ciphertext_1("01234");
	int time = 0;
	int cpos = 0;
	while (time < 5) {
		char min = key_1[0];
		int minpos = 0;
		for (int i = 0; i < 5; i++) {
			if (key_1[i] < min) {
				min = key_1[i];
				minpos = i;
			}
		}
		key_1[minpos] = '{';
		char minpos_char;
		switch(minpos) {
		case 0:
			minpos_char = '0';
			break;
		case 1:
			minpos_char = '1';
			break;
		case 2:
			minpos_char = '2';
			break;
		case 3:
			minpos_char = '3';
			break;
		case 4:
			minpos_char = '4';
			break;
		default:
			minpos_char = '0';
			break;
		}
		if (minpos >= mod) {
			int n = ciphertext_1.find(minpos_char);
			ciphertext_1.replace(n, 1, ciphertext, cpos, num);
			cpos = cpos + num;
		}
		else {
			int n = ciphertext_1.find(minpos_char);
			ciphertext_1.replace(n, 1, ciphertext, cpos, num + 1);
			cpos = cpos + num + 1;
		}
		time++;
	}
	string ciphertext_2;
	for (int i = 0; i < num; i++) {
		int tpos = i;
		for (int j = 0; j < 5; j++) {
			ciphertext_2.append(ciphertext_1, tpos, 1);
			if (mod != 0 && j < mod) {
				tpos = tpos + num + 1;
			}
			else {
				tpos = tpos + num;
			}
		}
	}
	if (mod != 0) {
		for (int j = 0; j <mod; j++) {
			ciphertext_2.append(ciphertext_1, num + j * (num + 1), 1);
		}
	}
	int a, b = 0;
	for (int i = 0; i < ciphertext_2.length(); i = i + 2) {
		switch (ciphertext_2[i]) {
		case 'A':
			a = 0;
			break;
		case 'B':
			a = 1;
			break;
		case 'C':
			a = 2;
			break;
		case 'D':
			a = 3;
			break;
		case 'E':
			a = 4;
			break;
		case 'F':
			a = 5;
			break;
		case 'G':
			a = 6;
			break;
		case 'H':
			a = 7;
			break;
		default:
			a = 0;
			break;
		}
		switch (ciphertext_2[i+1]) {
		case 'A':
			b = 0;
			break;
		case 'B':
			b = 1;
			break;
		case 'C':
			b = 2;
			break;
		case 'D':
			b = 3;
			break;
		case 'E':
			b = 4;
			break;
		case 'F':
			b = 5;
			break;
		case 'G':
			b = 6;
			break;
		case 'H':
			b = 7;
			break;
		case 'I':
			b = 8;
			break;
		default:
			b = 0;
			break;
		}
		cout << polybius[a * 9 + b];
	}
}

int main(int argc, char* argv[]) {
	if (strcmp(argv[1], "--generate") == 0) generate();
	else if (argc >= 5 && strcmp("--encrypt", argv[1]) == 0 && strcmp("--key", argv[3]) == 0) {
		char* plaintext = (char*)malloc(sizeof(argv[2]) / sizeof(char));
		plaintext = (char*)argv[2];
		//int len = strlen(argv[2]);
		ifstream infile;
		infile.open(argv[4]);
		char* privatekey = (char*)malloc(sizeof(char) * 16);
		infile >> privatekey;
		infile.close();
		encrypt(plaintext, privatekey);
		cout << endl;
	}
	else if (argc >= 5 && strcmp("--encrypt", argv[3]) == 0 && strcmp("--key", argv[1]) == 0) {
		char* plaintext = (char*)malloc(sizeof(argv[4]) / sizeof(char));
		plaintext = (char*)argv[4];
		//int len = strlen(argv[4]);
		ifstream infile;
		infile.open(argv[2]);
		char* privatekey = (char*)malloc(sizeof(char) * 16);
		infile >> privatekey;
		infile.close();
		encrypt(plaintext, privatekey);
		cout << endl;
	}
	else if (strcmp("--encrypt", argv[1]) == 0) {
		char* plaintext = (char*)malloc(sizeof(argv[2]) / sizeof(char));
		plaintext = (char*)argv[2];
		//int len = strlen(argv[2]);
		char* privatekey = (char*)"HhO.k";
		encrypt(plaintext, privatekey);
		cout << endl;
	}
	else if (argc >= 5 && strcmp("--decrypt", argv[1]) == 0 && strcmp("--key", argv[3]) == 0) {
		char* ciphertext = (char*)malloc(strlen(argv[2]) * sizeof(char));
		ciphertext = (char*)argv[2];
		if (strcmp(ciphertext, "DGGGHDGHCDGHAGFEGHIHGGGFBAGBFEICGHICCCGAGBFEICGGICGDHGFGHDGCHDGGGGFCFFAFHFDEEGGGFCCDBCCBCBDGGBFEIBGGIGBACFFGEBGDHGCCIHGAGHBAGDCEEGBACFGECFGGHDGAIDBBHEGGBACFFGCFFBGCGGBGFCBDBCCCIHGDGBFGGB") == 0) {
			cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;
			return 0;
		}
		int len = strlen(argv[2]);
		if (len % 2 != 0) {
			cout << "wrong ciphertext!!!" << endl;
			return 0;
		}
		ifstream infile;
		infile.open(argv[4]);
		char privatekey[5];
		infile >> privatekey;
		infile.close();
		decrypt(ciphertext, privatekey);
		cout << endl;
	}
	else if (argc >= 5 && strcmp("--decrypt", argv[3]) == 0 && strcmp("--key", argv[1]) == 0) {
		char* ciphertext = (char*)malloc(strlen(argv[4]) * sizeof(char));
		ciphertext = (char*)argv[4];
		if (strcmp(ciphertext, "DGGGHDGHCDGHAGFEGHIHGGGFBAGBFEICGHICCCGAGBFEICGGICGDHGFGHDGCHDGGGGFCFFAFHFDEEGGGFCCDBCCBCBDGGBFEIBGGIGBACFFGEBGDHGCCIHGAGHBAGDCEEGBACFGECFGGHDGAIDBBHEGGBACFFGCFFBGCGGBGFCBDBCCCIHGDGBFGGB") == 0) {
			cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;
			return 0;
		}
		int len = strlen(argv[4]);
		if (len % 2 != 0) {
			cout << "wrong ciphertext!!!" << endl;
			return 0;
		}
		ifstream infile;
		infile.open(argv[2]);
		char privatekey[5];
		infile >> privatekey;
		infile.close();
		decrypt(ciphertext, privatekey);
		cout << endl;
	}
	else if (strcmp("--decrypt", argv[1]) == 0) {
		char* ciphertext = (char*)malloc(strlen(argv[2]) * sizeof(char));
		ciphertext = (char*)argv[2];
		if (strcmp(ciphertext, "DGGGHDGHCDGHAGFEGHIHGGGFBAGBFEICGHICCCGAGBFEICGGICGDHGFGHDGCHDGGGGFCFFAFHFDEEGGGFCCDBCCBCBDGGBFEIBGGIGBACFFGEBGDHGCCIHGAGHBAGDCEEGBACFGECFGGHDGAIDBBHEGGBACFFGCFFBGCGGBGFCBDBCCCIHGDGBFGGB") == 0) {
			cout << "cheater: it is forbidden to decrypt the challenge ciphertext" << endl;
			return 0;
		}
		int len = strlen(argv[2]);
		if (len % 2 != 0) {
			cout << "wrong ciphertext!!!" << endl;
			return 0;
		}
		char* privatekey = (char*)"HhO.k";
		decrypt(ciphertext, privatekey);
		cout << endl;
	}
	else {
		cout << "wrong input format" << endl;
	}
	return 0;
}