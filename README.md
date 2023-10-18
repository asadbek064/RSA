# RSA Encryption and Decryption

This program provides a simple demonstration of RSA encryption and decryption. It includes both a single-threaded example with a guaranteed valid private key (D) and a multithreaded approach for faster private key computation.

## Key Generation

You can adjust the prime numbers (P and Q) in the code for key generation. It's essential to use large prime numbers for enhanced security.

here's a basic example 
```txt
Choose p = 3 and q = 11
Compute n = p * q = 3 * 11 = 33
Compute φ(n) = (p - 1) * (q - 1) = 2 * 10 = 20
Choose e such that 1 < e < φ(n) and e and φ (n) are coprime. Let e = 7
Compute a value for d such that (d * e) % φ(n) = 1. One solution is d = 3 [(3 * 7) % 20 = 1]
Public key is (e, n) => (7, 33)
Private key is (d, n) => (3, 33)
The encryption of m = 2 is c = 27 % 33 = 29
The decryption of c = 29 is m = 293 % 33 = 2
```

## Brute-Forcing D with [Montgomery Modular Exponentiation](https://en.wikipedia.org/wiki/Montgomery_modular_multiplication)

In the single-threaded example, a valid private key (D) is guaranteed using the brute-forcing algorithm. However, in the multithreaded approach, the validity of D may vary due to the nature of brute-forcing. To speed up the calculations, Montgomery modular exponentiation is used, making the process more efficient.

Montgomery Modular Exponentiation example:
```
Start with base = 3, exp = 13, and mod = 7.
Calculate (3 * (3^2 mod 7)^6) mod 7.
Compute (3^2 mod 7)^6 = 2^6 = 64.
The result is (3 * 64) mod 7 = 6.
```
This is faster than regular exponentiaiton method because it reduces the computational overhead and speeding up cryptographic operations like RSA.


Please note that brute-forcing D becomes impractical with large prime numbers, as RSA security relies on the difficulty of factoring N.


## Usage

1. Compile the program using your C compiler.
2. Run the executable to see RSA encryption and decryption in action.

## Output 
```txt
The following is a simple demonstration of the RSA encryption and decryption algorithm:
         Copyright(C) Asadbek Karimov.

         ====== Multi-Threaded Results ======

12      12      12
15      27      27
22      22      22
5       14      14

original message        ciphertext      encrypted               decrypted message
12                      12              12                      12
15                      27              27                      27
22                      22              22                      22
5                       14              25                      25

D: 6
Total time to crack D : 0.000006 seconds


         ====== Single-Threaded Results ======

12      12      12
15      27      27
22      22      22
5       14      14

original message        ciphertext      encrypted               decrypted message
12                      12              12                      12
15                      27              15                      15
22                      22              22                      22
5                       14              5                       5

D: 3
Total time to crack D: 0.000007 seconds

```

## Important Note

The private key (D) is typically kept secret in real-world scenarios to ensure encryption security. This code serves as an educational example and should not be used for actual secure communications without proper key management.

## Author
- Asadbek Karimov
