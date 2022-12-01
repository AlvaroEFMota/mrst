#include "../GraphContainer.hpp"
#include "../TightCutDecomposition.hpp"
#include <iostream>

using namespace std;

int main() {
    GraphContainer G;
    G.GraphInitFromFile("src/tests/inputs/tight_cut_decomposition.in");
    vector<GraphContainer> graphs;
    graphs.push_back(G);
    G.ShowGraph("Input");
    vector<GraphContainer> results = DecomposeInTightCuts(graphs);

    for (auto graph: results) {
        graph.ShowGraph("component");
    }

    if (results.size() == 4) {
        cout << "#################################### [OK] Tight cut verification" << endl;
     } else {
        cout << "#################################### [FAIL] Tight cut verification" << endl;
    }
    
    return 0;
}