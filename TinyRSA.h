#ifndef __TINYRSA_H__
#define __TINYRSA_H__


//#include "BigInt.h"
#include <gmpxx.h>

class TinyRSA {
public:
	TinyRSA();
	mpz_class randBigNumber(int, mpz_class);
	mpz_class generate_prime(int); // generates a prime number given length

	mpz_class gcd(mpz_class, mpz_class);
	mpz_class modularInverse(mpz_class, mpz_class);

	mpz_class getTotient(mpz_class, mpz_class);

	mpz_class multiplicative_modulo(mpz_class, mpz_class, mpz_class);
	mpz_class modular_exponentiation(mpz_class, mpz_class, mpz_class);
	bool is_prime(mpz_class);

	void generate_keys(mpz_class&, mpz_class&, mpz_class&, int);

	mpz_class encrypt(mpz_class, mpz_class, mpz_class);
	mpz_class decrypt(mpz_class, mpz_class, mpz_class);
};

#endif