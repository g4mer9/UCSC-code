#include "mathlib.h"

static int terms = 0;

//approximates e, stops when next term in taylor series < epsilon
double e(void) {
    terms = 0;
    double denom;
    int k = 0;
    double next_term = 1.0;
    double e_sum = 0.0;

    while (next_term > EPSILON) { //checks if next term calculated in previous loop is larger than E
        e_sum += next_term; //adding to sum
        terms++;
        k++; //iteration count
        denom = 1; //resets denom for next factorial calculation
        for (double i = 1; i <= k; i++) { //factorial loop
            denom *= i;
        }
        next_term = 1.0 / denom; //next term in the series
    }
    e_sum += next_term; //adding to sum
    terms++;
    return e_sum;
}
//returns num of terms in e taylor series calculated
int e_terms(void) {
    return terms;
}
