#include "../GraphContainer.hpp"
#include "../PfaffianVerification.hpp"
#include <iostream>

using namespace std;

int main() {
    GraphContainer G;
    G.GraphInitFromFile("src/tests/inputs/heawood.in");

    /* Testing if G is isomorphic to the heawood graph
     */
    if (headwood_verification(G)) {
        cout << "#################################### [OK] Heawood_verification " << endl;
    } else {
        cout << "#################################### [FAIL] Heawood_verification " << endl;
    }
    
    return 0;
}