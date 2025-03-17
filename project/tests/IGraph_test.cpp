#include "Graph_test.hpp"

#include "ListGraph.hpp"

int main()
{
    IGraph *ptr = new ListGraph(0);
    delete ptr;
    return 0;
}
