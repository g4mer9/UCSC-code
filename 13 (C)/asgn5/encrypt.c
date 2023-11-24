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
    char *pubname = "ss.pub";
    bool v = 0;
    char *username = NULL;
    char *fileerr = "There was a problem opening the file. Make sure it exists.\n";
    char *print_h = "SYNOPSIS\n"
                    "   Encrypts data using SS encryption.\n"
                    "   Encrypted data is decrypted by the decrypt program.\n"
                    "\n"
                    "USAGE\n"
                    "   ./encrypt [OPTIONS]\n"
                    "\n"
                    "OPTIONS\n"
                    "   -h              Display program help and usage.\n"
                    "   -v              Display verbose program output.\n"
                    "   -i infile       Input file of data to encrypt (default: stdin).\n"
                    "   -o outfile      Output file for encrypted data (default: stdout).\n"
                    "   -n pbfile       Public key file (default: ss.pub).";
    int opt = 0;

    while ((opt = (getopt(argc, argv, OPTIONS)) != 1)) {
        switch (opt) {
        case 'i': (void) strcpy(inname, optarg); break;
        case 'o': (void) strcpy(outname, optarg); break;
        case 'n': (void) strcpy(pubname, optarg); break;
        case 'v': v = 1; break;
        case 'h': fprintf(stderr, "%s\n", print_h); return 1;
        default: fprintf(stderr, "%s\n", print_h); return 1;
        }
    }

    mpz_t n;
    mpz_init(n); // mpz inits

    if (access(pubname, F_OK) != 0) {
        fprintf(stderr, "%s", fileerr); //printing file error if cant open
        return 1;
    }
    priv = fopen(pubname, "r"); // opening file

    ss_read_pub(n, username, priv); // setting pub key from file

    if (inname != NULL)
        in = fopen(inname, "r"); // setting input and output files
    if (outname != NULL)
        out = fopen(outname, "w");

    if (v) {
        gmp_fprintf(stderr,
            "user = %s\n"
            "n (%i bits) = %Zd\n",
            username, (int) mpz_sizeinbase(n, 2), n);
    }

    //other stuff
    ss_encrypt_file(in, out, n);
    fclose(priv);
    fclose(in);
    fclose(out);
    mpz_clear(n);
}
