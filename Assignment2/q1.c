#include "graphAdt.h"


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
    for(i=6;i<g->v;i++)
    {
        if(!visited[i])
        {
            dfsUtil(g,i,visited);
        
            printf("\n");
        }
    }
    for(i=0;i<6;i++)
    {
        if(!visited[i])
        {
            dfsUtil(g,i,visited);
        
            printf("\n");
        }
    }
}

int main()
{
    srand(time(0)); 
    
    //makeRandomGraph(&g);

    // 8 und
    int arr[] = {0,1, 0,2, 0,3,
                1,2, 1,4, 2,5,
                3,5,4,5,5,6,4,7,6,7};
    // 6 dir
    int arr2[] = {
        0,1, 0,2,
        1,3, 1,5,
        2,3,
        3,4,
        4,1, 4,5,
        5,3
    };

    // 8 dir
    int arr3[] = {
        0,1, 0,2, 0,4,
        1,3,
        2,5,
        3,4, 3,6, 3,7,
        4,1, 4,6,
        5,0, 5,7,
        7,6
    };

    Graph g,g2,g3;
    initGraph(&g,8,MATRIX);
    initGraph(&g2,6,MATRIX);
    initGraph(&g3,8,MATRIX);

    createGraphFromInput(&g,0,arr,sizeof(arr)/sizeof(int));
    createGraphFromInput(&g2,1,arr2,sizeof(arr2)/sizeof(int));
    createGraphFromInput(&g3,1,arr3,sizeof(arr3)/sizeof(int));
    
    //dfs(&g);
    printf("\n");
    
    //dfs(&g2);
    printf("\n");
    dfs(&g3);
    printf("\n");
    
    //printGraph(&g);
    return 0;
}