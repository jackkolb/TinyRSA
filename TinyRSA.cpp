#include "TinyRSA.h"

#include <math.h> // for pow in randmpz_class
#include <iostream>
using namespace std;

TinyRSA::TinyRSA() {
    srand(time(NULL));
}


mpz_class TinyRSA::randBigNumber(int length, mpz_class max = 0) {
    if (max == 0) {
        mpz_pow_ui (max.get_mpz_t(), mpz_class(10).get_mpz_t(), length);
    }
    
    mpz_class result;

    while (result < max) {
        result = rand() % 10;
        for (int i = 0; i < length; i++) {
            result = (result * 10) + (rand() % 10);
        }
    }

    return result;
}


mpz_class TinyRSA::generate_prime(int length = 218) {
    mpz_class result;

    while (true) {
        result = randBigNumber(length);
        if (is_prime(result)) {
            return result;
        }
    }
    return 0;
}

mpz_class TinyRSA::getTotient(mpz_class p, mpz_class q) {
    return mpz_class((p - 1) * (q - 1));
}


mpz_class TinyRSA::gcd(mpz_class a, mpz_class b) {
    mpz_class c;
    if (b > a) {
        c = a;
        a = b;
        b = c;
    }

    mpz_class latest;
    while (true) {
        latest = a % b;
        
        a = b;
        if (latest == mpz_class(0)) {
            return a;
        }
        else {
            b = latest;
        }
    }
}


// C function for extended Euclidean Algorithm
mpz_class gcd_ExtendedEuclidean(mpz_class a, mpz_class b, mpz_class *x, mpz_class *y) {
    // Base Case
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    mpz_class x1, y1; // To store results of recursive call
    mpz_class gcd = gcd_ExtendedEuclidean(b%a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}


// Function to find modulo inverse of a
mpz_class TinyRSA::modularInverse(mpz_class a, mpz_class b) {
    mpz_class x, y;
    mpz_class g = gcd_ExtendedEuclidean(a, b, &x, &y);
    mpz_class res = 0;
    if (g != 1) {
        cout << "Inverse doesn't exist";
    }
    else
    {
        // b is added to handle negative x
        res = (x%b + b) % b;
    }
    return res;
}


// calculates (a * b) % c taking into account that a * b might overflow 
mpz_class TinyRSA::multiplicative_modulo(mpz_class a, mpz_class b, mpz_class mod)
{
    mpz_class x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b = b / 2;
    }
    return x % mod;
}

 
// modular exponentiation
mpz_class TinyRSA::modular_exponentiation(mpz_class base, mpz_class exponent, mpz_class mod) {
    mpz_class x = 1;
    mpz_class y = base;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            x = (x * y) % mod;
        }
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
 

// Miller-Rabin primality test
bool TinyRSA::is_prime(mpz_class prime_tested) {
    int iteration = 25; // iteration signifies the accuracy

    // not prime if < 2
    if (prime_tested < 2) {
        return false;
    }

    // not prime if % 2 = 0
    if (prime_tested != 2 && prime_tested % 2 == 0) {
        return false;
    }

    mpz_class s = prime_tested - 1;
    while (s % 2 == 0) {
        s = s / 2;
    }

    for (int i = 0; i < iteration; i++) {
        mpz_class base = rand() % (prime_tested - 1) + 1;
        mpz_class temp = s;
        mpz_class mod = modular_exponentiation(base, temp, prime_tested);
        while (temp != prime_tested - 1 && mod != 1 && mod != prime_tested - 1) {
            mod = multiplicative_modulo(mod, mod, prime_tested);
            temp = temp * 2;
        }
        if (mod != prime_tested - 1 && temp % 2 == 0) {
            return false;
        }
    }
    return true;
}


void TinyRSA::generate_keys(mpz_class &public_key, mpz_class &private_key, mpz_class &n, int length) {

    mpz_class first_prime = generate_prime(length);

    mpz_class second_prime = generate_prime(length);

    n = first_prime * second_prime;
    mpz_class totient = getTotient(first_prime, second_prime);
    
//    mpz_class private_key;

    while (true) {
        private_key = randBigNumber(65567, totient);
        if (private_key == 1 || private_key == 0) {
            continue;
        }
        if (gcd(private_key, totient) == 1) {
            break;
        }
    }
    public_key = modularInverse(private_key, totient);
}


mpz_class TinyRSA::encrypt(mpz_class to_encrypt, mpz_class key, mpz_class product) {
    mpz_class encrypted;
    mpz_powm(encrypted.get_mpz_t(), to_encrypt.get_mpz_t(), key.get_mpz_t(), product.get_mpz_t());
    return encrypted;
}


mpz_class TinyRSA::decrypt(mpz_class to_decrypt, mpz_class key, mpz_class product) {
    mpz_class decrypted;
    mpz_powm(decrypted.get_mpz_t(), to_decrypt.get_mpz_t(), key.get_mpz_t(), product.get_mpz_t());
    return decrypted;
}