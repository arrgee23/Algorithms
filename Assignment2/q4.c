#include "graphAdt.h"
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
    Graph g;
    initGraph(&g,8,MATRIX);
    int arr[] = {2,3, 3,1, 4,0,4,1, 5,0,5,1};
    int arr2[] = {0,2, 1,0,1,3, 2,4,2,5, 3,2};

    // 6 dir ab1
    int arr4[] = 
    {
        0,1,
        1,2, 1,5,
        3,4, 3,0,
        4,1
    };
    // 8 dir ab2
    int arr3[] = {0,3, 
                1,3,1,4, 
                2,4,2,7, 
                3,5,3,6,3,7, 
                4,6 };
    createGraphFromInput(&g,1,arr3,sizeof(arr3)/sizeof(int));

    //printGraph(&g);
    //printGraph(&gc);

    Stack* s = createStack(10000);
    dfsToStack(&g,s);
    int i;
    
    while(!isEmpty(s))
    {
        int n = pop(s);
        printf("%d ",n);
    }

    
    return 0;
}