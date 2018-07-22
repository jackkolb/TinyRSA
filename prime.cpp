/* 
 * C++ Program to Implement MiBigInter Rabin Primality Test
 */

#include "bigint/BigInt.h"

#include <gmpxx.h>

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;
 
 
// calculates (a * b) % c taking into account that a * b might overflow 
mpz_class multiplicative_modulo(mpz_class a, mpz_class b, mpz_class mod)
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
mpz_class modular_exponentiation(mpz_class base, mpz_class exponent, mpz_class mod) {
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
bool is_prime(mpz_class prime_tested) {
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


// Main
int main()
{
    string input;

    mpz_class num;
    num = "32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152301645904403697613233287231227125684710820209725157101726931323469678542580656697935045997268352998638215525166389647960126939249806625440700685819469589938384356951833568218188663";

    if (is_prime(num))
        cout<<num<<" is prime"<<endl;
    else
        cout<<num<<" is not prime"<<endl;
    return 0;
}
