//my code from last quarter from when I failed CSE13S, with certain things changed to reflect the new assignments. Don't mark me for plagiarism when it's my own code please.

#include "heap.h"

#include "stats.h"

#include <stdio.h>
#include <stdlib.h>

uint32_t l_child(uint32_t n) {
    return 2 * n + 1;
}

uint32_t r_child(uint32_t n) {
    return 2 * n + 2;
}

uint32_t parent(uint32_t n) {
    return (n - 1) / 2;
}

uint32_t smaller;
uint32_t *heap;
uint32_t *sorted_list;

void up_heap(Stats *stats, uint32_t *a, uint32_t n) {
    while ((n > 0) && (a[n] < a[parent(n)])) {
        swap(stats, &a[n], &a[parent(n)]);
        n = move(stats, parent(n));
    }
}
void down_heap(Stats *stats, uint32_t *a, uint32_t heap_size) {
    int n = 0;
    while (cmp(stats, l_child(n), heap_size) == -1) {
        if (cmp(stats, r_child(n), heap_size) == 0)
            smaller = l_child(n);
        else {
            if (cmp(stats, a[l_child(n)], a[r_child(n)]) == -1)
                smaller = l_child(n);
            else
                smaller = r_child(n);
        }
        if (cmp(stats, a[n], a[smaller]) == -1)
            break;
        swap(stats, &a[n], &a[smaller]);
        n = smaller;
    }
}
uint32_t *build_heap(Stats *stats, uint32_t *list, uint32_t elements) {
    heap = (uint32_t *) calloc(elements, sizeof(uint32_t));
    for (uint32_t i = 0; i < elements; i++) {
        heap[i] = 0;
    }
    for (uint32_t n = 0; n < elements; n++) {
        heap[n] = move(stats, list[n]);
        up_heap(stats, heap, n);
    }
    return heap;
}

void heap_sort(Stats *stats, uint32_t *list, uint32_t elements) {
    sorted_list = (uint32_t *) calloc(elements, sizeof(uint32_t));
    heap = build_heap(stats, list, elements);
    for (uint32_t i = 0; i < elements; i++) {
        sorted_list[i] = 0;
    }
    for (uint32_t n = 0; n < elements; n++) {
        sorted_list[n] = heap[0];
        heap[0] = heap[elements - n - 1];
        down_heap(stats, heap, elements - n);
    }
    for (uint32_t i = 0; i < elements; i++) {
        list[i] = sorted_list[i];
    }
    free(sorted_list);
    free(heap);
}
