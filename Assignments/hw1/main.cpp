#include <gmpxx.h>
#include <iostream>
#include <ctime>
using namespace std;

pair<mpz_class, pair<mpz_class, mpz_class> > extended_euclidean_algorithm(const mpz_class& a, const mpz_class& b) {
	pair<mpz_class, mpz_class> r(b, a), s(0, 1), t(1, 0);
	while (r.first != 0)
	{
		mpz_class q = r.second / r.first;
		r = make_pair(r.second - q * r.first, r.first);
		s = make_pair(s.second - q * s.first, s.first);
		t = make_pair(t.second - q * t.first, t.first);
	}
	return make_pair(r.second, make_pair(s.second, t.second));
}

int main() {
	gmp_randclass rr(gmp_randinit_default);
	rr.seed(time(nullptr));
	mpz_class a = rr.get_z_bits(4096);
	mpz_class b = rr.get_z_bits(4096);
	mpz_class GMPresult = gcd(a, b);
	mpz_class EUCresult = extended_euclidean_algorithm(a, b).first;
	cout << "The first random number is: " << a << endl;
	cout << "The second random number is: " << b << endl;
	cout << "gcd(a,b) with GMP Library: " << GMPresult << endl;
	cout << "gcd(a,b) with extended Euclidean algorithm: " << EUCresult << endl;
	if (EUCresult == GMPresult) cout << "The result is same as that of the GMP function." << endl;
	else cout << "The result is different from that of the GMP function." << endl;
	return 0;
}
