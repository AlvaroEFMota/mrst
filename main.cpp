//#include "initial_verification.h"
//#include "types.h"

#include "GraphContainer.hpp"
#include "InadmissibleEdges.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    GraphContainer G;
    G.GraphInitFromStdin();
    G.ComputeBipartite();
    G.KuhnMunkres();
    if (!G.PerfectMatching()) {
        cerr << "The imput graph has no perfect matching" << endl;
        exit(0);
    }
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
    }
    
    return 0;
}