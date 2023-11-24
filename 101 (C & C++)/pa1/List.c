/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa1
 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

//types--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct NodeObj{
    listData data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

//constructors/deconstructors----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//mallocs new node and returns pointer
Node create_node(listData x) {
    Node new = malloc(sizeof(NodeObj));
    assert(new != NULL);
    new->data = x;
    new->prev = NULL, new->next = NULL;
    return new;
}

//frees nodeobj and nulls pointer
void delete_node(Node* pL) {
    if(pL != NULL && (*pL) != NULL) {
        free(*pL);
        *pL = NULL;
    }
}

//mallocs new list and returns itself
List newList(void){
    List new = malloc(sizeof(ListObj));
    assert(new != NULL);
    new->front = NULL, new->back = NULL, new->cursor = NULL;
    new->length = 0;
    new->index = -1;
    return new;
}

//frees list and nulls pointer
void freeList(List* pL){
    clear(*pL);
    free(*pL);
    *pL = NULL;
}

//access functions------------------------------------------------------------------------------------

//returns length if list exists
int length(List L) {
    if(L == NULL ){
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

//returns index of cursor if defined, -1 otherwise
int index(List L) {
    if(L == NULL) {
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

//returns data from front (0th) index of list if it exists and length > 0
listData front(List L){
    if( L==NULL ){
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling front() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

listData back(List L){
    if( L==NULL ){
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling back() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    listData d = L->back->data;
    return d;
}

listData get(List L){
    if( L==NULL ){
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling get() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling get() on List with index of -1\n");
        exit(EXIT_FAILURE);
    }
    return (L->cursor)->data;
}

bool equals(List A, List B){
    if(A->length != B->length) return 0; //false if different sizes
    if(A->length == 0) return 1; //if both are empty, return true

    int prev_indexA = A->index; //storing initial cursors and resetting to front
    int prev_indexB = B->index;
    moveFront(A);
    moveFront(B);

    while(A->index != -1){ //while cursor is defined (becomes undefined when moveNext reaches bounds)
        if((A->cursor)->data != (B->cursor)->data) {
            A->index = prev_indexA;
            B->index = prev_indexB;
            return 0;
        }
        moveNext(A);
        moveNext(B);
    }
    return 1;
}

//manip functions---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void clear(List L) {
    while(L->front != NULL) { //while front is defined, delete it. when there are no more elements it will become undefined
        deleteFront(L);
    }
}

//sets cursor node's data to x if length > 0
void set(List L, listData x) {
    if( L==NULL ){
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling set() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling set() on List with index of -1\n");
        exit(EXIT_FAILURE);
    }

    (L->cursor)->data = x; // sets cursor's node data to x
}

//if L is non-empty, set cursor to front
void moveFront(List L) {
    if(L->length == 0) return; //if L is empty, do nothing
    L->cursor = L->front; //set cursor to front
    L->index = 0;
}

//if L is non-empty, set cursor to back
void moveBack(List L) {
    if(L->length == 0) return; //if L is empty, do nothing
    L->cursor = L->back; //set cursor to back
    L->index = L->length - 1;
}

//if cursor is not at front, move 1 towards front. if at front, cursor becomes undefined.
void movePrev(List L) {
    if(L->cursor == NULL) return; //if cursor is undefined, do nothing
    if(L->index > 0) {
        L->index--;
        L->cursor = L->cursor->prev; //move left if index is after front (> 0)
        return;
    }
    L->cursor = NULL;
    L->index = -1;
}

//if cursor is not at back, move 1 towards back. if at back, cursor becomes undefined.
void moveNext(List L){
    if(L->cursor == NULL) return; //if cursor is undefined, do nothing
    if(L->index < (L->length - 1)) {
        L->index++;
        L->cursor = L->cursor->next; //move right if index is before back (< len - 1)
        return;
    }
    L->cursor = NULL;
    L->index = -1;
}

//prepend new node to front/beginning of list
void prepend(List L, listData x) {
    if(L->length == 0) { //creating first node if list is empty
        Node new = create_node(x);
        L->front = new, L->back = new; //sets pointers to front and back of list
        L->length++;
        return;
    }

    Node new = create_node(x); //creating node
    (L->front)->prev = new;
    new->next = (L->front);//setting next and prev pointers
    L->front = new; //setting node as the new front
    L->length++;
    if(L->index != -1) L->index++; //if cursor is defined, add to index since new node is before it
}

//append new node to back/end of list
void append(List L, listData x) {

    if(L->length == 0) { //creating first node if list is empty
        Node new = create_node(x);
        L->front = new, L->back = new; //sets pointers to front and back of list
        L->length++;
        return;
    }

    Node new = create_node(x); //creating node
    (L->back)->next = new;
    new->prev = (L->back);//setting next and prev pointers
    L->back = new; //setting node as the new back
    L->length++;
}

//insert new node before cursor
void insertBefore(List L, listData x) {
    if( L==NULL ){
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling insertBefore() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling insertBefore() on List with index of -1\n");
        exit(EXIT_FAILURE);
    }

    if(L->index == 0) {
        prepend(L, x); //if cursor is start of list, prepend
        return;
    }

    //else, update the directional pointers of new node, cursor, and cursor->prev
    Node new = create_node(x); //creating node

    //with example n1, n2, n3 | n1, n4, n2, n3
    //with cursor on n2 and new node as n4

    L->cursor->prev->next = new; //n1's next is set to n4
    new->prev = L->cursor->prev; //n4's prev is set to n1
    L->cursor->prev = new; //n2's prev is set to n4
    new->next = L->cursor;//n4's next is set to n2

    L->length++;
    L->index++; //since new node is placed before cursor
}

//insert new node after cursor
void insertAfter(List L, listData x) {
    if( L==NULL ){
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling insertAfter() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling insertAfter() on List with index of -1\n");
        exit(EXIT_FAILURE);
    }

    if(L->index == L->length - 1) {
        append(L, x); //if cursor is end of list, append
        return;
    }

    //else, update the directional pointers of new node, cursor, and cursor->next
    Node new = create_node(x); //creating node

    //with example n1, n2, n3 | n1, n2, n4, n3
    //with cursor on n2 and new node as n4

    L->cursor->next->prev = new; //n3's prev is set to n4
    new->next = L->cursor->next; //n4's next is set to n3
    L->cursor->next = new; //n2's next is set to n4
    new->prev = L->cursor;//n4's prev is set to n2

    L->length++;
}

void deleteFront(List L) {
    if( L==NULL ){
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling deleteFront() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index == 0) {
        //L->index = -1; //making cursor undefined if it's being deleted
        L->cursor = NULL;
    }
    if(L->length == 1) {
        delete_node(&L->front);
        L->front = NULL, L->back = NULL;
        L->length = 0;
        return;
    }
    Node temp = L->front->next;
    delete_node(&L->front);
    L->front = temp;
    L->front->prev = NULL;
    L->length--;
    if(L->index != -1) L->index--;//if index is 0, makes undefined = -1, else lowers index of cursor since object left of it has been deleted
}

void deleteBack(List L) {
    if( L==NULL ){
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling deleteBack() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index == L->length - 1) {
        L->index = -1; //making cursor undefined if it's being deleted
        L->cursor = NULL;
    }
    if(L->length == 1) {
        delete_node(&L->front);
        L->front = NULL, L->back = NULL;
        L->length = 0;
        return;
    }
    Node temp = L->back->prev;
    delete_node(&L->back);
    L->back = temp;
    (L->back)->next = NULL; //setting new back's next to null
    L->length--;
}

void delete(List L) {
    if( L==NULL ){
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling delete() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling delete() on List with index of -1\n");
        exit(EXIT_FAILURE);
    }
    if(L->index == 0) {
        deleteFront(L);
        return;
    }
    if(L->index == L->length - 1) {
        deleteBack(L);
        return;
    }

    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev; //making cursor's two neighbors point to each other

    delete_node(&L->cursor);

    L->length = L->length - 1;
    L->index = -1; //making cursor undefined since it's being deleted
}

//other operations----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printList(FILE* out, List L) {
    if( L==NULL ){
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length <= 0){
        fprintf(stderr, "List Error: calling printList() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    int prev_index = L->index;
    moveFront(L); //setting temporary cursor

    while (L->index != -1) {
        fprintf(out, "%i ", (L->cursor)->data); //print data in space seperated statements and moveNext
        moveNext(L);
    }
    L->index = prev_index;
}

List copyList(List L) {
    List M = newList();
    int prev_index = L->index;
    moveFront(L); //setting temporary cursor

    while (L->index != -1) {
        append(M, (L->cursor)->data); //iterate over original list and append to new list with old data
        moveNext(L);
    }

    L->index = prev_index;
    return M;
}

//wow 400 lines
