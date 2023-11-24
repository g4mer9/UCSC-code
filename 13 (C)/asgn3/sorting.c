//my code from last quarter from when I failed CSE13S, with certain things changed to reflect the new assignments. Don't mark me for plagiarism when it's my own code please.

#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "Hasbqhr:n:p:"
#include <inttypes.h>
#include <math.h>
#include <stdint.h>

int dig_count(uint32_t n) {
    int count = 0;
    do {
        n /= 10;
        ++count;
    } while (n != 0);
    return count;
}

int main(int argc, char **argv) {
    //initial variables
    int opt = 0;
    Set sorts = set_empty();
    Stats *stats = &(Stats) { .moves = 0, .compares = 0 }; //initialize stats
    int size = 100;
    int seed = 13371453;
    int printed = 100;
    uint32_t *list;
    uint32_t *temp_list;
    uint32_t temp;
    char print_H[]
        = ("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\nUSAGE\n   "
           "./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n   -H              "
           "Display program help and usage.\n   -a              Enable all sorts.\n   -b           "
           "   Enable Batcher Sort.\n   -h              Enable Heap Sort.\n   -q              "
           "Enable Quick Sort.\n   -s              Enable Shell Sort.\n   -n length       Specify "
           "number of array elements (default: 100).\n   -p elements     Specify number of "
           "elements to print (default: 100).\n   -r seed         Specify random seed (default: "
           "13371453).");

    while ((opt = (getopt(argc, argv, OPTIONS))) != -1) { //command line args, inserting into set
        switch (opt) {
        case 'a':
            sorts = set_insert(sorts, 0);
            sorts = set_insert(sorts, 1);
            sorts = set_insert(sorts, 2);
            sorts = set_insert(sorts, 3);
            break;
        case 's':
            if (!set_member(sorts, 0))
                sorts = set_insert(sorts, 0);
            break;
        case 'b':
            if (!set_member(sorts, 1))
                sorts = set_insert(sorts, 1);
            break;
        case 'q':
            if (!set_member(sorts, 2))
                sorts = set_insert(sorts, 2);
            break;
        case 'h':
            if (!set_member(sorts, 3))
                sorts = set_insert(sorts, 3);
            break;
        case 'r':
            temp = (uint32_t) strtol(optarg, (char **) NULL, 10);
            seed = temp;
            break;
        case 'n':
            temp = (int) strtol(optarg, (char **) NULL, 10);
            size = temp;
            break;
        case 'p':
            temp = (int) strtol(optarg, (char **) NULL, 10);
            printed = temp;
            break;
        case 'H': printf("%s\n", print_H); return 1;
        default: printf("%s\n", print_H); return 1;
        }
    }

    //memalloc of sorting lists
    list = (uint32_t *) calloc(size, sizeof(uint32_t));
    temp_list = (uint32_t *) calloc(size, sizeof(uint32_t));
    srand(seed);
    for (int i = 0; i < size; i++) {
        temp = rand() & 0x3FFFFFFF;
        list[i] = temp;
    }
    for (int i = 0; i < size; i++)
        temp_list[i] = list[i]; //copying list

    //shell sort
    if (set_member(sorts, 0)) {
        shell_sort(stats, temp_list, size);
        printf("Shell Sort, %i elements, %lu moves, %lu compares\n", size, stats->moves,
            stats->compares);
        if (printed > size)
            printed = size;
        for (int i = 0; i < printed; i++) { //stats printing
            int count = dig_count(temp_list[i]);
            for (int j = 0; j < 13 - count; j++)
                printf(" ");
            printf("%u", temp_list[i]);
            if (i != 0 && (i + 1) % 5 == 0)
                printf("\n");
        }
        for (int i = 0; i < size; i++)
            temp_list[i] = list[i];
    }
    reset(stats);

    //batcher sort
    if (set_member(sorts, 1)) {
        batcher_sort(stats, temp_list, size);
        printf("Batcher Sort, %i elements, %lu moves, %lu compares\n", size, stats->moves,
            stats->compares);
        if (printed > size)
            printed = size;
        for (int i = 0; i < printed; i++) { //stats printing
            int count = dig_count(temp_list[i]);
            for (int j = 0; j < (13 - count); j++)
                printf(" ");
            printf("%u", temp_list[i]);
            if (i != 0 && (i + 1) % 5 == 0)
                printf("\n");
        }
        for (int i = 0; i < size; i++)
            temp_list[i] = list[i];
    }
    reset(stats);

    //quick sort
    if (set_member(sorts, 2)) {
        quick_sort(stats, temp_list, size);
        printf("Quick Sort, %i elements, %lu moves, %lu compares\n", size, stats->moves,
            stats->compares);
        if (printed > size)
            printed = size;
        for (int i = 0; i < printed; i++) { //stats printing
            int count = dig_count(temp_list[i]);
            for (int j = 0; j < 13 - count; j++)
                printf(" ");
            printf("%u", temp_list[i]);
            if (i != 0 && (i + 1) % 5 == 0)
                printf("\n");
        }
        for (int i = 0; i < size; i++)
            temp_list[i] = list[i];
    }
    reset(stats);

    //heap sort
    if (set_member(sorts, 3)) {
        heap_sort(stats, temp_list, size);
        printf("Heap Sort, %i elements, %lu moves, %lu compares\n", size, stats->moves,
            stats->compares);
        if (printed > size)
            printed = size;
        for (int i = 0; i < printed; i++) { //stats printing
            int count = dig_count(temp_list[i]);
            for (int j = 0; j < 13 - count; j++)
                printf(" ");
            printf("%u", temp_list[i]);
            if (i != 0 && (i + 1) % 5 == 0)
                printf("\n");
        }
        for (int i = 0; i < size; i++)
            temp_list[i] = list[i];
    }
    reset(stats);

    //freeing memory
    free(list);
    free(temp_list);
    return 0;
}
