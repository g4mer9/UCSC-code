#include "mathlib.h"

#include <stdint.h>

static int terms = 0;

//approximates pi using the bbp method
double pi_bbp(void) {
    terms = 0;
    int k = 0;
    uint64_t temp;
    double pi_sum = 0.0;
    double next_term;

    while (1) { //loops sum until next term < epsilon
        temp = 16;
        if (k == 0)
            temp = 1;
        else
            for (int i = 1; i < k; i++)
                temp *= 16; // pow for the leading 16^-k coefficient
        next_term = (1.0 / temp)
                    * ((4.0 / (8.0 * k + 1.0)) - (2.0 / (8.0 * k + 4.0)) - (1.0 / (8.0 * k + 5.0))
                        - (1.0 / (8.0 * k + 6.0)));
        if (next_term < EPSILON) {
            pi_sum += next_term; //adding next term
            terms++;
            break; //epsilon check here since first term isn't 1
        }
        pi_sum += next_term; //adding next term
        terms++;
        k++; //iteration count
    }
    return pi_sum;
}

int pi_bbp_terms(void) {
    return terms;
}
