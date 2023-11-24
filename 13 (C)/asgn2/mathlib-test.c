#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    bool u, b, m, eu, v, n, s;
    s = 0;
    int opt = 0;
    double temp, temp1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { //commandline args
        switch (opt) {
        case 'a': u = 1, b = 1, m = 1, eu = 1, v = 1, n = 1; break;
        case 'e': u = 1; break;
        case 'b': b = 1; break;
        case 'm': m = 1; break;
        case 'r': eu = 1; break;
        case 'v': v = 1; break;
        case 'n': n = 1; break;
        case 's': s = 1; break;
        case 'h':
            printf("SYNOPSIS\n"
                   "   A test harness for the small numerical library.\n"
                   "\n"
                   "USAGE\n"
                   "   ./mathlib-test [-aebmrvnsh]\n"
                   "\n"
                   "OPTIONS\n"
                   "  -a   Runs all tests.\n"
                   "  -e   Runs e test.\n"
                   "  -b   Runs BBP pi test.\n"
                   "  -m   Runs Madhava pi test.\n"
                   "  -r   Runs Euler pi test.\n"
                   "  -v   Runs Viete pi test.\n"
                   "  -n   Runs Newton square root tests.\n"
                   "  -s   Print verbose statistics.\n"
                   "  -h   Display program synopsis and usage.\n");
            return 1;
        }
    }

    //testing and printing results
    if (u) {
        temp = e();
        temp1 = temp - M_E;
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", temp, M_E, absolute(temp1));
        if (s)
            printf("e() terms = %d\n", e_terms());
    }
    if (eu) {
        temp = pi_euler();
        temp1 = temp - M_PI;
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", temp, M_PI,
            absolute(temp1));
        if (s)
            printf("pi_euler() terms = %d\n", pi_euler_terms());
    }
    if (b) {
        temp = pi_bbp();
        temp1 = temp - M_PI;
        printf(
            "pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", temp, M_PI, absolute(temp1));
        if (s)
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
    }
    if (m) {
        temp = pi_madhava();
        temp1 = temp - M_PI;
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", temp, M_PI,
            absolute(temp1));
        if (s)
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
    }
    if (v) {
        temp = pi_viete();
        temp1 = temp - M_PI;
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", temp, M_PI,
            absolute(temp1));
        if (s)
            printf("pi_viete() terms = %d\n", pi_viete_factors());
    }
    if (n) {
        for (double i = 0; i <= 10; i += .1) {
            temp = sqrt_newton(i);
            temp1 = temp - sqrt(i);
            printf("sqrt_newton(%16.15lf) = %16.15lf, sqrt(%16.15lf) = %16.15lf, diff = %16.15lf\n",
                i, temp, i, sqrt(i), absolute(temp1));
            if (s)
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
        }
    }

    return 0;
}
