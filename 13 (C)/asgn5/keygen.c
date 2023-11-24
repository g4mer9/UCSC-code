#include "ss.h"
#include "randstate.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <gmp.h>

#define OPTIONS "vhb:i:n:d:s:"
//gmp_randstate_t state;

int main(int argc, char **argv) {
    FILE *pb, *pv;
    char *pbfile = "ss.pub";
    char *pvfile = "ss.priv";
    int v = 0;
    int opt = 0;
    uint64_t nbits = 256;
    uint64_t seed = time(NULL);
    uint64_t iters = 50;
    char *fileerr = "There was a problem opening the file. Make sure it exists.\n";
    char *username;
    char *print_h = "SYNOPSIS\n"
                    "   Generates an SS public/private key pair.\n"
                    "\n"
                    "USAGE\n"
                    "   ./keygen [OPTIONS]\n"
                    "\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -b bits         Minimum bits needed for public key n (default: 256).\n"
                    "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n"
                    "   -n pbfile       Public key file (default: ss.pub).\n"
                    "   -d pvfile       Private key file (default: ss.priv).\n"
                    "   -s seed         Random seed for testing.";

    while ((opt = (getopt(argc, argv, OPTIONS))) != -1) {
        switch (opt) {
        case 'v': v = 1; break;
        case 'b': nbits = (int) strtol(optarg, (char **) NULL, 10); break;
        case 'i': iters = (int) strtol(optarg, (char **) NULL, 10); break;
        case 'n': (void) strcpy(pbfile, optarg); break;
        case 'd': (void) strcpy(pvfile, optarg); break;
        case 's': seed = (int) strtol(optarg, (char **) NULL, 10); break;
        case 'h': fprintf(stderr, "%s\n", print_h); return 1;
        }
    }

    mpz_t p, q, n, d, pq;
    mpz_inits(p, q, n, d, pq, NULL);

    if (access(pbfile, F_OK) != 0) {
        fprintf(stderr, "%s\n", fileerr); //printing file error if cant open
        return 1;
    }
    if (access(pvfile, F_OK) != 0) {
        fprintf(stderr, "%s\n", fileerr); //printing file error if cant open
        return 1;
    }
    pb = fopen(pbfile, "w"); // opening file
    pv = fopen(pvfile, "w");

    fchmod(fileno(pv), 0600);

    randstate_init(seed);

    ss_make_pub(p, q, n, nbits, iters);
    fprintf(stderr, "passes make pub\n");
    ss_make_priv(d, pq, p, q);

    username = getenv("USER");

    ss_write_pub(n, username, pb);

    ss_write_priv(pq, d, pv);

    if (v)
        gmp_fprintf(stdout,
            "username = %s\n"
            "p (%i bits) = %Zd\n"
            "q (%i bits) = %Zd\n"
            "n (%i bits) = %Zd\n"
            "d (%i bits) = %Zd\n"
            "pq (%i bits) = %Zd\n",
            username, (int) mpz_sizeinbase(p, 2), p, (int) mpz_sizeinbase(q, 2), q,
            (int) mpz_sizeinbase(n, 2), n, (int) mpz_sizeinbase(d, 2), d,
            (int) mpz_sizeinbase(pq, 2), pq);

    fclose(pb);
    fclose(pv);
    mpz_clears(p, q, n, d, pq, NULL);
}
