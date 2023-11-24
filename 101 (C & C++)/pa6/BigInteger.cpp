/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa6
 */

#include <iostream>
#include <stdexcept>
#include "BigInteger.h"

using namespace std;

int power = 9;//set to 9
long base = 1000000000;//set to 1 bil

//CONST/DEST------------------------------------------------------------------------------------------------------------

BigInteger::BigInteger() { //empty constructor, list remains empty
    signum = 0;
}

BigInteger::BigInteger(long x) { //constructor for long x
    if ( x > 0 ) signum = 1;
    else if ( x < 0 ) {
        signum = -1;
        x = -x;
    }
    else signum = 0;
    while ( x > 0) {
        digits.insertAfter(x % base);
        x /= base;
    }
}

BigInteger::BigInteger(std::string s) { //constructor for string s
    if (s.empty()) {
        throw std::invalid_argument("Input string is empty.");
    }

    size_t start = 0;
    if (s[0] == '+') {
        start = 1;
        signum = 1;
    }
    else if (s[0] == '-') {
        start = 1;
        signum = -1;
    }
    else signum = 1;

    for (size_t i = start; i < s.length(); i++) {
        if(!isdigit(s[i])) {
            throw std::invalid_argument("Invalid character in input string.");
        }
    }

    if (start == 1) s.erase(0, 1); //erase sign if any
    while (s[0] == '0') s.erase(0, 1); //erase leading 0's if any

    while(s.length() > (unsigned int)(power)) { //insert last power elements of the string into the list, erase from string, and repeat
        std::string sub = s.substr((s.length() - (power)), (power));
        while (sub[0] == '0') sub.erase(0, 1); //erase leading 0's if any
        if(!sub.empty()) {
            long node = std::stol(sub, 0, 10);
            digits.insertAfter(node);
        }
        else {
            digits.insertAfter(0);
        }
        s.erase(s.length() - (power));
    }
    long node = std::stol(s, 0, 10);
    digits.insertAfter(node);
}



BigInteger::BigInteger(const BigInteger &N) { //copy constructor
    signum = N.signum;
    digits = N.digits;
}

//ACCESS FUNCTIONS------------------------------------------------------------------------------------------------------

int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    //if different signs
    if (signum < N.signum) return -1;
    else if (signum > N.signum) return 1;
    else { //same sign
        BigInteger thisCopy = *this;
        BigInteger copy = N; //copy

        thisCopy.digits.moveFront();
        copy.digits.moveFront();
        int i = 0;
        while (i < thisCopy.digits.length() and i < copy.digits.length()) {
            if (thisCopy.digits.peekNext() < copy.digits.peekNext()) return -signum;
            if (thisCopy.digits.peekNext() > copy.digits.peekNext()) return signum;
            thisCopy.digits.moveNext();
            copy.digits.moveNext();
            i++;
        }
        if (i < thisCopy.digits.length()) return signum;
        if (i < copy.digits.length()) return -signum;
        return 0; //nums are equal
    }
}

//MANIPULATION FUNCTIONS------------------------------------------------------------------------------------------------

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    if(signum != 0) signum = -signum;//only negate if it isn't 0
}

//ARITHMETIC FUNCTIONS--------------------------------------------------------------------------------------------------

BigInteger BigInteger::add(const BigInteger &N) const {
    //adding N or this to 0
    if (signum == 0) return N;
    else if (N.signum == 0) return *this;

    //determine smaller/bigger number
    BigInteger larger;
    BigInteger smaller;
    if (compare(N) == 1) {
        larger = *this;
        smaller = N;
    }
    else {
        larger = N;
        smaller = *this;
    }

    BigInteger result;
    if(larger.signum == smaller.signum) {
        result.signum = signum;
        long carry = 0;
        int smallerSize = smaller.digits.length();

        larger.digits.moveBack();
        smaller.digits.moveBack();
        int i = 0;
        while(larger.digits.position() > 0) {
            long sum = larger.digits.peekPrev() + carry; //larger element + carry
            if (i < smallerSize) sum += smaller.digits.peekPrev(); //if smaller node in range, add it
            result.digits.insertAfter(sum % base); //adding without carry
            carry = sum / base; //setting carry
            larger.digits.movePrev();
            if (i < smallerSize) smaller.digits.movePrev();
            i++;
        }

        if (carry > 0) result.digits.insertAfter(carry);
    }
    else if(signum == -1) { //-A + B -> B - A
        BigInteger tempB = N;
        tempB.negate();
        result = tempB.sub(*this);
    }
    else { //A + -B -> A - B
        BigInteger tempB = N;
        tempB.negate();
        result = sub(tempB);
    }
    return result;
}

BigInteger BigInteger::sub(const BigInteger &N) const {
    //subbing N or this by 0
    if (signum == 0) {
        BigInteger temp = N;
        temp.negate();
        return temp; //0 - N
    }
    else if (N.signum == 0) return *this; //this - 0

    //determine smaller/bigger number
    BigInteger larger;
    BigInteger smaller;
    BigInteger result;
    if (compare(N) == 1) {
        result.signum = 1; //sign of result will be sign of larger
        larger = *this;
        smaller = N;
    }
    else {
        result.signum = -1;//^
        larger = N;
        smaller = *this;
    }

    if(compare(N) == 0) return BigInteger(); // A - A
    if (larger.signum == smaller.signum) { //only compute if same sign
        int borrow = 0;
        int largerSize = larger.digits.length();
        int smallerSize = smaller.digits.length();

        larger.digits.moveBack();
        smaller.digits.moveBack();
        int i = 0;
        int j = 0;
        while (larger.digits.position() > 0 or smaller.digits.position() > 0){
            long diff = 0;
            if(compare(N) == 1){
                if (i < largerSize) diff += larger.digits.peekPrev() - borrow;
                if (j < smallerSize) diff -= smaller.digits.peekPrev();
                if (larger.signum == -1) diff = -diff;
                if (diff < 0) { //normalize
                    diff += base;
                    borrow = 1;
                }
                else borrow = 0;
            }
            else {
                if (j < smallerSize) diff += smaller.digits.peekPrev() + borrow;
                if (i < largerSize) diff -= larger.digits.peekPrev();
                if (larger.signum == -1) diff = -diff;
                if (diff > 0) { //normalize
                    diff -= base;
                    diff = -diff;
                    borrow = 1;
                }
                else {
                    diff = -diff;
                    borrow = 0;
                }
            }

            result.digits.insertAfter(diff);
            if (i < largerSize) larger.digits.movePrev();
            if (j < smallerSize) smaller.digits.movePrev();
            if (i <= largerSize) i++;
            if (j <= smallerSize) j++;
        }
    }
    else if (signum == -1){ //-A - B -> -A + -B
        BigInteger tempB = N;
        tempB.negate();
        result = tempB.add(*this);
    }
    else { //A - -B -> A + B
        BigInteger tempB = N;
        tempB.negate();
        result = add(tempB);
    }
    return result;
}

BigInteger BigInteger::mult(const BigInteger &N) const {
    BigInteger result;
    BigInteger temp;

    if(signum == 0 || N.signum == 0) return result; // if either are 0, return 0
    temp.signum = 1;

    //determine smaller/bigger number
    BigInteger larger;
    BigInteger smaller;
    if (compare(N)) {
        larger = *this;
        smaller = N;
    }
    else {
        larger = N;
        smaller = *this;
    }
    //mult
    long digit = 0;
    long carry = 0;
    smaller.digits.moveBack();
    int i = 0;
    while (smaller.digits.position() > 0) { //for i digits, then carry
        larger.digits.moveBack();
        temp.digits.clear();
        for (int k = 0; k < i; ++k) { //setting 0's in 2nd+ loops of multiplication
            temp.digits.insertAfter(0);
        }
        int j = 0;
        while (larger.digits.position() > 0 or carry != 0) { //for j digits, then carry
            digit = 0;
            if (j < larger.digits.length()) { //add larger digit if in range
                digit += larger.digits.peekPrev();
                larger.digits.movePrev();
                digit *= smaller.digits.peekPrev();
            }
            digit += carry;
            temp.digits.insertAfter(digit % (base)); //store result if first small node being multiplied
            carry = digit / (base); //update carry
            j++;
        }
        //throw std::invalid_argument(std::to_string(result.digits.length())
        result = result.add(temp); //add temp to result
        smaller.digits.movePrev();
        i++;
    }
    result.signum = signum * N.signum; //signum of result
    return result;
}
//OTHER FUNCTIONS-------------------------------------------------------------------------------------------------------

std::string BigInteger::to_string() {
    if (signum == 0) return "0";

    //make string and add negative symbol if necessary
    std::string print;
    if(signum == -1) print += "-";

    //append digits
    digits.moveFront();
    for (int i = 0; i < digits.length(); ++i) {
        std::string digit = "";
        if(i != 0) {
            int x = (power - std::to_string(digits.peekNext()).length());
            for (int j = 0; j < x; ++j) {
                digit += "0";
            }
        }
        digit += std::to_string(digits.peekNext());

        print += digit;
        digits.moveNext();
    }
    return print;
}

//OVERRIDES-------------------------------------------------------------------------------------------------------------

//sending tostring to filestream
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.to_string();
}

//returns true iff A=B
bool operator==( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == 0);
}

//returns true iff A<B
bool operator<( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == -1);
}

//returns true iff A<=B
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == -1 || A.compare(B) == 0);
}

//returns true iff A>B
bool operator>( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == 1);
}

//returns true iff A>=B
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) == 1 || A.compare(B) == 0);
}

//returns A+B
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

//sets A = A + B and returns A
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

//returns A-B
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

//sets A = A - B and returns A
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

//returns A*B
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

//sets A = A * B and returns A
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}
