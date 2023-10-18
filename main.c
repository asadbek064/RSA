/* 
    Files Name      rsa.c
    Description     Simple demonstration of RSA encryption and decryption algorithm
 */

#include <stdio.h>
#include <math.h>
#include <pthread.h>


// Shared data structure to store D and a flag indicating if D is found
typedef struct {
    long long D;
    int found;
} SharedData;


// RSA parameters
/* P and Q must be prime numbers and must be very large in real production use */
#define P (3)
#define Q (11)
#define N (P * Q)
#define Totient ((P - 1) * (Q - 1)) /* Euler's totient function */
#define E (7)                       /* E must have only one common divisor with Totient */


#define NUM_THREADS 4

// brute-force D (multithreaded approach may not guarantee a valid D in all cases)
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

// Calculate modular multiplicative inverse using Extended Euclidean Algorithm (guarantees a valid D)
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


int main(void) {
    // Multi Threaded
    int i;
    int msg[4] = {12, 15, 22, 5};
    long en[4], de[4];
    int SecCode[4], DeMsg[4];
    long long D_MT = 0;
    

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
            D_MT = results[i];
            break;
        }
    }

    printf("\t ====== Multi-Threaded Results ======\n\n");


     for (i = 0; i < 4; i++) {
        // C = M^E MOD N using modular exponentiation
        en[i] = montgomeryExp(msg[i], E, N);
        SecCode[i] = en[i];
        printf("%d\t%ld\t%d\n", msg[i], en[i], SecCode[i]);
    }

    printf("\noriginal message\tciphertext\tencrypted\t\tdecrypted message\n");

    for (i = 0; i < 4; i++) {
        // M = C^D MOD N using modular exponentiation
        de[i] = montgomeryExp(SecCode[i], D_MT, N);
        DeMsg[i] = de[i];
        printf("%d\t\t\t%d\t\t%ld\t\t\t%d\n", msg[i], SecCode[i], de[i], DeMsg[i]);
    }

    printf("\nD: %lld\nTotal time to crack D : %f seconds\n\n\n", D_MT,(double)D_MT / CLOCKS_PER_SEC);

    // Single Threaded
    int i_ST;
    int msg_ST[4] = {12, 15, 22, 5};
    long en_ST[4], de_ST[4];
    int SecCode_ST[4], DeMsg_ST[4];

    clock_t start_time_ST = clock(); 
    long long D_ST = modInverse(E, Totient);
    clock_t end_time_ST = clock(); 

    double total_time_ST = (double)(end_time_ST - start_time_ST) / CLOCKS_PER_SEC;

    printf("\t ====== Single-Threaded Results ======\n\n");

    for (i_ST = 0; i_ST < 4; i_ST++) {
        // C = M^E MOD N using modular exponentiation
        en_ST[i_ST] = montgomeryExp(msg_ST[i_ST], E, N);
        SecCode_ST[i_ST] = en_ST[i_ST];
        printf("%d\t%ld\t%d\n", msg_ST[i_ST], en_ST[i_ST], SecCode_ST[i_ST]);
    }

    printf("\noriginal message\tciphertext\tencrypted\t\tdecrypted message\n");

    for (i_ST = 0; i_ST < 4; i_ST++) {
        // M = C^D MOD N using modular exponentiation
        de_ST[i_ST] = montgomeryExp(SecCode_ST[i_ST], D_ST, N);
        DeMsg_ST[i_ST] = de_ST[i_ST];
        printf("%d\t\t\t%d\t\t%ld\t\t\t%d\n", msg_ST[i_ST], SecCode_ST[i_ST], de_ST[i_ST], DeMsg_ST[i_ST]);
    }

    printf("\nD: %lld\nTotal time to crack D: %f seconds\n", D_ST, total_time_ST);

    getchar();

    return 0;
}
