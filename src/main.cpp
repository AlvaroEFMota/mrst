//fazendo commit na master
#include "GraphContainer.hpp"
#include "InadmissibleEdges.hpp"
#include "TightCutDecomposition.hpp"
#include "pfaffian.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    GraphContainer G;
    G.GraphInitFromStdin();
    InitialVerification(G);
    
    G.ShowGraph("Initial Graph");

    RemovalInadmissibleEdges(G);
    G.ShowGraph("After the removal_inadmissible_edges");
    
    vector<GraphContainer> components_list = ConnectedComponents(G);

    int count = 0;
    for (vector<GraphContainer>::iterator it = components_list.begin(); it != components_list.end(); ++it) {
        auto stream = std::stringstream{};
        stream << "Component " << count++;
        (*it).ComputeBipartite();
        (*it).KuhnMunkres();
        (*it).ShowGraph(stream.str());

        TightCutReduction((*it));
    }

    return 0;
}