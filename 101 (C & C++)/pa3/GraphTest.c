/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa3
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    /**PA2 Graph.c TESTS
    Graph A = newGraph(100);
    List B = newList();
    List L = newList();
    append(B, 3);
    append(B, 42);
    append(B, 2);
    append(B, 64);

    assert(getSize(A) == 0); //get size test
    addArc(A, 2, 1); //addarc test
    addEdge(A, 3, 4);//addedge test
    assert(getSize(A) == 2); //get size test
    addEdge(A, 1, 4);

    printGraph(stderr, A); //print graph test (desired output is below)
    assert(getOrder(A) == 100); // get order test

    BFS(A, 3);
    assert(getSource(A) == 3); //get source test
    assert(getParent(A, 4) == 3); //get parent test
    assert(getDist(A, 4) == 1); //get distance test

    makeNull(A);
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 3);

    getPath(L, A, 64);
    assert(equals(L, B)); //BFS/getpath test

    freeGraph(&A);
    freeList(&L);
    freeList(&B);*/
    Graph A = newGraph(6);
    List L = newList();

    assert(getOrder(A) == 6);
    for (int i = 1; i <= 6; i++)
        assert(getDiscover(A, i) == UNDEF);

    addArc(A, 1, 3);
    addArc(A, 1, 2);
    addArc(A, 1, 4);
    addArc(A, 2, 3);
    addArc(A, 3, 5);
    addArc(A, 4, 5);
    addArc(A, 5, 2);
    printGraph(stdout, A);
    printf("\n");

    for (int i = 1; i <= 6; i++) {
        append(L, i);
    }
    DFS(A, L);
    assert(getDiscover(A, 1) == 1);
    assert(getParent(A, 4) == 1);
    assert(getFinish(A, 5) == 5);
    Graph T = transpose(A);
    printGraph(stdout, T);
    printf("\n");
    freeList(&L);
    freeGraph(&A);
    freeGraph(&T);
    return 0;
}
/**
 * ideal output:
 * 1: 2 3 4
 * 2: 3
 * 3: 5
 * 4: 5
 * 5: 2
 * 6:
 *
 * 1:
 * 2: 1 5
 * 3: 1 2
 * 4: 1
 * 5: 3 4
 * 6:
 *
*/