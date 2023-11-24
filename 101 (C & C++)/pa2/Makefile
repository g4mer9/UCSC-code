BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindPath : FindPath.o Graph.o List.o
	gcc -std=c17 -Wall -o FindPath FindPath.o Graph.o List.o

FindPath.o : FindPath.c Graph.h List.h
	gcc -std=c17 -Wall -c FindPath.c

GraphTest : GraphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o Graph.o List.o

GraphTest.o : GraphTest.c Graph.c List.c
	gcc -std=c17 -Wall -c GraphTest.c Graph.c List.c

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

Graph.o : Graph.c Graph.h List.h
	gcc -std=c17 -Wall -c Graph.c List.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

clean :
	rm -f List.o Graph.o GraphTest.o GraphTest GraphClient GraphClient.o FindPath FindPath.o

checkTest :
	valgrind --leak-check=full ./GraphTest

checkPath :
	valgrind --leak-check=full ./FindPath in1.txt out1.txt

checkClient : GraphClient
	$(MEMCHECK) ./GraphClient

