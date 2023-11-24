/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa7
 */
#include <iostream>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main (int argc, char **argv) {
    if (argc != 3) { //argument count
        std::cout << "Usage: Order <input file> <output file>" << endl;
        return 1;
    }
    fstream in(argv[1], fstream::in);
    fstream out(argv[2], fstream::out);

    Dictionary A;
    //parse file
    std::string line;
    valType linect = 1;
    while (std::getline(in, line)) { //populate dict
        keyType key = line;
        A.setValue(key, linect);
        linect++;
    }

    out << A.to_string() << endl;
    out << A.pre_string() << endl;

    in.close();
    out.close();
    return 0;
}
