/* 
    Files Name      rsa.c
    Description     Simple demonstration of RSA encryption and decryption algorithm
 */

#include <stdio.h>
#include <math.h>

// Modular exponentiation function to avoid integer overflow
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

// Calculate modular multiplicative inverse
long long modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0;
    long long x1 = 1;

    while (a > 1) {
         q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

     if (x1 < 0)
        x1 += m0;

    return x1;
}

int main(void) {
    int i;
    int msg[4] = {12, 15, 22, 5};
    long en[4], de[4];
    int SecCode[4], DeMsg[4];

    // RSA parameters
    /* P and Q must be prime numbers and must be very large in real production use */
    #define P (3)
    #define Q (11)
    #define N (P * Q)
    #define Totient ((P - 1) * (Q - 1)) /* Euler's totient function */
    #define E (7)                       /* E must have only one common divisor with Totient */
    long long D = modInverse(E, Totient);


    printf("The following is a simple demonstration of the RSA encryption and decryption algorithm:\n");
    printf("\t Copyright(C) Asadbek Karimov.\n\n");

    for (i = 0; i < 4; i++) {
        // C = M^E MOD N using modular exponentiation
        en[i] = modExp(msg[i], E, N);
        SecCode[i] = en[i];

        printf("%d\t\t\t%ld\t\t%d\n", msg[i], en[i], SecCode[i]);
    }

    printf("\noriginal message\tciphertext\tencrypted\t\tdecrypted message\n");

    for (i = 0; i < 4; i++) {
        // M = C^D MOD N using modular exponentiation
        de[i] = modExp(SecCode[i], D, N);
        DeMsg[i] = de[i];

        printf("%d\t\t\t%d\t\t%ld\t\t\t%d\n", msg[i], SecCode[i], de[i], DeMsg[i]);
    }

    getchar();

    return 0;
}
