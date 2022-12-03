#include "GraphContainer.hpp"
#include "pfaffian.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    GraphContainer G;
    G.GraphInitFromStdin();
    G.ShowGraph("Initial Graph");
    if (BipartitePfaffianVerification(G)) {
        cout << "The graph is bipartite pfaffian!" << endl;
    } else {
        cout << "The graph is'n bipartite pfaffian!" << endl;
    }
    

    return 0;
}