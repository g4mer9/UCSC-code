//my code from last quarter from when I failed CSE13S, with certain things changed to reflect the new assignments. Don't mark me for plagiarism when it's my own code please.

#include "randstate.h"

#include <stdlib.h>

gmp_randstate_t state;

void randstate_init(uint64_t seed) {
    srand(seed);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

void randstate_clear(void) {
    gmp_randclear(state);
}
