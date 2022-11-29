#include "../GraphContainer.hpp"
#include "../InadmissibleEdges.hpp"
#include <iostream>

using namespace std;

int main() {
    GraphContainer G;
    G.GraphInitFromFile("src/tests/inputs/inadmissible_edges.in");

    GraphContainer matching_covered_graph = RemovalInadmissibleEdges(G);
    cout << "#################################### [OK] Heawood_verification " << endl;
    
    return 0;
}