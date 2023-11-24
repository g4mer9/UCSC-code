/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa1
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

int main(int argc, char* argv[]){

    List A = newList();
    List B = newList();
    List C = newList();
    List D = NULL;

    for(int i = 1; i <= 20; i++) { //testing append/prepend and printing
        append(A,i);
        prepend(B,i);
    }
    append(C, 1);
    printList(stdout,A);
    printf("\n");
    printList(stdout,B);
    printf("\n");
    printList(stdout,C);
    printf("\n");

    moveFront(A); //testing iteration and get()
    while(index(A) >= 0){
        printf("%d ", get(A));
        moveNext(A);
    }
    printf("\n");

    moveBack(B);
    while(index(B) >= 0){
        printf("%d ", get(B));
        movePrev(B);
    }
    printf("\n");

    moveFront(C); //testing out of bounds
    moveNext(C);
    assert(C->index == -1);

    D = copyList(A);//testing copyList() and equals()
    printf("%s\n", equals(A,B)?"true":"false");
    printf("%s\n", equals(B,D)?"true":"false");
    printf("%s\n", equals(D,A)?"true":"false");


    moveFront(A); //testing insert before/after and delete()
    for(int i = 0; i < 5; i++) moveNext(A); // at index 5
    insertBefore(A, -1);
    for(int i = 0; i < 9; i++) moveNext(A); // at index 15
    insertAfter(A, -2);
    for(int i = 0; i < 5; i++) movePrev(A); // at index 10
    delete(A);
    printList(stdout,A);
    printf("\n");

    //testing delete front and back
    deleteFront(A);
    deleteBack(A);
    printList(stdout, A);
    printf("\n");

    printf("%d\n", length(A)); //testing clear
    clear(A);
    printf("%d\n", length(A));

    //testing frees
    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);

    return(0);
}

/*
Output of this program should be:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19
19
0
*/
