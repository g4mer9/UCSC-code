/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa2
 */
#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "List.h"

#define INF -1
#define NIL 0

//types--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct GraphObj* Graph;

//constructors/deconstructors----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph *pG);

//access functions---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

//manip functions----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

//other operations----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void printGraph(FILE *out, Graph G);

