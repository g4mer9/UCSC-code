#include "mathlib.h"

static int terms = 0;

//approximates pi using madhava method
double pi_madhava(void) {
    terms = 0;
    int k = 0;
    double pi_sum = 0.0;
    double next_term = 1.0;
    double num = 1.0;

    while (num > EPSILON) { //checks if next term calculated in previous loop is larger than E
        pi_sum += next_term; //adding to sum
        terms++;

        k++; //iteration count
        num = -3.0;
        for (int i = 1; i < k; i++) { //pow function
            num *= -3.0;
        }

        if (k > 0)
            num = 1.0
                  / num; // setting num to be reciprocal of itself if k > 0, otherwise setting it to 1 bc it's to the 0th exponent.
        else
            num = 1;

        next_term = num * (1.0 / ((2.0 * k) + 1.0)); //writes next term
        num = absolute(next_term);
    }
    pi_sum += next_term; //adding to sum
    terms++;
    pi_sum *= sqrt_newton(12.0);

    return pi_sum;
}

//returns number of terms calculated during pi approximation
int pi_madhava_terms(void) {
    return terms;
}
