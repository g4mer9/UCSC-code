/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa4
 */
#include <stdio.h>
#include "Matrix.h"

int main(int argc, char **argv) {
    Matrix A = newMatrix(100);
    Matrix B = newMatrix(100);
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 3, 1);
    changeEntry(B, 1, 1, 1);
    changeEntry(B, 1, 3, 1);
    if (!equals(A, B)) {
        printMatrix(stderr, A);
        printMatrix(stderr, B);
    }
    changeEntry(A, 1, 3, 0);
    if (equals(A, B)) {
        printMatrix(stderr, A);
        printMatrix(stderr, B);
    }
    return 0;
}