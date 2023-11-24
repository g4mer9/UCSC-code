/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa5
 */

#include <iostream>
#include <stdexcept>
#include "List.h"
using namespace std;

//CONST/DEST------------------------------------------------------------------------------------------------------------

//priv node constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr, prev = nullptr;
}

//class constructor/destructor

List::List() {
    frontDummy = new Node(-1);
    backDummy = new Node(-1);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    num_elements = 0;
    pos_cursor = 0;
}

//copy
List::List(const List& L) {
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;

    Node* N = L.frontDummy->next; //start at front
    while(N != L.backDummy) {
        this->insertAfter(N->data);//insert into new list until end of list
        this->moveNext();
        N = N->next;
    }
}

//destructor
List::~List() {
    this->clear();
    delete this->frontDummy;
    delete this->backDummy;
}

//ACCESS FUNCTIONS------------------------------------------------------------------------------------------------------

//len
int List::length() const {
    return this->num_elements;
}

//front->data, pre: len > 0
ListElement List::front() const {
    if( length()==0 ){
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

//back->data, pre: len > 0
ListElement List::back() const {
    if( length()==0 ){
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;
}

//pos
int List::position() const {
    return pos_cursor;
}

//cursor->next->data, pre: position()<length()
ListElement List::peekNext() const {
    if( position() >= length() ){
        throw std::range_error("List: peekNext(): position() >= length()");
    }
    return afterCursor->data;
}

//cursor->next->data, pre: pre: position()>0
ListElement List::peekPrev() const {
    if( position() <= 0 ){
        throw std::range_error("List: peekNPrev(): position() <= 0");
    }
    return beforeCursor->data;
}

//MANIPULATION FUNCTIONS------------------------------------------------------------------------------------------------

//make list empty
void List::clear() {
    if(length() != 0) {
        moveFront();
        while (length() > 0 and position() < length()) {
            eraseAfter();
        }
    }
}

//move cursor to front and set index to 0
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

//move cursor to back adn set index to length()
void List::moveBack() {
    pos_cursor = length();
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

//moves cursor to the right and returns value passed over
//pre: position()<length()
ListElement List::moveNext() {
    if( position() >= length() ){
        throw std::range_error("List: moveNext(): position() >= length()");
    }
    pos_cursor++;

    beforeCursor = afterCursor;
    afterCursor = beforeCursor->next;
    return beforeCursor->data;
}

//moves cursor to left and returns value passed over
//pre: position()>0
ListElement List::movePrev() {
    if( position() <= 0) {
        throw std::range_error("List: movePrev(): position() <= 0");
    }
    pos_cursor--;

    afterCursor = beforeCursor;
    beforeCursor = afterCursor->prev;
    return afterCursor->data;
}

//inserts x after cursor
void List::insertAfter(ListElement x) {
    Node * N = new Node(x);
    beforeCursor->next = N;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    N->next = afterCursor;
    afterCursor = N;
    num_elements++;
}

//inserts x before cursor.
void List::insertBefore(ListElement x) {
    insertAfter(x);
    moveNext();
}

//overwrites the data in the node after the cursor
//pre: position()<length()
void List::setAfter(ListElement x) {
    if( position() >= length() ){
        throw std::range_error("List: setAfter(): position() >= length()");
    }
    afterCursor->data = x;
}

//overwrites the data in the node after the cursor
//pre: position()>0
void List::setBefore(ListElement x) {
    if( position() <= 0) {
        throw std::range_error("List: setBefore(): position() <= 0");
    }
    beforeCursor->data = x;
}

//deletes element after cursor
//pre: position()<length()
void List::eraseAfter() {
    if( position() >= length() ){
        throw std::range_error("List: eraseAfter(): position() >= length()");
    }
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    delete afterCursor;
    afterCursor = beforeCursor->next;
    num_elements--;
}

//deletes element before cursor
//pre: position()>0
void List::eraseBefore() {
    if( position() <= 0) {
        throw std::range_error("List: setBefore(): position() <= 0");
    }
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    delete beforeCursor;
    beforeCursor = afterCursor->prev;
    pos_cursor--;
    num_elements--;
}

//OTHER FUNCTIONS-------------------------------------------------------------------------------------------------------
//linear search for x in List (->) left to right, returns index of cursor (after element) after found, -1 otherwise
int List::findNext(ListElement x) {
    while (position() < length()) {
        if (afterCursor->data == x) {
            moveNext();
            return position();
        }
        else moveNext();
    }
    return -1;
}

//linear search for x in List (<-) right to left, returns index of cursor (before element) after found, -1 otherwise
int List::findPrev(ListElement x) {
    while (position() > 0) {
        if (beforeCursor->data == x) {
            movePrev();
            return position();
        }
        else movePrev();
    }
    return -1;
}

//removes any repeated elements
void List::cleanup() {
    List * L = new List();
    Node * N = this->frontDummy->next;
    int i = 0;
    while(N != this->backDummy and (i+1 <= num_elements)) {
        L->moveFront();
        if(L->findNext(N->data) == -1) { //unique element found in original list
            L->insertAfter(N->data);
        }
        else { //non unique element found in original list
            if(N == afterCursor) {
                N = N->prev;
                i--;
                eraseAfter();
            }
            else if(N == beforeCursor) {
                N = N->prev;
                i--;
                eraseBefore();
            }
            else {
                if (i < position()) pos_cursor--;
                Node * temp = N->next;
                N->next->prev = N->prev;
                N->prev->next = temp;
                delete N;
                num_elements--;
                N = temp->prev;
                i--;
            }
        }
        N = N->next;
        i++;
    }
    delete L;
}

//returns new list that combines source class and L, with its cursor in pos 0
List List::concat(const List& L) const {
    List J;
    Node* M = this->frontDummy->next;
    while(M != this->backDummy) { //first list (this)
        J.insertAfter(M->data);
        J.moveNext();
        M = M->next;
    }

    Node* N = L.frontDummy->next;
    while(N != L.backDummy) {
        J.insertAfter(N->data);//second list (L)
        J.moveNext();
        N = N->next;
    }

    J.moveFront();
    return J;
}

//returns a string representation of this List consisting of a comma separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    Node *N = nullptr;
    std::string s = "";
    if(num_elements != 0) s = "(";

    for(N = frontDummy->next; N != backDummy; N = N->next) {
        if(N != backDummy->prev and N != backDummy) s += std::to_string(N->data) + ", ";
        else s += std::to_string(N->data) + ")";
    }

    return s;
}

//eq
bool List::equals(const List& R) const {
    if(this->length() == 0  or R.length() == 0) {
        if(this->length() == 0  and R.length() == 0) return true;
        else return false;
    }
    if(this->length() != R.length()) return false;

    bool eq = false;
    Node * N = nullptr;
    Node * M = nullptr;

    eq = (this->length() == R.length() );
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while (eq && N!= nullptr) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


//OVERRIDES-------------------------------------------------------------------------------------------------------------

//inserts to_string into stream
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

//returns true iff A and B are same integer sequence
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

//overwrites the state of this List with state of L
List& List::operator=( const List& L ) {
    if( this != &L) { //not 2 of the same pointers
        clear();
        Node* current = L.frontDummy->next;
        while(current != L.backDummy) {
            if(current->data != -1) {
                insertAfter(current->data);
            }
            current = current->next;
            moveNext();
        }
        pos_cursor = L.position();
        num_elements = L.length();
    }
    return *this;
}

