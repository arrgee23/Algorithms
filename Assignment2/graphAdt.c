#include "graphAdt.h"

// returns pointer to matrix

void initGraph(Graph* g,int nodes,int type)
{
    g->v = nodes;
    g->type = type;
    
    // matrix representation
    if(type==MATRIX)
        g->graph = calloc(g->v*g->v,sizeof(int));
    else if(type==LIST)
    {
        g->graph = calloc(g->v,sizeof(Node*));
        Node** adjList = (g->graph);
    }
    
}   
void complimentGraph(Graph* g,Graph* gc)
{
    gc->v = g->v;
    gc->type = g->type;
    gc->graph = calloc(g->v*g->v,sizeof(int));
    int i,j;
    for(i=0;i<g->v;i++)
    {
       for(j=0;j<g->v;j++)
       {
           if(hasEdge(g,i,j))
                addEdge(gc,j,i);
       }
    }
}
void makeRandomGraph(Graph* g)
{
    int nodes = g->v;
    
    printf("nodes: %d\n",nodes);

    int noEdges = generateRandIntBetween(0,(nodes*(nodes-1))/2);
    int mat[g->v][g->v];

    int i,j;
    for(i=0;i<g->v;i++)
        for(j=0;j<g->v;j++)
            mat[i][j] = 0;
    for(i=0;i<noEdges;i++)
    {
        int u,v;
        do{
            u = generateRandIntBetween(0,nodes-1);
            v = generateRandIntBetween(0,nodes-1);
        }while(u==v || mat[u][v]);
        printf("%d-%d\n",u,v);    
        addEdge(g,u,v);
        mat[u][v] = 1;
    }
}
void createGraphFromInput(Graph* g,int isDirected,int* arr,int len)
{
    int i=0;
    for (int i = 0; i < len; i+=2)
    {
        addEdge(g,arr[i],arr[i+1]);
        if(!isDirected)
            addEdge(g,arr[i+1],arr[i]);
    }
    
}

void createGraphFromInputWeight(Graph* g,int isDirected,int* arr,int len)
{
    int i=0;
    for (int i = 0; i < len; i+=3)
    {
        addEdgewithWeight(g,arr[i],arr[i+1],arr[i+2]);
        if(!isDirected)
            addEdgewithWeight(g,arr[i+1],arr[i],arr[i+2]);
    }
}

int hasEdge(Graph* g,int i,int j)
{
    if(g->type==MATRIX)
    {
        int* mat = g->graph;
        return *(mat+g->v*i+j);
    }
    else
    {
        printf("HasEdge function not implemented for ll\n");
        assert(0);
    }
    
}

void addEdgewithWeight(Graph* g,int i,int j,int w)
{
     if(i==j || i>=g->v || j>=g->v || i<0 || j<0)
    {
        assert(0);
    }
    if(g->type==MATRIX)
    {
        int* mat = g->graph;
        *(mat+g->v*i+j) = w;
    }
}

void addEdge(Graph* g,int i,int j)
{
    if(i==j || i>=g->v || j>=g->v || i<0 || j<0)
    {
        assert(0);
    }
    if(g->type==MATRIX)
    {
        int* mat = g->graph;
        *(mat+g->v*i+j) = 1;
    }
    else
    {
        Node** adjList = g->graph;
        append(adjList+i,j);
    }
    
}

int generateRandIntBetween(int a,int b)
{
    if(a!=b)
    {
        return (rand() % (b - a + 1)) + a;
    }
    return a;
}

void printGraph(Graph* g)
{
    int i=0,j=0;
    printf("-----------------------------------\n");
    if(g->type==MATRIX)
    {
        for(i=0;i<g->v;i++)
        {
            for(j=0;j<g->v;j++)
            {
                printf("%d ",hasEdge(g,i,j));
            }
            printf("\n");
        }
    }
    else
    {
        Node** adjList = g->graph;
        for(int i=0;i<g->v;i++)
        {
            printf("%d: ",i);
            Node* head = *(adjList+i);
            while(head!=NULL)
            {
                printf("%d ",head->n);
                head = head->next;
            }
            printf("\n");
        }
    }
    
    printf("-----------------------------------\n");
}

Node* createNode(int v)
{
    Node* ret = malloc(sizeof(Node));
    ret->n = v;
    ret->next = NULL;
    return ret;
}
void append(Node** head,int v)
{
    if(*head == NULL)
    {
        *head = createNode(v);
    }else
    {
        Node* t = (*head);
        *head = createNode(v);
        (*head)->next = t;

    }
    
}