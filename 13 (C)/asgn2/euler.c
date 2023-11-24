#include "mathlib.h"

static int terms = 0;

//approximates pi with euler method
double pi_euler(void) {
    terms = 0;
    unsigned long long k = 1;
    double pi_sum = 0.0;
    double next_term = 1.0;

    while (next_term > EPSILON) { //checks if next term calculated in previous loop is larger than E
        pi_sum += next_term; //adding to sum
        terms++;
        k++; //iteration count

        next_term = 1.0 / (k * k); //calculating next term in series
    }
    pi_sum += next_term; //adding to sum
    terms++;
    pi_sum *= 6.0; //6 on outside of sigma notation in euler solution
    return sqrt_newton(pi_sum); //square rooting answer as shown in euler solution
}

//returns number of terms calculated during pi approximation
int pi_euler_terms(void) {
    return terms;
}
