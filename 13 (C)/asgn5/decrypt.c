#include "ss.h"
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <gmp.h>
#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {
    FILE *in = stdin;
    char *inname = NULL;
    FILE *out = stdout;
    char *outname = NULL;
    FILE *priv;
    char *privname = "ss.priv";
    bool v = 0;
    char *fileerr = "There was a problem opening the file. Make sure it exists.\n";
    char *print_h = "SYNOPSIS\n"
                    "   Decrypts data using SS decryption.\n"
                    "   Encrypted data is encrypted by the encrypt program.\n"
                    "\n"
                    "USAGE\n"
                    "   ./decrypt [OPTIONS]\n"
                    "\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -i infile       Input file of data to decrypt (default: stdin).\n"
                    "   -o outfile      Output file for decrypted data (default: stdout).\n"
                    "   -n pvfile       Private key file (default: ss.priv).";
    int opt = 0;

    while ((opt = (getopt(argc, argv, OPTIONS)) != 1)) {
        switch (opt) {
        case 'i': (void) strcpy(inname, optarg); break;
        case 'o': (void) strcpy(outname, optarg); break;
        case 'n': (void) strcpy(privname, optarg); break;
        case 'v': v = 1; break;
        case 'h': fprintf(stderr, "%s\n", print_h); return 1;
        default: fprintf(stderr, "%s\n", print_h); return 1;
        }
    }

    mpz_t pq, d;
    mpz_inits(pq, d, NULL); // mpz inits

    if (access(privname, F_OK) != 0) {
        fprintf(stderr, "%s", fileerr); //printing file error if cant open
        return 1;
    }
    priv = fopen(privname, "r"); // opening file

    ss_read_priv(pq, d, priv); // setting private key from file

    if (inname != NULL)
        in = fopen(inname, "r"); // setting input and output files
    if (outname != NULL)
        out = fopen(outname, "w");

    if (v)
        gmp_fprintf(stderr,
            "pq (%i bits) = %Zd\n"
            "d (%i bits) = %Zd\n",
            (int) mpz_sizeinbase(pq, 2), pq, (int) mpz_sizeinbase(d, 2), d); //verbose output

    ss_decrypt_file(in, out, d, pq);

    fclose(priv);
    fclose(in);
    fclose(out);
    mpz_clears(pq, d, NULL);
}
