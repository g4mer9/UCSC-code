/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa4
 */


#pragma once
#include <stdio.h>
#include <stdbool.h>

//types
typedef struct NodeObj* Node;

typedef void* listData;

typedef struct ListObj{
    Node cursor;
    Node front;
    Node back;
    int index;
    int length;
} ListObj;

typedef struct ListObj* List;

//constructor/deconstructor
List newList(void);
void freeList(List* pL);//sets *pL to NULL.

//access functions
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
listData front(List L); // Returns front element of L. Pre: length()>0
listData back(List L); // Returns back element of L. Pre: length()>0
listData get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0

// manip functions
void clear(List L); // Resets L to its original empty state.
void set(List L, listData x); // Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void moveFront(List L); // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void movePrev(List L); // If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L); // If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void prepend(List L, listData x); // Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void append(List L, listData x); // Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void insertBefore(List L, listData x); // Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, listData x); // Insert new element after cursor.
// Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
