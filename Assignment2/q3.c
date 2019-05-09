/*
    for every node during dfs visit record their parent, discovery time
    after coming back from the recursive call update low, which is the lowest 
    visit time to which the vertex or any of the vertex at subtree rooted at this vertex
    // isAp,visited initially al false
    // initial val doesnt matter: disc,low,parent
    // but before dfs call parent must be set. for root it is itself

*/
#include "graphAdt.h"

int min(int a,int b)
{
    return a<b? a:b;
}

int myTime = 0;
void dfsUtil(Graph* g,int current,int* visited,int* low,int* disc,int* parent,int* isAp)
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
    printf("%d ",current);

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
                dfsUtil(g,child,visited,low,disc,parent,isAp);
                
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
int main()
{
    Graph g;
    initGraph(&g,14  ,MATRIX);

    // 10
    int arr[] = {0,1, 0,2, 0,3,
                1,2, 1,4, 2,5,
                3,5,4,5,5,6,4,7,6,7};

    // 10 und ab1
    int arr3[]={
        0,1, 0,2,
        1,2,
        2,3,
        3,4, 3,6,
        4,5, 
        5,6, 5,7,
        7,8, 7,9,
        8,9
    };

    // 14 und ab2
    int arr2[]={
        0,1, 0,2,
        1,3,
        2,3,
        3,4,
        4,5,
        5,6,
        6,7, 6,8, 6,10,
        8,9, 8,13,
        10,11, 10,12,
        11,12,
        12,13
    };


    createGraphFromInput(&g,0,arr2,sizeof(arr2)/sizeof(int));

    int *visited, *low, *disc, *parent, *isAp;
    visited = calloc(g.v,sizeof(int));
    low = calloc(g.v,sizeof(int));
    disc = calloc(g.v,sizeof(int));
    parent = calloc(g.v,sizeof(int));
    isAp = calloc(g.v,sizeof(int));
    int i;

    for ( i = 0; i < g.v; i++)
    {
        //printf("%d %d %d %d %d\n",visited[i],low[i],disc[i],parent[i],isAp[i]);
        //low[i] = INT_MAX;
    }

    dfsUtil(&g,0,visited,low,disc,parent,isAp);
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

    for(i=0;i<g.v;i++)
        if(*(isAp+i))
            printf("\n#%d is an Ap\n",i);
    

}