/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa3
 */
#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "List.h"

#define UNDEF -2
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
//int getSource(Graph G); //(pa2 function)
int getParent(Graph G, int u);
//int getDist(Graph G, int u); //(pa2 function)
//void getPath(List L, Graph G, int u); //(pa2 function)
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) (pa3 function) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) (pa3 function) */


//manip functions----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
//void BFS(Graph G, int s); //(pa2 function)
void DFS(Graph G, List S); //pre: len(S) == getOrder(G)

//other operations----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);

