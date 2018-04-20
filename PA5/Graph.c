/**Mengdi Wei
  *ID: 1538074
  *PA5
  *This is the graph.c, which provides 
  * a libarry of methods.
  */


#include <stdio.h> 
#include <stdlib.h> 
#include "List.h"
#include "Graph.h"

#define NIL (int) 0
#define UNDEF (int) -1
#define WHITE (int) 0
#define GRAY (int) 1
#define BLACK (int) -1

typedef struct GraphObj {
  int * colors;
  int * parents;
  int * discover;
  int * end;
  int flags;
  int order;
  int size;
  int clock;
  List * str;
}
GraphObj;
 //This is the constructor
Graph newGraph(int n) {
  Graph G = malloc(sizeof(struct GraphObj));
  G -> str = calloc(n + 1, sizeof(List));
  G -> str[0] = NULL;
  G -> colors = calloc(n + 1, sizeof(int));
  G -> parents = calloc(n + 1, sizeof(int));
  G -> discover = calloc(n + 1, sizeof(int));
  G -> end = calloc(n + 1, sizeof(int));
  G -> flags = 1;
  G -> order = n;
  G -> size = NIL;
  G -> clock = UNDEF;
  for (int i = 1; i < n + 1; i++) {
    G -> str[i] = newList();
    G -> discover[i] = UNDEF;
    G -> end[i] = UNDEF;
    G -> colors[i] = WHITE;
    G -> parents[i] = NIL;
  }
  return G;
}
//free all things in a graph
void freeGraph(Graph * pG) {
  if (pG != NULL && * pG != NULL) {
    free(( * pG) -> colors);
    free(( * pG) -> discover);
    free(( * pG) -> end);
    free(( * pG) -> parents);
    for (int i = 1; i <= ( * pG) -> order; i++) {
      freeList( & ( * pG) -> str[i]);
    }
    free(( * pG) -> str);
    free( * pG); * pG = NULL;
  }
}
//return size of a graph
int getSize(Graph G) {
  if (G == NULL) {
    printf("getSize() called on a NULL graph reference");
    exit(1);
  }
  return G -> size;
}
//return order of a graph
int getOrder(Graph G) {
  if (G == NULL) {
    printf("getOrder() called on a NULL graph reference");
    exit(1);
  }

  return G -> order;
}
//return the source of a graph
int getParent(Graph G, int u) {
  if (G == NULL) {
    printf("Graph Error: getParent() called on a NULL graph reference");
    exit(1);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Called getParent() on out of bound u.\n");
    exit(1);
  }
  return G -> parents[u];
}
//return result of discover of a graph
int getDiscover(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getDiscover on NULL Graph");
    exit(1);
  }
  if (u < 1 || u > getOrder(G)) {
    fprintf(stderr, "getDiscover Error: index out of range of discover");
    exit(1);
  }

  return G -> discover[u];
}
//retrun result of finish of the graph
int getFinish(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getFinish on NULL Graph");
    exit(1);
  }
  if (u < 1 || u > getOrder(G)) {
    fprintf(stderr, "getFinish Error: index out of range of finish");
    exit(1);
  }
  return G -> end[u];
}
//add edges from u to v, and from v to u
void addEdge(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr, "Graph error: addEdge() called on null Graph reference\n");
    exit(1);
  }
  G -> flags = 0;
  addArc(G, u, v);
  addArc(G, v, u);
  G -> size--;
}
//add one  way edge from u to v to the graph
void addArc(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr, "Graph error: addArc() called on null Graph reference\n");
    exit(1);
  }
  List L = G -> str[u];
  if (length(L) == 0) {
    append(L, v);
    G -> size++;
    return;
  }
  if (v<front(L)){
    prepend(L, v);
    G -> size++;
    return;
  }
  if (v>back(L)){
    append(L, v);
    G -> size++;
    return;
  }
  moveFront(L);
  int a = get(L);
  moveNext(L);
  while (index(L) != -1) {
    if (v < get(L)&&v>a) {
      insertBefore(L, v);
      break;
    }
    a = get(L);
    moveNext(L);
  }
  if (index(L) == -1)
    append(L, v);
  G -> size++;
}
//recursive funtion for the DFS
void Visit(Graph G, List S, int x) {
  if (G == NULL) {
    printf("Graph Error: visit() called on a NULL graph reference");
    exit(1);
  }
  G -> colors[x] = GRAY;
  G -> clock++;
  G -> discover[x] = G -> clock;
  List list = G -> str[x];
  moveFront(list);
  while (index(list) != -1) {
    int value = get(list);
    if (G -> colors[value] == WHITE) {
      G -> parents[value] = x;
      Visit(G, S, value);
    }
    moveNext(list);
  }
  G -> colors[x] = BLACK;
  G -> clock++;
  G -> end[x] = G -> clock;
  prepend(S, x);
}
//Run dfs for the graph and could get colors parents and time for the graph
void DFS(Graph G, List S) {
  if (G == NULL) {
    printf("Graph Error: DFS() called on a NULL graph reference");
    exit(1);
  }
  if (length(S) != getOrder(G)) {
    printf("Graph Error: DFS() called with a stack length != G->order\n");
    exit(1);
  }

  for (int i = 1; i <= getOrder(G); i++) {
    G -> colors[i] = WHITE;
    G -> parents[i] = NIL;
  }
  G -> clock = 0;
  moveFront(S);
  while (index(S) != -1) {
    int value = get(S);
    if (G -> colors[value] == WHITE) {
      Visit(G, S, value);
    }
    moveNext(S);
  }
  for (int i = 1; i <=getOrder(G); i++)
    deleteBack(S);
}
//transpose a graph
Graph transpose(Graph G) {
  if (G == NULL) {
    printf("Graph Error: transpose() called on a NULL graph reference");
    exit(1);
  }
  Graph graph = newGraph(G -> order);
  for (int i = 1; i <= getOrder(G); i++) {
    List list = G -> str[i];
    if (length(list) != 0) {
      moveFront(list);

      while (index(list)!=-1) {
        int number = get(list);
        addArc(graph, number, i);
        moveNext(list);
      }
    }
  }
  return graph;
}
//copy a graph
Graph copyGraph(Graph G){
    Graph graph = newGraph(getOrder(G));
    for (int i=1; i<=getOrder(G);i++){
    	  List list=G->str[i];
    	  moveFront(list);
        while(index(list)!=-1){
            addArc(graph,i,get(list));
            moveNext(list);
        }
    }
    return graph;
}
//print a graph
void printGraph(FILE * out, Graph G) {
  if (G == NULL) {
    printf("Graph Error: printGraph() called on a NULL graph reference");
    exit(1);
  }
  if (G == NULL) {
    printf("Graph Error: calling printGraph() on NULL Graph reference\n");
    exit(1);
  }
  for (int i = 1; i <= getOrder(G); i++) {
    fprintf(out, "%d: ", i);
    printList(out, G -> str[i]);
    fprintf(out, "\n");
  }
}