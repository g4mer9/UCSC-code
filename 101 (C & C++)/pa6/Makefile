#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Arithmetic
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Arithmetic
#------------------------------------------------------------------------------

Arithmetic : Arithmetic.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o Arithmetic Arithmetic.o BigInteger.o List.o

Arithmetic.o : List.h BigInteger.h Arithmetic.cpp
	g++ -std=c++17 -Wall -c Arithmetic.cpp

ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o

ListClient : ListClient.o List.o
	g++ -std=c++17 -Wall -o ListClient ListClient.o List.o 

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp

ListClient.o : List.h ListClient.cpp
	g++ -std=c++17 -Wall -c ListClient.cpp

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

BigIntegerClient : BigIntegerClient.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o BigIntegerClient BigIntegerClient.o BigInteger.o List.o

BigIntegerTest.o : BigInteger.h BigIntegerTest.cpp
	g++ -std=c++17 -Wall -c BigIntegerTest.cpp

BigIntegerClient.o : BigInteger.h BigIntegerClient.cpp
	g++ -std=c++17 -Wall -c BigIntegerClient.cpp

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp

BigInteger.o : BigInteger.h BigInteger.cpp
	g++ -std=c++17 -Wall -c BigInteger.cpp

clean :
	rm -f Shuffle Shuffle.o ListClient ListClient.o List.o

check1 : Arithmetic
	valgrind --leak-check=full ./Arithmetic

check2 : ListTest
	valgrind --leak-check=full ./ListTest

check3 : BigIntegerClient
	valgrind --leak-check=full ./BigIntegerClient

check4 : BigIntegerTest
	valgrind --leak-check=full ./BigIntegerTest