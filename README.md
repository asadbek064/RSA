# [RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem))

This program provides a simple demonstration of the RSA encryption and decryption algorithm. RSA is a widely used asymmetric encryption method for secure communication and data protection.

## Overview
The RSA algorithm relies on two large prime numbers, P and Q, which are used to generate public and private keys. The public key consists of two components: N (the product of P and Q) and E. The private key contains D, which is computed from P, Q, and E.

## Functionality
This program demonstrates the following aspects of RSA:
- Generation of public and private keys based on prime numbers P and Q.
- Encryption of messages using the public key.
- Decryption of ciphertext using the private key.

## Key Generation
To set up the RSA parameters, you can adjust the values of P and Q in the code. Keep in mind that P and Q must be large prime numbers for enhanced security. The program calculates N and the totient (Φ) value from P and Q, and then derives E and D from these values.

## Brute-Forcing `D`
Attempting to brute-force the private key `D` in RSA is impractical due to the vast number of possible values, making it an unrealistic approach. RSA's security relies on the difficulty of factoring `N`, not on discovering `D` directly.

In this demonstration, we brute-force `D` since our P and Q are small. It's essential to note that with larger prime numbers, such a brute-force approach becomes significantly more challenging.

## Usage
1. Compile the program using your C compiler.
2. Run the executable.
3. The program will encrypt and decrypt a set of sample messages using the RSA algorithm.
4. You can adjust the sample messages in the code or provide your own input.

## Important Note
The private key (D) should remain confidential and should not be shared. In a real-world scenario, D is typically not calculated from the public key, as it should be kept secret to ensure the security of the encryption process.

This code serves as an educational example and should not be used for actual secure communications without proper key management.

## Author
- Asadbek Karimov