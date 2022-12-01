#include "../GraphContainer.hpp"
#include "../FourSumDecomposition.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    GraphContainer G;
    G.GraphInitFromFile("src/tests/inputs/four_sum_decomposition.in");
    vector<GraphContainer> braces;
    braces.push_back(G);
    vector<GraphContainer> response = DecomposeAllBracesInFourSum(braces);
    for (auto graph: response) {
        graph.ShowGraph("Componen from 4 sum decomposition");
    }
    if (response.size() == 5) {
        cout << "#################################### [OK] 4 Sum Decomposition " << endl;
    } else {
        cout << "#################################### [FAIL] 4 Sum Decomposition " << endl;
    }
    return 0;
}