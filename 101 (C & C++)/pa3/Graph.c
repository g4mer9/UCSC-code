/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa3
 */
#include "Graph.h"
#include <stdlib.h>
#include <stdbool.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

//types--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct GraphObj {
    List *adj;//adjacency list, [i] contains list of neighbors to i
    int *color;//color of vertex [i]
    int *parent;//parent of vertex [i]
    //int *distance;//distance from most recent source to [i] //pa2 variable
    int order;//n of vertices
    int size;//n of edges
    int *discover;//discover time for index [i]
    int *finish;//finish time for index [i]
    //int source;//value of vertex last used as a source for BFS //pa2 variable
} GraphObj;

//constructors/deconstructors----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->discover = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));
    //G->distance = calloc(n + 1, sizeof(int));
    G->order = n;
    G->size = 0;
    //G->source = NIL;
    for (int i = 1; i <= n; i++) { //default graph values
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
        //G->distance[i] = INF;
    }
    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        Graph G = *pG;
        for (int i = 1; i <= getOrder(G); i++) {
            freeList(&(G->adj[i]));
        }
        free(G->adj);
        free(G->color);
        free(G->parent);
        free(G->discover);
        free(G->finish);
        //free(G->distance);
        free(*pG);
        *pG = NULL;
    }
}

//access functions---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

/*int getSource(Graph G) {
    return G->source;
}*/

int getParent(Graph G, int u) {
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if (u < 1 || u > getOrder(G)) {//precond
        fprintf(stderr, "getDiscover: vertex %d out of range\n", u);
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if (u < 1 || u > getOrder(G)) {//precond
        fprintf(stderr, "getFinish: vertex %d out of range\n", u);
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

/*int getDist(Graph G, int u) {
    return G->distance[u];
}*/

/*void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL) {
        fprintf(stderr, "getPath: graph has no source vertex\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "getPath: vertex index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    if (u == getSource(G)) append(L, u); //if u is source append u

    else if (getParent(G, u) == NIL) append(L, NIL); //if u doesnt have a parent, append NIL

    else {
        getPath(L, G, getParent(G, u));//recursive call to print all parents of u, starting with the source and working back down
        append(L, u);
    }
}*/

//manip functions---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void makeNull(Graph G) { //clear graph
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->adj[i]);//clearing adj lists
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        //G->distance[i] = INF;
    }
    G->size = 0;
}

void addArcHelper(List L, int v) {
    if (length(L) == 0) append(L, v); //appends if empty adj list

    else {
        moveFront(L);
        while (index(L) != -1 && v > get(L)) moveNext(L); // move right in list until out of bounds or correct position

        if (index(L) == -1) append(L, v); //append if end of list

        else insertBefore(L, v); //else insert before cursor
    }
}

void addArc(Graph G, int u, int v) {
    bool a = 0;
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {//bounds check
        fprintf(stderr, "addArc: vertex %d or %d out of range\n", u, v);
        exit(EXIT_FAILURE);
    }

    for (moveFront(G->adj[u]); G->adj[u]->index != -1; moveNext(G->adj[u])) {//is v in u (existing)
        if(get(G->adj[u]) == v) {
            a = 1;
            break;
        }
    }
    if(!a) G->size++; //increasing size (edge count) if:
    // u is in v (an arc goes one way) but v is not in u (there is no arc going the way requested)

    addArcHelper(G->adj[u], v);
}

void addEdge(Graph G, int u, int v) {
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "addEdge: vertex index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--; //offset since both addEdge and addArc calls seem to need G->size++
}

void Visit(Graph G, List N, int x, int *time) {
    int y;
    G->color[x] = GRAY; //vertex visited
    (*time)++; //increment time
    G->discover[x] = *time; //set discovery time

    List neighbors = G->adj[x];
    for (moveFront(neighbors); index(neighbors) != -1; moveNext(neighbors)) { //loop through neighbors
        y = get(neighbors);
        if (G->color[y] == WHITE) { //if neighbor is unvisited
            G->parent[y] = x; // set x as parent of y
            Visit(G, N, y, time); // recursively visit neighbor
        }
    }
    prepend(N, x);
    G->color[x] = BLACK; // set vertex as finished
    (*time)++;
    G->finish[x] = *time;
}

void DFS(Graph G, List S) {
    if(G == NULL ){
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(S == NULL ){
        fprintf(stderr, "DFS Error: calling DFS() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(S->length != getOrder(G)){
        fprintf(stderr, "DFS Error: calling DFS() when len(S) != getOrder(G)\n");
        exit(EXIT_FAILURE);
    }
    int t = 0;
    List N = newList();

    for (int i = 1; i <= length(S); ++i) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }

    //loop through all vertices and call Visit() if vertex is white
    moveFront(S);
    while (index(S) != -1) { //loop through vertices specified by s
        int x = get(S);
        if (G->color[x] == WHITE) {
            Visit(G, N, x, &t);
        }
        moveNext(S);
    }

    clear(S);
    for(moveFront(N); index(N) != -1; moveNext(N)) {
        append(S, get(N));
    }
    freeList(&N);
}

/*void BFS(Graph G, int s) {
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    while (Q->length != 0) {
        int u = front(Q);
        deleteFront(Q);
        List adj = G->adj[u];
        for (moveFront(adj); index(adj) != -1; moveNext(adj)) {
            int v = get(adj);
            if (G->color[v] == WHITE) {
                G->color[v] = GRAY;
                G->distance[v] = G->distance[u] + 1;
                G->parent[v] = u;
                append(Q, v);
            }
        }
        G->color[u] = BLACK;
    }
    freeList(&Q);
}
*/
//other operations----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//returns a new graph object representing the transpose of G
Graph transpose(Graph G) {
    Graph T = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        for (moveFront(G->adj[i]); index(G->adj[i]) != -1; moveNext(G->adj[i])) {
            addArc(T, get(G->adj[i]), i);
        }
    }
    return T;
}


//returns a new graph that is a copy of G
Graph copyGraph(Graph G) {
    Graph C = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        for (moveFront(G->adj[i]); index(G->adj[i]) != -1; moveNext(G->adj[i])) {
            addArc(C, get(G->adj[i]), i);//add edge in pa2
        }
    }
    return C;
}

void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d:", i);
        if(G->adj[i]->length != 0) printList(out, G->adj[i]); //print adj list if not empty
        fprintf(out, "\n");
    }
}

