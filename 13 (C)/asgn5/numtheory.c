//my code from last quarter from when I failed CSE13S, with certain things changed to reflect the new assignments. Don't mark me for plagiarism when it's my own code please.
#include "numtheory.h"
#include "randstate.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

//gmp_randstate_t state;

void gcd(mpz_t g, const mpz_t a, const mpz_t b) {
    mpz_t temp, atemp, btemp, temp1;
    mpz_inits(temp, temp1, atemp, btemp, NULL); // inits temps

    mpz_set_ui(g, 1);
    mpz_set(atemp, a);
    mpz_set(btemp, b); // stores a and b, and sets default return to 1

    while (mpz_cmp_ui(b, 0) != 0) { // while b is not 0
        mpz_set(temp, btemp);
        mpz_mod(btemp, a, b);
        mpz_set(atemp, temp);
    }
    mpz_set(g, atemp); //setting output

    mpz_clears(temp, temp1, atemp, btemp, NULL);
}

void mod_inverse(mpz_t o, const mpz_t a, const mpz_t n) {
    mpz_t r0, r1, t0, t1, temp, temp2, q;
    mpz_inits(r0, r1, t0, t1, temp, temp2, q, NULL); // temp inits

    mpz_set_ui(o, 0); // setting default return

    mpz_set(r0, n); // first two sets in pseudocode
    mpz_set(r1, a);
    mpz_set_ui(t0, 0);
    mpz_set_ui(t1, 1);

    while (mpz_cmp_ui(r1, 0) != 0) {
        mpz_fdiv_q(temp, r0, r1); // setting q to r / r'
        mpz_set(q, temp);

        mpz_set(temp, r0); // setting r to r', storing original r to temp
        mpz_set(r0, r1);

        mpz_mul(temp2, q, r1); // set r' to r-1*r'
        mpz_sub(r1, temp, temp2);

        mpz_set(temp, t0); // setting t to t', storing original t to temp
        mpz_set(t0, t1);

        mpz_mul(temp2, q, t1); // setting t' to t-1*t'
        mpz_sub(t1, temp, temp2);
    }
    if ((mpz_cmp_ui(r0, 1) <= 0)) { // if r > 1, this doesn't trigger and i remains 0
        if (mpz_cmp_ui(t0, 0) < 0)
            mpz_add(t0, t0, n); // if t < 0 add n to t
        mpz_set(o, t0); // "returning" t
    }
    mpz_clears(r0, r1, t0, t1, temp, temp2, q, NULL);
}

void pow_mod(mpz_t o, const mpz_t a, const mpz_t d, const mpz_t n) {
    mpz_t p, temp, dtemp;
    mpz_inits(p, temp, dtemp, NULL); // temp inits

    mpz_set_ui(o, 1); //setting default output as 1 and p as a
    mpz_set(p, a);
    mpz_set(dtemp, d);

    while (mpz_cmp_ui(dtemp, 0) > 0) { // while d > 0

        mpz_mod_ui(temp, n, 2);
        if (mpz_cmp_ui(temp, 0) != 0) { // if d is odd
            mpz_mul(temp, o, p);
            mpz_mod(o, temp, n); // setting o to o * p mod n
        }

        mpz_mul(temp, p, p);
        mpz_mod(p, temp, n); // setting p to p * p mod n

        mpz_fdiv_q_ui(dtemp, dtemp, 2); // dividing exp by 2
    }
    mpz_clears(p, temp, dtemp, NULL);
}

bool is_prime(const mpz_t n, uint64_t iters) {
    mpz_t s, r, y, j, a, temp, temp2;
    mpz_inits(s, r, y, j, a, temp, temp2, NULL); //initializing temps

    mpz_mod_ui(temp, n, 2);
    if (mpz_cmp_ui(n, 2) == 0)
        return 1; //if n is 2, return true
    else if (mpz_cmp_ui(temp, 0) == 0)
        return 0; //if n is even, return false

    mpz_sub_ui(r, n, 1);
    mpz_set_ui(s, 0);
    while (1) {
        mpz_mod_ui(temp, r, 2);
        if (mpz_cmp_ui(temp, 0) == 0) {
            mpz_fdiv_q_ui(r, r, 2);
            mpz_add_ui(s, s, 1);
        } else
            break;
    }
    for (uint64_t i = 1; i < iters; i++) {
        //random a
        mpz_set_ui(temp, 0);
        mpz_set_ui(a, 0);
        mpz_sub_ui(temp, n, 2);
        mpz_urandomm(a, state, temp);
        if (mpz_cmp(a, temp) != 0)
            mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);
        mpz_sub_ui(temp, n, 1);
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, temp) != 0)) {
            mpz_set_ui(j, 1);
            while (1) {
                mpz_sub_ui(temp, n, 1);
                mpz_sub_ui(temp2, s, 1);
                if (!((mpz_cmp(j, temp2) <= 0) && (mpz_cmp(y, temp) == 0)))
                    break;
                mpz_set_ui(temp, 2);
                pow_mod(y, y, temp, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(s, r, y, j, a, temp, temp2, NULL);
                    return 0;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, temp) != 0) {
                mpz_clears(s, r, y, j, a, temp, temp2, NULL);
                return 0;
            }
        }
    }
    mpz_clears(s, r, y, j, a, temp, temp2, NULL);
    return 1;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t cons;
    mpz_init(cons);
    mpz_set_ui(cons, 2);

    mpz_pow_ui(p, cons, (bits - 1)); // makes prime by subtracting 1 from 2^bits-1
    mpz_sub_ui(p, p, 1);

    while (1) {
        //gmp_fprintf(stderr, "%Zd\n", p);
        if ((is_prime(p, iters)) && ((mpz_sizeinbase(p, 2)) >= bits))
            break; //if prime and has more bits than bits
        mpz_add_ui(p, p, 2); // check next odd number
    }
    mpz_clear(cons);
}
