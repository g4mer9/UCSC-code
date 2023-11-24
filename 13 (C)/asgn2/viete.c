#include "mathlib.h"

static int terms = 0;

//approximates pi using the bbp method
double pi_viete(void) {
    terms = 0;
    double ak;
    double aj = sqrt_newton(2);
    double pi_sum = 1.0;
    double next_term = sqrt_newton(2.0) / 2.0;
    double temp;

    do { //loops sum until next term < epsilon
        pi_sum *= next_term; //adding next term
        terms++;
        ak = sqrt_newton(2.0 + aj);
        aj = ak;
        next_term = ak / 2.0;
        temp = absolute((next_term - 1));

    } while (temp > EPSILON);
    return (2.0 / pi_sum);
}

int pi_viete_factors() {
    return terms;
}
