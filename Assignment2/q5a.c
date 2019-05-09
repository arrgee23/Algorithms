#include "graphAdt.h"
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

int main()
{
    Graph g;
    initGraph(&g,6  ,MATRIX);
    int arr[] = {0,1, 0,2, 0,3,
                1,2, 1,4, 2,5,
                3,5,4,5,5,6,4,7,6,7};

    int arr3[]={0,1,1,2,0,2,
                2,4,4,3,3,5,5,6,6,4,
                5,7,7,8,8,9,9,7
                };

    int arr2[]={0,1,0,2,1,3,3,2,
                3,4, 4,5, 5,6, 6,7, 6,8, 
                8,9, 9,10, 10,11, 11,12, 12,13,
                6,12
                };
    int a[] = {0,1,4, 0,7,8,
                1,2,8, 1,7,11,
                2,3,7, 2,5,4, 2,8,2,
                3,4,9, 3,5,14,
                4,5,10, 
                5,6,2,
                6,7,1, 6,8,6,
                7,8,7,
            };

    // 6 dir ab2
    int ab2[] = {0,1,-1, 0,2,2, 0,4,4,
                1,3,3, 1,4,1,
                2,4,2, 2,5,3,
                4,3,1, 4,5,2
                    };
    // 6 ab1 und
    int ab1[] = {
        0,1,14, 0,2,9, 0,3,7,
        1,2,2, 1,4,9,
        2,3,10, 2,5,11,
        3,5,15,
        4,5,6
    };
    //createGraphFromInput(&g,0,a,sizeof(a)/sizeof(int));
    createGraphFromInputWeight(&g,1,ab2,sizeof(ab2)/sizeof(int));
    
    //printGraph(&g);
    /* create the (weight,nodId) array for every vertex 
    // init all to max except initial vertex
    // put that in the minQueue
    */

    // indicates wheather it is in sptset
    int* spset = calloc(g.v,sizeof(int));
    int* parent = calloc(g.v,sizeof(int));
    Pair* nodes = calloc(g.v,sizeof(Pair));
    int* weights = calloc(g.v,sizeof(int));
    // initialize index and item o
    int i;
    for ( i = 0; i < g.v; i++)
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
    for ( i = 0; i < g.v; i++)
        insert(h,(void*)(nodes+i));

    
    int addCount = 0;

    while(addCount<g.v)
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
            int* mat = g.graph;
            int v;

            // relax weights of all nodes adjacent to it
            for(v=0;v<g.v;v++)
            {
                // there is an edge to v th node
                if(*(mat+g.v*u+v) > 0 && !spset[v])
                {
                    int uvedge = *(mat+g.v*u+v);

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
    for ( i = 0; i < g.v; i++)
    {
        printf("%d\t%d\t%d\n",i,parent[i],weights[i]);
    }
    

    return 0;
}