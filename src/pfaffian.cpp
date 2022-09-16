#include "pfaffian.hpp"

void InitialVerification(GraphContainer &G) {
    if (!G.ComputeBipartite()) {
        cerr << "The imput graph isn't bipartite" << endl;
        exit(0);
    }
    
    
    if (!G.KuhnMunkres()) { // Create a unique function that use these functions of the blocks
        cerr << "The imput graph has no perfect matching" << endl;
        exit(0);
    }
}