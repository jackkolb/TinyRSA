#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <cmath>

#include "TinyRSA.h"
#include <gmpxx.h>

using namespace std;


int main()
{
    TinyRSA rsa;

    mpz_class public_key;
    mpz_class private_key;
    mpz_class n;
    
    rsa.generate_keys(public_key, private_key, n, 613);

    mpz_class testnum;
    testnum = "213";

    mpz_class encrypted;
    encrypted = rsa.encrypt(testnum, public_key, n);

    cout << "Encrypted: " << encrypted << endl;

    mpz_class decrypted;
    decrypted = rsa.decrypt(encrypted, private_key, n);

    cout << "Decrypted: " << decrypted << endl;
    return 0;
}
