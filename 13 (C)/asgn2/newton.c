#include "mathlib.h"

static int iters = 0;

//approximates sqrt with newton method
double sqrt_newton(double x) {
    iters = 0;
    if (x == 0.0)
        return 0.0;
    double sqrt, temp, abs;
    sqrt = x / 2;
    temp = 0.0;
    abs = 0.0;
    do { // gets closer and closer to real sqrt until previous approximation = current approximation
        temp = sqrt;
        sqrt = (x / temp + temp) / 2.0;
        abs = sqrt - temp;
        iters++;
    } while (absolute(abs) > EPSILON);
    return sqrt;
}

int sqrt_newton_iters(void) {
    return iters;
}
