#include "graphAdt.h"

int main()
{
    Graph g;
    initGraph(&g,5,LIST);
    makeRandomGraph(&g);
    printGraph(&g);
}