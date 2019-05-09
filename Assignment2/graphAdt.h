#ifndef GRAPHADT_H
#define GRAPHADT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <assert.h>
#include <limits.h>
#include <string.h>

#define MATRIX 0
#define LIST 1
#define EDGES 2

typedef struct GRAPH
{
    void* graph;
    int v;
    int type;
}Graph;

typedef struct NODE
{
    int n;
    struct NODE* next;
}Node;


Node* createNode(int v);
void append(Node** head,int v);
void initGraph(Graph* g,int nodes,int type);
void createGraphFromInput(Graph* g,int isDirected,int* arr,int len);
void createGraphFromInputWeight(Graph* g,int isDirected,int* arr,int len);
void makeRandomGraph(Graph* g);
void addEdge(Graph* g,int i,int j);
void addEdgewithWeight(Graph* g,int i,int j,int w);
void printGraph(Graph* g);
int generateRandIntBetween(int a,int b);
void complimentGraph(Graph* g,Graph* gc);
int hasEdge(Graph* g,int i,int j);




#endif