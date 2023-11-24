#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "ss.h"
#include "numtheory.h"

void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    srand(time(NULL));

    mpz_t temp, temp2, temp3, e1, e2;
    mpz_inits(temp, temp2, temp3, e1, e2, NULL);

    do {
        uint64_t temp_bits = ((rand() % (((2 * nbits) / 5) - (nbits / 5) + 1))
                              + (nbits / 5)); //setting bits and making primes
        make_prime(p, temp_bits, iters);
        make_prime(q, (nbits - (2 * temp_bits)), iters);

        mpz_mul(temp3, p, p); //setting n
        mpz_mul(n, temp3, q);

        mpz_sub_ui(temp, p, 1);
        mpz_sub_ui(temp2, q, 1);
        gcd(e1, p, temp2); //setting gcd of q-1 and p
        gcd(e2, q, temp); //setting gcd of p-1 and q
        //gmp_fprintf(stderr, "%Zd, Zd\n", p, q);
    } while (mpz_cmp_ui(e1, 1) != 0
             || (mpz_cmp_ui(e2, 1) != 0)); //while q-1 % p isn't 1 or p-1 % q isn't 1

    mpz_clears(temp, temp2, temp3, e1, e2, NULL);
}

void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {
    mpz_t lamda, p_temp, q_temp, gcdt, n;
    mpz_inits(lamda, p_temp, q_temp, gcdt, n, NULL); // temp inits

    mpz_sub_ui(p_temp, p, 1);
    mpz_sub_ui(q_temp, q, 1); // setting temps to -1
    gcd(gcdt, p_temp, q_temp); // setting gcd of p and q

    mpz_mul(pq, p_temp, q_temp); // setting pq as p - 1 * q - 1
    mpz_fdiv_q(lamda, pq, gcdt); // setting lcm
    mpz_mul(pq, p, q); // setting pq back to pq

    mpz_mul(n, pq, p); //setting n

    mod_inverse(d, n, lamda); // making priv with inverse of n mod lamda
    mpz_clears(lamda, p_temp, q_temp, gcdt, n, NULL);
}

void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile) {
    (void) gmp_fprintf(pbfile, "%Zx\n", n);
    (void) gmp_fprintf(pbfile, "%s\n", username);
}

void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {
    (void) gmp_fprintf(pvfile, "%Zx\n", pq);
    (void) gmp_fprintf(pvfile, "%Zx\n", d);
}

void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {
    (void) gmp_fscanf(pbfile, "%Zx\n", n);
    (void) gmp_fscanf(pbfile, "%s\n", username);
}

void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    (void) gmp_fscanf(pvfile, "%Zx\n", pq);
    (void) gmp_fscanf(pvfile, "%Zx\n", d);
}

void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {
    pow_mod(c, m, n, n);
}

void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {
    uint64_t j, size;
    mpz_t m, in, c;
    mpz_inits(m, in, c, NULL); // temp inits

    uint64_t k = ((((mpz_sizeinbase(n, 2)) / 2) - 1) / 8); //setting k

    uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t)); // allocating array for k bytes

    arr[0] = 0xFF; // prepending 1 byte

    //while EOF set arr[i] starting at 1 as next bit from file using fscanf
    while ((j = fread(arr + 1, 1, k - 1, infile)) != EOF) {
        mpz_import(m, j, 1, 1, 1, 0, arr); // import to mpz
        ss_encrypt(c, m, n); // encrypt
        gmp_fprintf(outfile, "%Zd\n", c); // print to file
    }

    free(arr); //freeing list
    mpz_clears(m, in, c, NULL);
}

void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {
    pow_mod(m, c, d, pq);
}

void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t d, mpz_t const pq) {
    uint64_t j;
    mpz_t c, m;
    mpz_inits(c, m, NULL); // temp inits

    uint64_t k = (mpz_sizeinbase(pq, 2) - 1) / 8; //setting k

    uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t)); // allocating array for k bytes

    while (gmp_fscanf(infile, "%Zd\n", c) != EOF) {
        ss_decrypt(m, c, d, pq); // decrypting
        mpz_export(arr, &j, 1, 1, 1, 0, m); // exporting to array

        for (uint64_t i = 1; i < j; ++i) {
            gmp_fprintf(outfile, "%Zd", arr[i]); // printing current block of bytes
        }
        fprintf(outfile, "\n"); // new line
    }
    free(arr);
    mpz_clears(c, m, NULL);
}
