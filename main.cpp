#include "initial_verification.h"
#include "types.h"

using namespace std;

int main(int argc, char *argv[])
{
    GraphContainer G = GraphInit();

    if (G.len % 2 != 0)
    {
        cout << "The graph G is pfaffian by emptiness" << endl;
        exit(0);
    }

    ShowGraph(G, "Initialized Graph");
    G.remove_vertex(7);
    G.remove_vertex(3);
    KuhnMunkres(G);
    ShowGraph(G, "Vertex 7 and 3 removed");
}