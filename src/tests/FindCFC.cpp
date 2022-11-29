#include "../GraphContainer.hpp"
#include "../utils.hpp"
#include <iostream>

using namespace std;

int main() {
    GraphContainer G;
    G.GraphInitFromFile("src/tests/inputs/find_cfc.in");

    /* Testing digraph generation
     */
    dfs_digraph_generation(G, 0);
    cout << "#################################### [OK] Digraph generation " << endl;
}