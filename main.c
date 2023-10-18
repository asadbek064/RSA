/* 
    Files Name      rsa.c
    Description     Simple demonstration of RSA encryption and decryption algorithm
 */

#include <stdio.h>
#include <math.h>
#include <pthread.h>


// RSA parameters
/* P and Q must be prime numbers and must be very large in real production use */
#define P (3)
#define Q (11)
#define N (P * Q)
#define Totient ((P - 1) * (Q - 1)) /* Euler's totient function */
#define E (7)                       /* E must have only one common divisor with Totient */


#define NUM_THREADS 4

// brute-force D
void* bruteForceD(void* args) {
    long long* result = (long long*)args;

    // Define the range of values to check for D
    long long start = 1;
    long long end = N;  // Adjust the upper bound as needed

    clock_t start_time = clock();

    for (long long d = start; d <= end; d++) {
        // Check if (E * d) % Totient == 1 to find D
        if ((E * d) % Totient == 1) {
            *result = d;
            break;  // D found, exit the loop
        }
    }

    clock_t end_time = clock();
    *result = end_time - start_time;

    pthread_exit(NULL);
}


// Montgomery modular exponentiation
long long montgomeryExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Calculate modular multiplicative inverse using Extended Euclidean Algorithm
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
    long long D = 0;


    printf("The following is a simple demonstration of the RSA encryption and decryption algorithm:\n");
    printf("\t Copyright(C) Asadbek Karimov.\n\n");

    // create an array of thread handles
    pthread_t threads[NUM_THREADS];
    long long results[NUM_THREADS];

    // invoke threads
    for(i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, bruteForceD, &results[i]);
    }

    // wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        if (results[i] > 0) {
            D = results[i];
            break;
        }
    }


     for (i = 0; i < 4; i++) {
        // C = M^E MOD N using modular exponentiation
        en[i] = montgomeryExp(msg[i], E, N);
        SecCode[i] = en[i];
        printf("%d\t%ld\t%d\n", msg[i], en[i], SecCode[i]);
    }

    printf("\noriginal message\tciphertext\tencrypted\t\tdecrypted message\n");

    for (i = 0; i < 4; i++) {
        // M = C^D MOD N using modular exponentiation
        de[i] = montgomeryExp(SecCode[i], D, N);
        DeMsg[i] = de[i];
        printf("%d\t%d\t%ld\t%d\n", msg[i], SecCode[i], de[i], DeMsg[i]);
    }

    printf("Total time to crack D: %f seconds\n", (double)D / CLOCKS_PER_SEC);

    getchar();

    return 0;
}
