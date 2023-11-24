/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa2
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
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
    freeList(&B);
    return 0;

}


/**
* desired output is below:
 * 1: 4
 * 2: 1
 * 3: 4
 * 4: 1 3
*/
