###List ADT and programs Lex and ListTest

Table of Contents:
List.c - main ADT, includes all requested functions
List.h - header file, contains typedef of List, ListObj, and Node
Lex.c - main program. Takes input and output file names and alphabitizes input
ListTest.c - test program that covers every function declared in List.h. I struggled to think of any extra edge cases that needed testing.


Usage instructions:
build with 'make'

clean with 'make clean'

run through terminal in the program directory with './Lex input output' or './ListTest'

the ideal ListTest output is included in a comment in the .c file, as well as the following:

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19
19
0

