/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa7
 */
#include <iostream>
#include "Dictionary.h"

using namespace std;

int main() {
    std::string S[] =   {
            "7",
            "3",
            "4",
            "8",
            "9",
            "2",
            "1",
            "5"
    };
    std::string T[] =   {
            "7",
            "3",
            "2",
            "9"
    };

    Dictionary A;
    Dictionary B;

    for(int i=0; i<8; i++) {
        A.setValue(S[i], i+1);
    }

    B = A;

    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << "B.size() = " << B.size() << endl  << B << endl;

    Dictionary C = B;
    cout << "C.size() = " << C.size() << endl  << C << endl;

    for(int i=0; i<4; i++){
        cout << "removing " << T[i] << endl;
        A.remove(T[i]);
    }

    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << A.pre_string() << endl;
}

/**ideal output:
A.size() = 8
1 : 7
2 : 6
3 : 2
4 : 3
5 : 8
7 : 1
8 : 4
9 : 5

B.size() = 8
1 : 7
2 : 6
3 : 2
4 : 3
5 : 8
7 : 1
8 : 4
9 : 5

C.size() = 8
1 : 7
2 : 6
3 : 2
4 : 3
5 : 8
7 : 1
8 : 4
9 : 5

removing 7
removing 3
removing 2
removing 9
A.size() = 4
1 : 7
4 : 3
5 : 8
8 : 4

8
4
1
5

 */