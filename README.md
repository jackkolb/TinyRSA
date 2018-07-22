# TinyRSA

An RSA libary that is actually easy to implement and use. After having great 
difficulty using OpenSSL... LibTomCrypt... various others... I decided to make my 
own instead, designed for simplicity and ease of use for the programmer. This 
libary does not include padding, ideal-prime-checking, or other advanced features 
for commercial applications, but should work well for smaller projects with limited 
audiences.


## Current Features

- Generate keys
- - Generate a prime number
- - - Generate a large number
- - - Primality check (Miller-Rabin)
- Encrypt a number (given public key and n)
- Decrypt a number (given private key and n)


## Upcoming Features

- Store keys/outputs as std::string so the user doesn't need to deal 
with GMP
- Header guards and standard formatting
- Comments :-)
- Standalone compiling


## Requirements

TinyRSA uses the GNU Multiprecision (GMP) number library to store numbers -- 
this will need to be installed on the system


## Example

```
#include <iostream>

#include "TinyRSA.h"
#include <gmpxx.h>

int main()
{
    TinyRSA rsa; // make a TinyRSA object to access its functions

    // keys, will be modifed by the generate_keys() function
    mpz_class public_key;
    mpz_class private_key;
    mpz_class n;
    
    rsa.generate_keys(public_key, private_key, n, 613); // generates the keys; 613 represents a 2048-bit encryption

    mpz_class testnum; // test number to encrypt
    testnum = "123"; // using 123 as an example

    mpz_class encrypted;
    encrypted = rsa.encrypt(testnum, public_key, n); // uses the public key and n to encrypt testnum

    std::cout << "Encrypted: " << encrypted << std::endl;

    mpz_class decrypted;
    decrypted = rsa.decrypt(encrypted, private_key, n); // uses the private key and n to decrypt the encrypted value

    std::cout << "Decrypted: " << decrypted << std::endl;
    return 0;
}
```
