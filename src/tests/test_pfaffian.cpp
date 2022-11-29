#include "../GraphContainer.hpp"
// #include "../InadmissibleEdges.hpp"
// #include "../TightCutDecomposition.hpp"
// #include "../FourSumDecomposition.hpp"
// #include "../PfaffianVerification.hpp"
#include "../pfaffian.hpp"
#include <iostream>

using namespace std;

int main() {
    GraphContainer G;
    G.GraphInitFromFile("src/tests/inputs/test_pfaffian.in");
    G.ShowGraph("Esse mesmo");
    if (BipartitePfaffianVerification(G)) {
        cout << "#################################### [OK] Pfaffian Verification " << endl;
    } else {
        cout << "#################################### [FAIL] Pfaffian Verification " << endl;
    }
    
    return 0;
}