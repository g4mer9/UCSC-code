/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa6
 */

#include <iostream>
#include "List.h"

using namespace std;
int main() {
    int n = 25;
    List A, B;

    for(int i = 1; i <= n; i++) {
        A.insertAfter(i);
        B.insertBefore(i);
    }

    cout << endl;
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;

    A.moveBack();
    B.moveFront();

    cout << "A: " << A << endl;
    cout << "A.position(): " << A.position() << endl;
    cout << "B: " << B << endl;
    cout << "B.position(): " << B.position() << endl;

    cout << endl << "A: ";
    for(int i = 1; i <= 7; i++){
        cout << A.movePrev() << " ";
    }
    cout << endl << "A.position(): " << A.position() << endl;

    cout << endl << "B: ";
    for(int i = 1; i <= 7; i++){
        cout << B.moveNext() << " ";
    }
    cout << endl << "B.position(): " << B.position() << endl;

    cout << endl;
    cout << "A==B:  " << (A==B?"true":"false") << endl;

    cout << A.findNext(5) << endl;
    A.eraseBefore();
    A.eraseAfter();
    cout << A.position() << endl;
    cout << A << endl;
    cout << B << endl;

    List C = A.concat(B);
    cout << endl << C << endl;

    List D;
    D.insertBefore(1);
    D.insertBefore(2);
    D.insertBefore(2);
    D.insertBefore(1);
    D.insertBefore(2);
    D.insertBefore(3);
    D.insertBefore(1);
    D.movePrev();
    D.movePrev();
    cout << endl << D << endl;
    D.cleanup();
    cout << endl << D << endl;

    return 0;
}
/**ideal output below:

A: (25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
B: (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25)
A: (25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
A.position(): 25
B: (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25)
B.position(): 0

A: 1 2 3 4 5 6 7
A.position(): 18

B: 1 2 3 4 5 6 7
B.position(): 7

A==B:  false
21
20
(25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 3, 2, 1)
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25)

(25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25)

(1, 2, 2, 1, 2, 3, 1)

(1, 2, 3)
 */