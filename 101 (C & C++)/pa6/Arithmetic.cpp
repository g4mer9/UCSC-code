/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa6
 */
#include <iostream>
#include <fstream>
#include "BigInteger.h"

using namespace std;

int main (int argc, char **argv) {
    if (argc != 3) { //argument count
        std::cout << "Usage: Arithmetic <input file> <output file>" << endl;
        return 1;
    }
    fstream in (argv[1], fstream::in);
    fstream out (argv[2], fstream::out);

    //parse 3 lines from file, skipping 2nd
    std::string line;
    std::getline(in, line); //1st
    BigInteger A = BigInteger(line);
    std::getline(in, line); //2nd
    std::getline(in, line); //3rd
    BigInteger B = BigInteger(line);

    //print calculations
    out << A.to_string() << endl << endl;
    out << B.to_string() << endl << endl;
    out << (A+B).to_string() << endl << endl;
    out << (A-B).to_string() << endl << endl;
    out << (A-A).to_string() << endl << endl;
    BigInteger x = BigInteger("3");
    BigInteger y = BigInteger("2");
    out << ((x * A) - (y * B)).to_string() << endl << endl;
    out << (A * B).to_string() << endl << endl;
    out << (A * A).to_string() << endl << endl;
    out << (B * B).to_string() << endl << endl;
    x = BigInteger("9");
    y = BigInteger("16");
    BigInteger C = (x * (A*A*A*A)) + (y * (B*B*B*B*B));
    out << C.to_string() << endl;

    //close files
    in.close();
    out.close();
    return 0;
}