#include "../GraphContainer.hpp"
#include "../InadmissibleEdges.hpp"
#include <iostream>

using namespace std;

int main() {
    GraphContainer G;
    G.GraphInitFromFile("src/tests/inputs/inadmissible_edges.in");

    GraphContainer matching_covered_graph = RemovalInadmissibleEdges(G);
    vector<GraphContainer> matching_covered_components = FindConnectedComponents(matching_covered_graph);
    for (auto graph: matching_covered_components) {
        graph.ShowGraph("component");
    }
    if (matching_covered_components.size() == 3) {
        cout << "#################################### [OK] Heawood_verification " << endl;
    } else {
        cout << "#################################### [FAIL] Heawood_verification " << endl;
    }
    
    return 0;
}