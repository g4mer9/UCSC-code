/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa2
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    FILE *in, *out;
    int n;
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
    if(in == NULL || out == NULL) {
        fprintf(stderr, "error opening files\n");
        exit(EXIT_FAILURE);
    }

    if(fscanf(in, "%d", &n) != 1) { //scanning in number of vertices
        fprintf(stderr, "Error scanning in number of vertices\n");
        exit(EXIT_FAILURE);
    }

    Graph G = newGraph(n); //new graph

    int u, v;
    while(fscanf(in, "%d %d", &u, &v) == 2 && u != 0 && v != 0) {
        addEdge(G, u, v);
    }

    printGraph(out, G);

    while (fscanf(in, "%d %d", &u, &v) == 2 && u != 0 && v != 0) {
        fprintf(out, "\n");
        BFS(G, u);
        int distance = getDist(G, v);
        if (distance == INF) {
            fprintf(out, "The distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists\n", u, v);
        } else {
            fprintf(out, "The distance from %d to %d is %d\n", u, v, distance);
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            List path = newList();
            getPath(path, G, v);
            printList(out, path);
            freeList(&path);
        }
    }

    fprintf(out, "\n");
    fclose(in);
    fclose(out);
    freeGraph(&G);

    return 0;
}
