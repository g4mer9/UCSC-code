/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa3
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    FILE *in, *out;
    char line[1000];
    int n, u, v, k, count;
    char *fileerr = "There was a problem opening the file.\n";

    if (argc != 3) { //checking number of args
        fprintf(stderr, "FindPath needs exactly two arguments: ./FindPath <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    char *in_name = argv[1];
    char *out_name = argv[2]; //copying file names

    if (access(in_name, F_OK) != 0) {
        fprintf(stderr, "%s\n", fileerr); //printing file error if cant open
        return 1;
    }

    in = fopen(in_name, "r"); //opening files
    out = fopen(out_name, "w+");
    if (in == NULL || out == NULL) {
        fprintf(stderr, "error opening files\n");
        exit(EXIT_FAILURE);
    }

    //read the number of vertices
    fgets(line, 1000, in);
    n = atoi(line);

    //creating graph and list
    List S = newList();
    Graph G = newGraph(n);

    //read the edges and add them to graph
    while(fgets(line, 1000, in) != NULL){
        sscanf(line, "%d %d", &u, &v);
        if(u == 0 && v == 0) break;
        addArc(G, u, v);
    }

    //print the adjacency list representation of G
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    //populating list
    for (int i = 1; i <= getOrder(G); i++) {
        append(S, i);
    }

    //DFS and transpose calls
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);
    //count strongly connected components
    count = 0;
    moveFront(S);
    while(index(S) >= 0){
        if(getParent(T, get(S)) == NIL)
            count++;
        moveNext(S);
    }
    fprintf(out, "G contains %d strongly connected components:\n", count);

    //malloc list of components
    List *components = malloc((count + 1) * sizeof(List));
    for(int i = 1; i <= count; i++) {
        components[i] = newList();
    }

    //appending groups of strongly connected components
    k = 1;
    moveBack(S);
    while(index(S) >= 0){
        int component = getParent(T, get(S));
        prepend(components[k], get(S));
        if(component == NIL) {
            k++;
            movePrev(S);
            continue;
        }
        movePrev(S);
    }

    //print
    for(int i = 1; i <= count; i++) {
        fprintf(out, "Component %d:", i);
        moveFront(components[i]);
        while(index(components[i]) >= 0){
            fprintf(out, " %d", get(components[i]));
            moveNext(components[i]);
        }
        fprintf(out, "\n");
        freeList(&components[i]);
    }

    // Free memory and close files
    freeList(&S);
    free(components);
    freeGraph(&G);
    freeGraph(&T);
    fclose(in);
    fclose(out);
    return 0;
}
