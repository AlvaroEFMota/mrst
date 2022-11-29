//fazendo commit na master
#include "GraphContainer.hpp"
#include "pfaffian.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    GraphContainer G;
    G.GraphInitFromStdin();
    G.ShowGraph("Initial Graph");
    if (test_heawood_verification(G)) {
        cout << "The input is isomorph to the Heawood" << endl;
    } else {
        cout << "The input is not the Heawood graph" << endl;
    }
    // if (BipartitePfaffianVerification(G)) {
    //     cout << "The graph is bipartite pfaffian!" << endl;
    // }
    

    return 0;
}