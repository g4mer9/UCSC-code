#include "quick.h"

#include "shell.h"
#include "stats.h"

#include <stdio.h>

//partition position
static int pos(Stats *stats, uint32_t *a, uint32_t n) {
    uint32_t pivot = move(stats, a[n - 1]);
    int i = 0;
    for (uint32_t j = 0; j < n - 1; j++) {
        if (cmp(stats, a[j], pivot) == -1) {
            swap(stats, &a[i], &a[j]);
            i++;
        }
    }
    swap(stats, &a[i], &a[n - 1]);
    return (i);
}

void quick_sort(Stats *stats, uint32_t *a, uint32_t n) {

    uint32_t small = 8;
    if (n < small) {
        shell_sort(stats, a, n);
        return;
    }
    int p = pos(stats, a, n);
    quick_sort(stats, a, p);
    quick_sort(stats, (a + p + 1), (n - p - 1));
}
