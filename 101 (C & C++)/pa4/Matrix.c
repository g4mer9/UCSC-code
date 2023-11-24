/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa4
 */
#include <stdlib.h>
#include <math.h>
#include "Matrix.h"
#include "List.h"


//matrix entry definition

typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

//matrix struct definition
typedef struct MatrixObj {
    int size;           // dimension of square matrix
    int nnz;            // number of non-zero elements
    List* rows;         // array of lists of entries (one for each row)
} MatrixObj;

//helper function for dot product
double vectorDot(List P, List Q) {
    double dot = 0.0;
    moveFront(P);
    moveFront(Q);
    while (index(P) != -1 && index(Q) != -1) {
        Entry e1 = (Entry) get(P);
        Entry e2 = (Entry) get(Q);
        if (e1->col < e2->col) {
            moveNext(P);
        } else if (e1->col > e2->col) {
            moveNext(Q);
        } else {
            dot += e1->val * e2->val;
            moveNext(P);
            moveNext(Q);
        }
    }
    return dot;
}

//returns new nxn Matrix in 0 state
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->nnz = 0;
    M->rows = malloc((n + 1) * sizeof(List));
    for (int i = 1; i <= n; i++) {
        M->rows[i] = newList();
    }
    return M;
}

//frees pM and sets to null
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 1; i <= (*pM)->size; i++) {
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}

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

//returns size of M
int size(Matrix M) {
    return M->size;
}

//returns number of non zero elements in M
int NNZ(Matrix M) {
    return M->nnz;
}

//returns 1 if A=B, else 0
int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL || size(A) != size(B)) return 0; //not equal if null or diff sizes

    if(NNZ(A) != NNZ(B)) {
        return 0; // false if different element count
    }

    if (A == B) {
        return 1; //equal if the same pointer
    }

    for (int i = 1; i <= size(A); i++) {
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        while (A->rows[i]->index != -1 && B->rows[i]->index != -1) {
            if (fabs(((Entry) get(A->rows[i]))->val - ((Entry) get(B->rows[i]))->val) > 0.0001) {
                return 0; //false if current List entries being checked aren't equal
            }
            moveNext(A->rows[i]);
            moveNext(B->rows[i]);
        }
        if (A->rows[i]->index != B->rows[i]->index && length(A->rows[i]) != 0) {
            return 0; //false if either has an element not in the other
        }
    }
    return 1;
}

//reset matrix to all 0's
void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= size(M); i++) {
        clear(M->rows[i]);
    }
    M->nnz = 0;
}

//change entry specified by coordinates
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > size(M) || j < 1 || j > size(M)) {
        fprintf(stderr, "Matrix Error: calling changeEntry() with out of bounds indices\n");
        exit(EXIT_FAILURE);
    }
    Entry E = newEntry(j, x);
    if (x != 0) {//inserting non zero element
        if(M->rows[i]->length == 0) { //if empty row, append and return
            append(M->rows[i], E);
            M->nnz++;
            return;
        }
        moveFront(M->rows[i]);
        Entry curr = get(M->rows[i]);
        while (M->rows[i]->index < (length(M->rows[i]) - 1) && curr->col < j) {//indexing to replacement spot
            moveNext(M->rows[i]);
            curr = get(M->rows[i]);
        }
        if (M->rows[i]->index == (length(M->rows[i]) - 1) && curr->col < j) { //if indexed out of bounds so everything to the right of the last element in the list is a 0
            append(M->rows[i], E);
            M->nnz++;
            return;
        }
        if(curr->col > j) {
            insertBefore(M->rows[i], E);
            M->nnz++;
            return;
        }
        else { // curr->col == j, therefore curr is the node to be replaced
            curr->val = x;
        }
    }
    else if(M->rows[i]->length != 0) {//inserting 0 element if there is any nnz in the row
        moveFront(M->rows[i]);
        Entry curr = get(M->rows[i]);
        while (M->rows[i]->index < (length(M->rows[i]) - 1) && curr->col < j) {//indexing to replacement spot
            moveNext(M->rows[i]);
            curr = get(M->rows[i]);
        }
        if (curr->col == j) {
            delete(M->rows[i]);
            M->nnz--;
        }
    }
    freeEntry(&E);
}

//matrix copier
Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix M = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        for(moveFront(A->rows[i]); index(A->rows[i]) != -1; moveNext(A->rows[i])){
            append(M->rows[i], ((Entry) get(A->rows[i])));
        }
    }
    M->nnz = A->nnz;
    return M;
}

//returns the transpose of A
Matrix transpose(Matrix A) {
    Matrix B = newMatrix(size(A));

    for (int i = 1; i <= size(A); i++) {
        List row = A->rows[i];
        for (moveFront(row); index(row) >= 0; moveNext(row)) {
            int j = ((Entry) get(row))->col;
            double x = ((Entry) get(row))->val;
            changeEntry(B, j, i, x);
        }
    }
    return B;
}

//returns x * A
Matrix scalarMult(double x, Matrix A) {
    int n = size(A);
    Matrix B = newMatrix(n);

    for (int i = 1; i <= n; i++) {
        List row = A->rows[i];
        for (moveFront(row); index(row) >= 0; moveNext(row)) {
            int j = ((Entry) get(row))->col;
            double y = x * ((Entry) get(row))->val;
            changeEntry(B, i, j, y);
        }
    }

    return B;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: sum() called with matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }

    int n = size(A);
    Matrix C = newMatrix(n);

    if(A == B) { //if summing itself
        for (int i = 1; i <= n; i++) {
            List rowA = A->rows[i];
            moveFront(rowA);
            while (index(rowA) >= 0) {
                int jA = ((Entry) get(rowA))->col;
                double x = ((((Entry) get(rowA))->val) * 2);
                changeEntry(C, i, jA, x);
                moveNext(rowA);
            }
        }
    }
    else {//A and B are different matrices
        for (int i = 1; i <= n; i++) {
            List rowA = A->rows[i];
            List rowB = B->rows[i];
            moveFront(rowA);
            moveFront(rowB);
            while (index(rowA) >= 0 && index(rowB) >= 0) {
                int jA = ((Entry) get(rowA))->col;
                int jB = ((Entry) get(rowB))->col;

                if (jA == jB) {
                    double x = ((Entry) get(rowA))->val + ((Entry) get(rowB))->val;
                    changeEntry(C, i, jA, x);
                    moveNext(rowA);
                    moveNext(rowB);
                } else if (jA < jB) {
                    double x = ((Entry) get(rowA))->val;
                    changeEntry(C, i, jA, x);
                    moveNext(rowA);
                } else {
                    double x = ((Entry) get(rowB))->val;
                    changeEntry(C, i, jB, x);
                    moveNext(rowB);
                }
            }

            while (index(rowA) >= 0) {
                int jA = ((Entry) get(rowA))->col;
                double x = ((Entry) get(rowA))->val;
                changeEntry(C, i, jA, x);
                moveNext(rowA);
            }

            while (index(rowB) >= 0) {
                int jB = ((Entry) get(rowB))->col;
                double x = ((Entry) get(rowB))->val;
                changeEntry(C, i, jB, x);
                moveNext(rowB);
            }
        }
    }

    return C;
}

Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix Error: calling diff() on matrices of different sizes.\n");
        exit(1);
    }

    Matrix C = newMatrix(size(A));
    int n = size(A);
    if(A == B) return C;
    else {//A and B are different matrices
        for (int i = 1; i <= n; i++) {
            List rowA = A->rows[i];
            List rowB = B->rows[i];
            moveFront(rowA);
            moveFront(rowB);
            while (index(rowA) >= 0 && index(rowB) >= 0) {
                int jA = ((Entry) get(rowA))->col;
                int jB = ((Entry) get(rowB))->col;
                if (jA == jB) {
                    double x = ((Entry) get(rowA))->val - ((Entry) get(rowB))->val;
                    changeEntry(C, i, jA, x);
                    moveNext(rowA);
                    moveNext(rowB);
                } else if (jA < jB) {
                    double x = ((Entry) get(rowA))->val;
                    changeEntry(C, i, jA, x);
                    moveNext(rowA);
                } else {
                    double x = ((Entry) get(rowB))->val;
                    changeEntry(C, i, jB, -x);
                    moveNext(rowB);
                }
            }

            while (index(rowA) >= 0) {
                int jA = ((Entry) get(rowA))->col;
                double x = ((Entry) get(rowA))->val;
                changeEntry(C, i, jA, x);
                moveNext(rowA);
            }

            while (index(rowB) >= 0) {
                int jB = ((Entry) get(rowB))->col;
                double x = ((Entry) get(rowB))->val;
                changeEntry(C, i, jB, -x);
                moveNext(rowB);
            }
        }
    }
    return C;
}

Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix Error: calling product() on matrices of different sizes.\n");
        exit(1);
    }

    Matrix C = newMatrix(size(A));
    Matrix BT = transpose(B);
    for (int i = 1; i <= size(A); i++) {
        if (length(A->rows[i]) == 0) {
            continue;
        }
        for (int j = 1; j <= size(A); j++) {
            if (length(BT->rows[j]) == 0) {
                continue;
            }
            double dotProduct = vectorDot(A->rows[i], BT->rows[j]);
            if (dotProduct != 0) {
                changeEntry(C, i, j, dotProduct);
            }
        }
    }
    freeMatrix(&BT);
    return C;
}

void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= size(M); i++) {
        if (length(M->rows[i]) > 0) {
            fprintf(out, "%d: ", i);
            moveFront(M->rows[i]);
            while (index(M->rows[i]) != -1) {
                Entry curr = get(M->rows[i]);
                fprintf(out, "(%d, %.1f) ", curr->col, curr->val);
                moveNext(M->rows[i]);
            }
            fprintf(out, "\n");
        }
    }
}