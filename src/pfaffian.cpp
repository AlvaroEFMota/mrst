#include "pfaffian.hpp"

bool BipartitePfaffianVerification(GraphContainer &G){

    /* Initial verification
     *
     */
    InitialVerification(G);

    /* Removal of inadmissibleEdges
     *
     */
    //RemovalInadmissibleEdges(G);
    //G.ShowGraph("After the removal_inadmissible_edges");
    //vector<GraphContainer> components_list = ConnectedComponents(G);

    // Should be removed
    vector<GraphContainer> components_list;
    components_list.push_back(G);

    /* Tight cut decoposition
     *
     */
    vector<GraphContainer> braces = TightCutDecompositionFunction(components_list);

    int count = 0;
    for (vector<GraphContainer>::iterator it = braces.begin(); it != braces.end(); ++it) {
        auto stream = std::stringstream{};
        stream << "Brace " << count++;
        //(*it).ComputeBipartite();
        //(*it).KuhnMunkres();
        (*it).ShowGraph(stream.str());

    }
    return true;
}

void InitialVerification(GraphContainer &G) {
    if (!G.ComputeBipartite()) {
        cerr << "The input graph isn't bipartite!" << endl;
        exit(0);
    }
    
    if (!G.KuhnMunkres()) { // Create a unique function that use these functions of the blocks
        cerr << "The input graph has no perfect matching!" << endl;
        exit(0);
    }
}