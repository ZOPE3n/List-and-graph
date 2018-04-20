
#ifndef _Graph_H_INCLUDE_
#define _Graph_H_INCLUDE_
#define NIL (int) 0
#define UNDEF (int) -1
#define WHITE (int) 0
#define GRAY (int) 1
#define BLACK (int) -1
#include "List.h"

typedef struct GraphObj* Graph;

Graph newGraph(int n);

void freeGraph(Graph* pG);

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);


void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif
