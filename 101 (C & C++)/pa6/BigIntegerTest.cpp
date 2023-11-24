/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa6
 */

/**
 * This test assumes that power is set to 2 and base is set to 100
 *
 */

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main() {
    //add tests

    string s1 = "4355797";
    string s2 = "149082";

    BigInteger A = BigInteger(s1);
    BigInteger B = BigInteger(s2);
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    BigInteger C = A+B;
    cout << "C = " << C << endl;

    s1 = "5";
    s2 = "785";

    A = BigInteger(s1);
    B = BigInteger(s2);
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    C = A+B;
    cout << "C = " << C << endl;

    s1 = "91287346670000043892345634563400005619187236478";
    s2 = "9876545439000000345634560000000002000034565430000000006543654365346534";

    A = BigInteger(s1);
    B = BigInteger(s2);
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    C = A+B;
    cout << "C = " << C << endl;

    //sub tests
    s1 = "4355797";
    s2 = "149082";

    A = BigInteger(s1);
    B = BigInteger(s2);
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    C = A-B;
    cout << "C = " << C << endl;

    s1 = "98765454390000034563456191872363456345619187236000456456345756780000065436543";
    s2 = "9876545439000000345634560000000002000034565430000000006543654365346534";

    A = BigInteger(s1);
    B = BigInteger(s2);
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    BigInteger D = A-B;
    cout << "D = " << D << endl;

    A = BigInteger("111122223333");
    B = BigInteger("111122223333");
    C = BigInteger();
    D = BigInteger("12348148518469129628889");

    // pos * pos = pos
    C = A * B;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;

    return 0;
}

/**
* Ideal output:
A = 4355797
B = 149082
C = 4504879
A = 5
B = 785
C = 790
A = 91287346670000043892345634563400005619187236478
B = 9876545439000000345634560000000002000034565430000000006543654365346534
C = 9876545439000000345634651287346672000078457775634563406549273552583012
A = 4355797
B = 149082
C = 4206715
A = 98765454390000034563456191872363456345619187236000456456345756780000065436543
B = 9876545439000000345634560000000002000034565430000000006543654365346534
D = -999901234555486545404436544153762196543654382812798564973543654249763654299909991
C = 12348148518469129628889
D = 12348148518469129628889
*/