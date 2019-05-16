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

void dfsUtil(Graph* g,int i,int* visited)
{
    if(g->type==LIST)
    {
        printf("dfs Not implemented for list");exit(0);
    }
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


void dfs(Graph* g)
{
    int* visited = calloc(g->v,sizeof(int));

    int i=0;
    printf("The DFS traversal is\n");
    for(i=0;i<g->v;i++)
    {
        if(!visited[i])
        {
            dfsUtil(g,i,visited);
        
            printf("\n");
        }
    }
}

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

void dfsUtilscc(Graph* g,int i,int* visited)
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
            dfsUtilscc(g,j,visited);
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
            dfsUtilscc(g,i,visited);
        
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

int findscc(Graph* g)
{
    printf("Strongly connected components: each component in a new line\n");
    
    //makeRandomGraph(&g);
    Graph gc;
    complimentGraph(g,&gc);

    //printGraph(&g);
    //printGraph(&gc);

    Stack* s = createStack(10000);
    dfsToStack(g,s);

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

/*
    for every node during dfs visit record their parent, discovery time
    after coming back from the recursive call update low, which is the lowest 
    visit time to which the vertex or any of the vertex at subtree rooted at this vertex
    // isAp,visited initially al false
    // initial val doesnt matter: disc,low,parent
    // but before dfs call parent must be set. for root it is itself

*/
int min(int a,int b)
{
    return a<b? a:b;
}

int myTime = 0;
void dfsAp(Graph* g,int current,int* visited,int* low,int* disc,int* parent,int* isAp)
{
    // mark this node as visited
    visited[current] = 1;
    myTime++; // increment the clock
    disc[current] = myTime;// set discovery time
    low[current]=disc[current]; // low[current] refers to the lowest visit time in 
                                // the subtree it is at max visit time

    // for all unvisited nodes in adjacnt list recursively call
    int child=0;
    int* mat = g->graph;
    //printf("%d ",current);

    int noOfChildren=0;
    for(child=0;child<g->v;child++)
    {

        // there is an edge to child th node and unvisited
        if(hasEdge(g,current,child))
        {
            

            // if unvisited child visit
            if(visited[child]==0)
            {
                noOfChildren++;
                parent[child] = current;
                dfsAp(g,child,visited,low,disc,parent,isAp);
                
                // now its child has its low number set so update its
                low[current] = min(low[current],low[child]);

                // now check if the node is an articulation point
                
                //if its the root and has more than one child sdfs tree then its ap
                if(parent[current]==current && noOfChildren>1)
                    isAp[current] = 1;

                // if the discovery time of the current node is greater than the low[child]
                // meaning earliest node reachable from child is discovered before the parent
                // means it is connected to the ancestor
                else if(parent[current]!=current && disc[current]<=low[child])
                {
                    isAp[current] = 1;
                    //printf("%d Made ap for %d",current,child);
                }    

            }else
            {
                // an already discovered child: update low
                if(parent[current] != child)
                    low[current] = min(low[current],disc[child]);
            }
            
        }
    }
}

void checkBridge(Graph* g,int current,int* visited,int* low,int* disc,int* parent)
{
    // mark this node as visited
    visited[current] = 1;
    myTime++; // increment the clock
    disc[current] = myTime;// set discovery time
    low[current]=disc[current]; // low[current] refers to the lowest visit time in 
                                // the subtree it is at max visit time

    // for all unvisited nodes in adjacnt list recursively call
    int child=0;
    int* mat = g->graph;
    //printf("%d ",current);

    int noOfChildren=0;
    for(child=0;child<g->v;child++)
    {

        // there is an edge to child th node and unvisited
        if(hasEdge(g,current,child))
        {
            // if unvisited child visit
            if(visited[child]==0)
            {
                noOfChildren++;
                parent[child] = current;
                checkBridge(g,child,visited,low,disc,parent);
                
                // now its child has its low number set so update its
                low[current] = min(low[current],low[child]);

                // now check if the edge is a bridge
                
                // if the discovery time of the current node is greater than the low[child]
                // meaning earliest node reachable from child is discovered before the parent
                // means it is connected to the ancestor
                if( disc[current]<low[child])
                {
                    //isAp[current] = 1;

                    printf("Bridge: %d-%d\n",current,child);
                }    

            }else
            {
                // an already discovered child: update low
                if(parent[current] != child)
                    low[current] = min(low[current],disc[child]);
            }
            
        }
    }
}

// wont work on disconnnected graph unless manipulated to run dfs on each
void findAP(Graph* g)
{
    printf("We print the list of articulation points below\n");   
    int *visited, *low, *disc, *parent, *isAp;
    visited = calloc(g->v,sizeof(int));
    low = calloc(g->v,sizeof(int));
    disc = calloc(g->v,sizeof(int));
    parent = calloc(g->v,sizeof(int));
    isAp = calloc(g->v,sizeof(int));
    int i;

    

    dfsAp(g,0,visited,low,disc,parent,isAp);
    //checkBridge(&g,0,visited,low,disc,parent);

    printf("\n\n");
   
    /*
    for ( i = 0; i < g.v; i++)
    {
        printf("**%d %d** ",i,g.v);
        printf("%d %d %d %d %d\n",visited[i],low[i],disc[i],parent[i],isAp[i]);
        //low[i] = INT_MAX;
    }
    */

    for(i=0;i<g->v;i++)
        if(*(isAp+i))
            printf("\n#%d is an Ap\n",i);
    

}

void findBridge(Graph* g)
{
    printf("We print the list of brige edges below\n");

    int *visited, *low, *disc, *parent, *isAp;
    visited = calloc(g->v,sizeof(int));
    low = calloc(g->v,sizeof(int));
    disc = calloc(g->v,sizeof(int));
    parent = calloc(g->v,sizeof(int));
    isAp = calloc(g->v,sizeof(int));
    int i;

    

    //dfsAp(&g,0,visited,low,disc,parent,isAp);
    checkBridge(g,0,visited,low,disc,parent);

    printf("\n\n");
   
    /*
    for ( i = 0; i < g.v; i++)
    {
        printf("**%d %d** ",i,g.v);
        printf("%d %d %d %d %d\n",visited[i],low[i],disc[i],parent[i],isAp[i]);
        //low[i] = INT_MAX;
    }
    */
   /*
    for(i=0;i<g->v;i++)
        if(*(isAp+i))
            printf("\n#%d is an Ap\n",i);
    */

}

void dfsUtilStackTopo(Graph* g,int i,int* visited,Stack* s)
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
            dfsUtilStackTopo(g,j,visited,s);
    }
    push(s,i);
}

void dfsToStackTopo(Graph* g,Stack* s)
{
    int* visited = calloc(g->v,sizeof(int));

    int i=0;
    for(i=0;i<g->v;i++)
    {
        if(!visited[i])
        {
            dfsUtilStackTopo(g,i,visited,s);
        
            //printf("\n");
            // push i into the stack
            //push(s,i);

        }
    }
}

int findTopo(Graph* g)
{
    printf("We print the nodes in topological sort ordering\n");
    Stack* s = createStack(10000);
    dfsToStackTopo(g,s);
    int i;
    
    while(!isEmpty(s))
    {
        int n = pop(s);
        printf("%d ",n);
    }

    
    return 0;
}

/*
    Generic heap implementation
*/

#define HEAP_SIZE 10000

typedef struct
{
    size_t element_size;                  // Generic implementation
    unsigned int num_allocated, num_used; // Keep track of the size
    void *array;                          // Using one-based indexing
    int (*comparator)(void *, void *);    // Returns -ve, 0, or +ve
    int type;                             // 0 for maxHeap, 1 for minHeap
} HEAP;

// swap elements at ith and jth index
static void _swap(HEAP *h, int i, int j)
{
    assert(i >= 0 && j >= 0 && i <= h->num_used && j <= h->num_used);
    void *arr = h->array;
    int size = h->element_size;

    void *buffer = malloc(size);
    char *ptr1 = (char *)arr + i * (h->element_size);
    char *ptr2 = (char *)arr + j * (h->element_size);
    memcpy(buffer, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, buffer, size);
}

void initHeap(HEAP **hh, size_t elemSize,
              unsigned int num_allocated,
              int (*some_comparator)(void *, void *))
{
    *hh = malloc(sizeof(HEAP));
    HEAP *h = *hh;
    h->element_size = elemSize;
    h->num_used = 0;
    h->num_allocated = num_allocated;
    h->array = malloc((h->num_allocated + 1) * (h->element_size)); // 1 index heap
    assert(h->array != NULL);
    h->comparator = some_comparator;
}

// swap up element at index k to the top
void _swapUp(HEAP *h, int k)
{
    char *base = (char *)h->array;
    // error hote pare for char*
    while (k > 1 && h->comparator(base + k * (h->element_size), base + (k / 2) * (h->element_size)) > 0)
    {
        _swap(h, k, k / 2);
        k = k / 2;
    }
}

void insert(HEAP *h, void *n)
{
    // before insert allocate space
    if (h->num_allocated == h->num_used)
    {
        // dont care
        assert(0);
    }
    // insert element in its place

    // first copy the element to the very end

    //get the address of the last place to insert
    char *copy_addr = (char *)h->array + ((h->element_size) * (h->num_used + 1));
    memcpy((void *)copy_addr, n, h->element_size);
    h->num_used++;

    _swapUp(h, h->num_used);
}

void printAsInt(HEAP *h)
{
    int *arr = h->array;

    for (int i = 0; i < h->num_used; i++)
        printf("%d ", arr[i]);
}

void printAsString(HEAP *h)
{
    char *arr = h->array;

    for (int i = 1; i < h->num_used + 1; i++)
        printf("%s ", arr + i * h->element_size);

    printf("\n");
}
static char *_getElemAddr(HEAP *h, int index)
{
    assert(index <= h->num_used && index>0);
    char *base = h->array;
    return base + index * (h->element_size);
}
void _swapDown(HEAP *h, int index)
{
    int leftChild = -1;
    int rightChild = -1;
    if (2 * index <= h->num_used)
    {
        leftChild = 2 * index;
        if (2 * index + 1 <= h->num_used)
            rightChild = 2 * index + 1;
    }

    int maxIndex = index;
    if (leftChild != -1 && h->comparator(_getElemAddr(h,maxIndex), _getElemAddr(h,leftChild) )<0)
        maxIndex = leftChild;

    if (rightChild != -1 && h->comparator(_getElemAddr(h,maxIndex), _getElemAddr(h,rightChild))<0)
        maxIndex = rightChild;
    
    if(maxIndex != index)
    {
        // swap the two elements
        _swap(h,maxIndex,index);

        // now tree rooted at maxIndex may not satisfy heap property
        // so recursively swapdown
        _swapDown(h,maxIndex);
    }
}
// arrLen = length of the array containing heap
// no of heap elements would be arrLen - 1 as index 0 is 
void initHeapFromArray(HEAP **hh,size_t elemSize,
                        void* arr,
                        int arrLen,
                        int (*some_comparator)(void*, void*))
{
    *hh = malloc(sizeof(HEAP));
    HEAP *h = *hh;
    h->element_size = elemSize;
    h->num_used = arrLen-1;
    h->num_allocated = arrLen;
    h->array = arr; // 1 index heap
    assert(h->array != NULL);
    h->comparator = some_comparator;

    int i=0;
    for(i=((arrLen-1)/2); i>=1; i--)
        _swapDown(h,i);
}

void extract(HEAP *h, void *buffer)
{
    assert(h->num_used);
    memcpy(buffer, _getElemAddr(h,1), h->element_size);
    memcpy(_getElemAddr(h,1), _getElemAddr(h,h->num_used),h->element_size);
    h->num_used--;
    _swapDown(h, 1);
}
/*
int main()
{
    HEAP *h = NULL;
    initHeap(&h, 5, 100, &strcmp);

    char *a = "aaaa";
    char *b = "bbbb";
    char *c = "cccc";
    char *d = "dddd";
    char *e = "eeee";
    char *f = "ffff";
    char *g = "gggg";

    insert(h, (void *)a);
    insert(h, (void *)b);
    insert(h, (void *)c);
    insert(h, (void *)d);
    insert(h, (void *)e);
    insert(h, (void *)f);
    insert(h, (void *)g);
    
    for(int i=0;i<7;i++)
    {
        printAsString(h);
        char buffer[5];
        extract(h,(void*)buffer);
        printf("\nExtractMax: %s\n",buffer);
    }

    return 0;
}
*/
/*
Dijsktra's algorithm
pick min weight vertex everytime and relax edges
single source to all verices shortest path
*/
typedef struct PAIR
{
    int weight;
    int id;
}Pair;


int minHeapComp(void* a,void* b)
{
    Pair aa = *((Pair*)a);
    Pair bb = *((Pair*)b);

    return bb.weight-aa.weight;
}

int dijsktra(Graph* g)
{
    printf("Here we print for each node its final weight and parent\n");
    //printGraph(&g);
    /* create the (weight,nodId) array for every vertex 
    // init all to max except initial vertex
    // put that in the minQueue
    */

    // indicates wheather it is in sptset
    int* spset = calloc(g->v,sizeof(int));
    int* parent = calloc(g->v,sizeof(int));
    Pair* nodes = calloc(g->v,sizeof(Pair));
    int* weights = calloc(g->v,sizeof(int));
    // initialize index and item o
    int i;
    for ( i = 0; i < g->v; i++)
    {
        nodes[i].id = i;
        nodes[i].weight = INT_MAX;
        weights[i] = INT_MAX;
    }
    
    // make node with id 0(node[1]) weight 0
    nodes[0].weight = 0;
    weights[0] = 0;

    // make a min queue and add the weights
    HEAP* h;
    initHeap(&h,sizeof(Pair),HEAP_SIZE,&minHeapComp);
    for ( i = 0; i < g->v; i++)
        insert(h,(void*)(nodes+i));

    
    int addCount = 0;

    while(addCount<g->v)
    {
        Pair buffer;
        extract(h,(void*)&buffer);

        // we have already placed this node in shortest paths set
        // mutliple weights for the same node can be there
        if(!spset[buffer.id])
        {
            // include this in set
            spset[buffer.id]=1;
            addCount++;
            int u = buffer.id;
            int* mat = g->graph;
            int v;

            // relax weights of all nodes adjacent to it
            for(v=0;v<g->v;v++)
            {
                // there is an edge to v th node
                if(*(mat+g->v*u+v) > 0 && !spset[v])
                {
                    int uvedge = *(mat+g->v*u+v);

                    if(weights[v]>weights[u]+uvedge)
                    {
                        // update weight and add updated weight to minHeap
                        weights[v]=weights[u]+uvedge;
                        Pair p;
                        p.id = v;
                        p.weight = weights[v];
                        parent[v] = u;
                        insert(h,(void*)&p);
                    }
                }
            }
        }
    }
    printf("vertex\tparent\tweight\n");
    for ( i = 0; i < g->v; i++)
    {
        printf("%d\t%d\t%d\n",i,parent[i],weights[i]);
    }
    

    return 0;
}

// graph representation with edges
typedef struct EDGE
{
    int u;
    int v;
    int w;
}Edge;

typedef struct SET
{
    int parent;
    int rank;
}Set;
int compareEdge(void* a,void* b)
{
    Edge e1 = *((Edge*)a);
    Edge e2 = *((Edge*)b);

    return e1.w - e2.w;
}


int findSet(Set* s,int elem)
{
    
    if(s[elem].parent!=elem)
    {
        s[elem].parent = findSet(s,s[elem].parent);
    }
    return s[elem].parent;
}

int unionSet(Set* s,int x, int y)
{
    int a = findSet(s,x);
    int b = findSet(s,y);

    if(s[a].rank>s[b].rank)
    {
        s[b].parent = a;
    }
    else
    {
        s[a].parent = b;
        if(s[a].rank == s[b].rank)
            s[b].rank++;
    }
    
}

int kruskal(int* arr,int len,int isDirected,int ver)
{
    // sort edges according to weight
    // 10 und
    Edge* edgelist = (Edge*)calloc(len/3,sizeof(Edge));
    
    int i;
    for (i = 0; i < len; i+=3)
    {
       edgelist[i/3].u = arr[i];
       edgelist[i/3].v = arr[i+1];
       edgelist[i/3].w = arr[i+2];
       //printf("%d %d %d\n",edgelist[i/3].u,edgelist[i/3].v,edgelist[i/3].w);
    }

    // add each edge in a set
    qsort(edgelist,len/3,sizeof(Edge),&compareEdge);

    // initialize set
    Set* sets = calloc(ver,sizeof(Set));
    for(i=0;i<ver;i++)
    {
        sets[i].parent = i;
        sets[i].rank = 0;
    }

    // extract min edges everytime and if it doesnt create a cycle
    // add to shortest path
    // V-1 edges need to be added
    int count=0;
    i=0;
    printf("Here we print the edges selected in mst and their weight\n");
    printf("Edge\tWeight\n");
    while(count<ver-1 && i<len/3)
    {
        // extract min weight edge everytime
        Edge e = edgelist[i];
        int a = findSet(sets,e.u);
        int b = findSet(sets,e.v);

        // if they dont create a cycle add it
        if( a!=b)
        {
            unionSet(sets,a,b);
            printf("%d-%d\t%d\n",e.u,e.v,e.w);
            count++;
        }
        i++;
    }
}

int main()
{
    int problemNo,isDirected;
    printf("Type of problem being solved :\n");
    printf("Enter 1 for DFS\n");
    printf("Enter 2 for Strongly Connected Components\n");
    printf("Enter 3 for Articulation Point \n");
    printf("Enter 4 for Bridge \n");
    printf("Enter 5 for Topological Sort\n"); 
    printf("Enter 6 for Dijkstras Shortest Path\n");
    printf("Enter 7 for Kruskals Spanning Tree \n");
    scanf("%d",&problemNo);

    printf("Enter 1 for Directed\nEnter 0 for Undirected\n");
    scanf("%d",&isDirected);

    printf("Enter the no of Vertices: ");
    int ver;
    scanf("%d",&ver);

    Graph g;
    
    
    printf("Enter the no of Edges: ");
    int edge;
    scanf("%d",&edge);
    printf("****************************************************************************\n");
    if(problemNo < 6){
        printf("Enter the edges by space (or newline) separated list of integers\n Note the vertex numbering starts from 0\n");
        printf("For example if we have a 3 vertex graph, then the veritces are numbered 0,1,2\n");
        printf("If the directed edges are 0-1 and 0-2 then you should enter\n");
        printf("0 1 0 2\n");

        printf("For a 3 vertex undirected graph where only 0-2 is an edge. Entering only one direction of the edge would suffice\n");
        printf("You may enter\neither\n");
        printf("0 2\nor\n");
        printf("2 0\n");
    }
    else{
        printf("Enter the edges by space (or newline) separated list of integers\n Note the vertex numbering starts from 0\n");
        printf("Every edge in the pattern <start> <end> <weight>\n");
        printf("For example if we have a 3 vertex graph, then the veritces are numbered 0,1,2\n");
        printf("If the directed edges are 0-1 and 0-2 with respective weights 3 and 4\n then you should enter\n");
        printf("0 1 3 0 2 4\n");

        printf("For a 3 vertex undirected graph where only 0-2 is an edge with weight=5. Entering only one direction of the edge would suffice\n");
        printf("You may enter\neither\n");
        printf("0 2 5\nor\n");
        printf("2 0 5\n");
    }
    printf("****************************************************************************\n");

    printf("Now please enter the edges in the way mentioned above\n");
    int arr[20000];
    int i=0;
    
    if(problemNo <6){
        initGraph(&g,ver,MATRIX);
        for ( i = 0; i < 2*edge; i++)
        {
            scanf("%d",&arr[i]);
        }
        createGraphFromInput(&g,isDirected,arr,2*edge);
    
    }
    else if(problemNo==7){
        initGraph(&g,ver,MATRIX);
        for ( i = 0; i < 3*edge; i++)
        {
            scanf("%d",&arr[i]);
        }
        //createGraphFromInput(&g,isDirected,arr,2*edge);
        createGraphFromInputWeight(&g,isDirected,arr,3*edge);
    }
    else{
        for ( i = 0; i < 3*edge; i++)
        {
            scanf("%d",&arr[i]);
        }
    }
    
    //printGraph(&g);

    switch (problemNo)
    {
        case 1:
            dfs(&g);
            break;
        
        case 2:
            findscc(&g);
            break;
        case 3:
            findAP(&g);
            break;
        case 4:
            findBridge(&g);
            break;
        case 5:
            findTopo(&g);
            break;
        case 6:
            dijsktra(&g);
            break;
        case 7:
            kruskal(arr,3*edge,isDirected,ver);
            break;
        default:
            break;
    }
    return 0;
}