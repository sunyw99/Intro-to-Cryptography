#include<gmp.h>
#include<time.h>
#include<fstream>
#include<string.h>
#include<iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <cstdlib>
using namespace std;

int main()
{
	int security_level = 80;//The security level can be changed according to need.

	//The generating process.
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, time(NULL));
	//Generate p,q.
	mpz_t p, q;
	mpz_init(p);
	mpz_init(q);
	if (security_level < 112) {
		mpz_urandomb(p, state, 1024);
		mpz_urandomb(q, state, 1024);
	}
	else if (security_level < 128) {
		mpz_urandomb(p, state, 2048);
		mpz_urandomb(q, state, 2048);
	}
	else if (security_level < 192) {
		mpz_urandomb(p, state, 3072);
		mpz_urandomb(q, state, 3072);
	}
	else if (security_level < 256) {
		mpz_urandomb(p, state, 7680);
		mpz_urandomb(q, state, 7680);
	}
	else {
		mpz_urandomb(p, state, 15360);
		mpz_urandomb(q, state, 15360);
	}
	mpz_nextprime(p, p);
	mpz_nextprime(q, q);
	//Generate n.
	mpz_t n;
	mpz_init(n);
	mpz_mul(n, p, q);
	//Generate phi.
	mpz_t f;
	mpz_init(f);
	mpz_sub_ui(p, p, 1);
	mpz_sub_ui(q, q, 1);
	mpz_mul(f, p, q);
	//Generate e.
	mpz_t e;
	mpz_init_set_ui(e, 65537);
	//Generate d.
	mpz_t d;
	mpz_init(d);
	mpz_invert(d, e, f);


	//The encrypting process.
	mpz_t m, c;
	mpz_init(c);
	mpz_init_set_ui(m, 1234);//The plaintext can be changed according to need.
	gmp_printf("%s %ZX\n\n", "The plaintext is: ", m);
	mpz_powm(c, m, e, n);
	gmp_printf("%s %ZX\n\n", "The cipertext is: ", c);

	//The decrypting process.
	mpz_t m_decrypted;
	mpz_init(m_decrypted);
	//mpz_init_set_ui(c, 1234); The ciphertext can be changed according to need.
	mpz_powm(m_decrypted, c, d, n);
	gmp_printf("%s %ZX\n\n", "The decrypted message is: ", m_decrypted);

	mpz_clear(m);
	mpz_clear(c);
	mpz_clear(m_decrypted);
	mpz_clear(q);
	mpz_clear(p);
	mpz_clear(n);
	mpz_clear(f);
	mpz_clear(e);
	mpz_clear(d);
	return 0;
}
