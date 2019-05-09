/*
    Kruskals algorithm with union finding
*/

#include <stdio.h>
#include<stdlib.h>

#define NO_VERTEX 6

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

int main()
{
    // sort edges according to weight
    // 10 und
    int ab[] = {
        0,1,6, 0,2,3, 0,3,9,
        1,2,4, 1,4,2, 1,5,9,
        2,3,9, 2,4,2, 2,6,9,
        3,6,8, 3,9,18,
        4,5,9, 4,6,8,
        5,6,7, 5,7,4, 5,8,5,
        6,8,9, 6,9,10,
        7,8,1, 7,9,4,
        8,9,3
    };

    // 6 und 
    int ab2[] = {
        0,1,5, 0,2,6, 0,3,4,
        1,2,1, 1,3,2,
        2,3,2, 2,5,3, 2,4,5,
        3,5,4, 
        4,5,4       
        };
    
    
    int len = sizeof(ab2)/(sizeof(int));
    Edge* edgelist = (Edge*)calloc(len/3,sizeof(Edge));
    
    int i;
    for (i = 0; i < len; i+=3)
    {
       edgelist[i/3].u = ab2[i];
       edgelist[i/3].v = ab2[i+1];
       edgelist[i/3].w = ab2[i+2];
       //printf("%d %d %d\n",edgelist[i/3].u,edgelist[i/3].v,edgelist[i/3].w);
    }
    
    /*
    // add edge 0-1 
    edgelist[0].u = 0; 
    edgelist[0].v = 1; 
    edgelist[0].w = 10; 
  
    // add edge 0-2 
    edgelist[1].u = 0; 
    edgelist[1].v = 2; 
    edgelist[1].w = 6; 
  
    // add edge 0-3 
    edgelist[2].u = 0; 
    edgelist[2].v = 3; 
    edgelist[2].w = 5; 
  
    // add edge 1-3 
    edgelist[3].u = 1; 
    edgelist[3].v = 3; 
    edgelist[3].w = 15; 
  
    // add edge 2-3 
    edgelist[4].u = 2; 
    edgelist[4].v = 3; 
    edgelist[4].w = 4; 

    

    int i;
    /*
    for (i = 0; i < 10; i++)
    {
        printf("%d ",edgelist[i].w);
    }*/

    // add each edge in a set
    qsort(edgelist,len/3,sizeof(Edge),&compareEdge);

    // initialize set
    Set* sets = calloc(NO_VERTEX,sizeof(Set));
    for(i=0;i<NO_VERTEX;i++)
    {
        sets[i].parent = i;
        sets[i].rank = 0;
    }

    // extract min edges everytime and if it doesnt create a cycle
    // add to shortest path
    // V-1 edges need to be added
    int count=0;
    i=0;
    while(count<NO_VERTEX-1 && i<len/3)
    {
        // extract min weight edge everytime
        Edge e = edgelist[i];
        int a = findSet(sets,e.u);
        int b = findSet(sets,e.v);

        // if they dont create a cycle add it
        if( a!=b)
        {
            unionSet(sets,a,b);
            printf("%d-%d ----> %d\n",e.u,e.v,e.w);
            count++;
        }
        i++;
    }
}