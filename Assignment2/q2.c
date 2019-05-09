#include "graphAdt.h"
/*
* call dfs on G : record finish time
* call dfs on Gt based on highest to lowest finish time
* strongly connected component remains strongly connected componenet on gt
* SCC s create a dag having a source and a sink
* highest finish time node is in the source node of scc graph so we do transpose and compute scc
* we dont need to record finish time explicitly.. in dfs call we put them in a stack when recursive visit to all
* dfs subtrees end
*/

#define TOTAL_NODES 16

// A structure to represent a stack 
typedef struct STACK 
{ 
    int top; 
    int capacity; 
    int* array; 
}Stack; 
  
Stack* createStack(int capacity) 
{ 
    Stack* stack = ( Stack*) malloc(sizeof( Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*) malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 
  
int isFull( Stack* stack) 
{   return stack->top == stack->capacity - 1; } 
  
int isEmpty( Stack* stack) 
{   return stack->top == -1;  } 
  
void push( Stack* stack, int item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    //printf("%d pushed to stack\n", item); 
} 
  
int pop( Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 

void dfsUtil(Graph* g,int i,int* visited)
{
    // mark this node as visited
    visited[i] = 1;
    // for all unvisited nodes in adjacnt list recursively call
    int j=0;
    int* mat = g->graph;
    printf("%d ",i);    
    for(j=0;j<g->v;j++)
    {
        // there is an edge to j th node
        if(*(mat+g->v*i+j) == 1 && visited[j]==0)
            dfsUtil(g,j,visited);
    }
}

void dfsUtilStack(Graph* g,int i,int* visited,Stack* s)
{
    // mark this node as visited
    visited[i] = 1;
    // for all unvisited nodes in adjacnt list recursively call
    int j=0;
    int* mat = g->graph;
    //printf("%d ",i);    
    for(j=0;j<g->v;j++)
    {
        // there is an edge to j th node
        if(*(mat+g->v*i+j) == 1 && visited[j]==0)
            dfsUtilStack(g,j,visited,s);
    }
    push(s,i);
}
void dfsToSCC(Graph* g,Stack* s)
{
    int* visited = calloc(g->v,sizeof(int));

    int i=0;
    while(!isEmpty(s))
    {
        i = pop(s);
        if(!visited[i])
        {
            dfsUtil(g,i,visited);
        
            printf("\n");
            // push i into the stack
            
        }
    }
}

void dfsToStack(Graph* g,Stack* s)
{
    int* visited = calloc(g->v,sizeof(int));

    int i=0;
    for(i=0;i<g->v;i++)
    {
        if(!visited[i])
        {
            dfsUtilStack(g,i,visited,s);
        
            //printf("\n");
            // push i into the stack
            //push(s,i);

        }
    }
}

int main()
{
    srand(time(0)); 

    // 12 dir ab1
    int arr[] = {
        0,1,
        1,3, 1,4, 1,2,
        2,1, 2,5, 2,6,
        4,5,
        5,4, 5,7,
        6,7, 6,9,
        7,10,
        8,6,
        9,8,
        10,11,
        11,9
    };

    // 16 dir ab2
    int arr2[] = {
        0,2,
        1,0, 1,5,
        2,1, 2,4,
        3,2, 3,6,
        4,3, 4,5, 4,7,
        5,10, 5,12, 5,14,
        6,7,
        7,9, 7,8,
        8,6,
        9,8, 
        10,11, 10,15,
        11,10,
        12,13,
        13,14, 13,15,
        14,12, 14,15,
    };

    Graph g;
    initGraph(&g,TOTAL_NODES,MATRIX);
    createGraphFromInput(&g,1,arr2,sizeof(arr2)/sizeof(int));
    //makeRandomGraph(&g);
    Graph gc;
    complimentGraph(&g,&gc);

    //printGraph(&g);
    //printGraph(&gc);

    Stack* s = createStack(TOTAL_NODES);
    dfsToStack(&g,s);
    int i;
    /*
    printf("top: %d\n",s->top);
    for(i=0;i<g.v;i++)
    {
        printf("**%d ",s->array[i]);
    }
    */

    dfsToSCC(&gc,s);

    return 0;
}