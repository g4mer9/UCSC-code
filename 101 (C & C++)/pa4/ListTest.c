/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa4
 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

Entry newEntry(int col, double val) {
    Entry newEntry = (Entry) malloc(sizeof(EntryObj));
    if (newEntry != NULL) {
        newEntry->col = col;
        newEntry->val = val;
    }
    return newEntry;
}

void freeEntry(Entry* entryPtr) {
    if (entryPtr != NULL && *entryPtr != NULL) {
        free(*entryPtr);
        *entryPtr = NULL;
    }
}

int main(int argc, char* argv[]) {
    List A = newList();
    Entry e = newEntry(1, 1);
    Entry f = newEntry(1, 2);
    Entry g = newEntry(1, 3);
    append(A, e);
    append(A, f);
    append(A, g);

    moveFront(A);
    while(index(A) != -1) {
        fprintf(stderr, "%i\n", index(A));
        moveNext(A);
    }
    return 0;
}