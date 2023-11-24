/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa5
 */
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

using namespace std;

void shuffle(List& D) {
    int size = D.length();
    List left, right;

    int leftSize = size / 2;

    //create subsets
    D.moveFront();
    left.moveBack();
    right.moveBack();
    for (int  i = 0; i < leftSize; i++) {
        left.insertBefore(D.peekNext());
        D.moveNext();
    }
    for (int i = leftSize; i < size; i++) {
        right.insertBefore(D.peekNext());
        D.moveNext();
    }


    //perform shuffle
    D.clear();
    D.moveBack();
    right.moveFront();
    left.moveFront();
    for (int i = 0; i < leftSize; i++) {
        D.insertBefore(right.peekNext());
        right.moveNext();
        D.insertBefore(left.peekNext());
        left.moveNext();
    }

    if(size % 2 != 0) { //last element if odd size
        D.insertBefore(right.peekNext());
    }
}

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Shuffle needs exactly 1 argument: max deck size" << endl;
    }

    int size = std::stoi(argv[1]);
    std::cout << "deck size     shuffle count\n";
    std::cout << "------------------------------\n";

    List deck;
    List original;
    for (int n = 1; n <= size; n++) {
        deck.clear();
        for (int i = 0; i < n; i++) {
            deck.moveBack();
            deck.insertBefore(i);
        }

        original = deck;
        int shufflect = 0;

        do {
            shuffle(deck);
            shufflect++;
        } while (!(deck == original));

        std::cout << n << "     " << shufflect << endl;
    }
    return 0;
}