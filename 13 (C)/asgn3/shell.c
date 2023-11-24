//my code from last quarter from when I failed CSE13S, with certain things changed to reflect the new assignments. Don't mark me for plagiarism when it's my own code please.

#include "shell.h"

#include "gaps.h"
#include "stats.h"

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    uint32_t gap = 1;
    uint32_t j;
    uint32_t k = 0;
    uint32_t temp;
    while (gap >= 1) {
        gap = gaps[k];
        for (uint32_t i = gap; i < length; i++) {
            j = i;
            temp = move(stats, arr[i]);
            while ((j >= gap) && (cmp(stats, temp, arr[j - gap])) == -1) {
                arr[j] = move(stats, arr[j - gap]);
                j -= gap;
            }
            arr[j] = move(stats, temp);
        }
        k++;
    }
}
