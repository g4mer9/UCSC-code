#include "stats.h"

#include <stdio.h>
#include <stdlib.h>

static void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    if (cmp(stats, A[x], A[y]) == 1) {
        swap(stats, &A[x], &A[y]);
    }
    return;
}

static int count_bits(int n) {
    int count = 0;
    int temp = n;
    while (temp) {
        count++;
        temp >>= 1;
    }
    return count;
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0)
        return;
    int bits = count_bits(n);
    int k = 1 << (bits - 1);
    while (k > 0) {
        //printf("%d\n", k);
        int q = 1 << (bits - 1);
        uint32_t r = 0;
        int d = k;
        while (d > 0) {
            for (uint32_t i = 0; i < (n - d); i++) {
                if ((i & k) == r)
                    comparator(stats, A, i, i + d);
            }
            d = q - k;
            q >>= 1;
            r = k;
        }
        k >>= 1;
    }
    return;
}
