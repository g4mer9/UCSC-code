/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa4
 */

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    char *fileerr = "There was a problem opening the file.\n";

    if (argc != 3) {
        printf("Sparce needs exactly two arguments: ./Sparce <input file> <output file>\n");
        return 1;
    }

    char *inputFile = argv[1];
    char *outputFile = argv[2];

    input = fopen(inputFile, "r");
    output = fopen(outputFile, "w+");

    if (input == NULL || output == NULL) {
        printf("%s\n", fileerr);
        return 1;
    }

    int n, a, b, row, col;
    double value;
    fscanf(input, "%d %d %d", &n, &a, &b);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);


    for (int i = 0; i < a; i++) {
        fscanf(input, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    for (int i = 0; i < b; i++) {
        fscanf(input, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    fprintf(output, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(output, A);

    fprintf(output, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(output, B);

    Matrix C = scalarMult(1.5, A);
    fprintf(output, "\n(1.5)*A =\n");
    printMatrix(output, C);

    Matrix D = sum(A, B);
    fprintf(output, "\nA+B =\n");
    printMatrix(output, D);

    Matrix E = sum(A, A);
    fprintf(output, "\nA+A =\n");
    printMatrix(output, E);

    Matrix F = diff(B, A);
    fprintf(output, "\nB-A =\n");
    printMatrix(output, F);

    Matrix G = diff(A, A);
    fprintf(output, "\nA-A =\n");
    printMatrix(output, G);

    Matrix H = transpose(A);
    fprintf(output, "\nTranspose(A) =\n");
    printMatrix(output, H);

    Matrix I = product(A, B);
    fprintf(output, "\nA*B =\n");
    printMatrix(output, I);

    Matrix J = product(B, B);
    fprintf(output, "\nB*B =\n");
    printMatrix(output, J);

    fprintf(output, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

    fclose(input);
    fclose(output);
    return 0;
}