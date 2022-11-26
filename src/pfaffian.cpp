#include "pfaffian.hpp"

int BipartitePfaffianVerification(const GraphContainer &G){
    GraphContainer G_copy = G;
    /* Initial verification
     * Check whether the input graph is bipartite and matching covered.
     */
    if (!G_copy.ComputeBipartite()) {
        cerr << "The input graph isn't bipartite!" << endl;
        return NotBipartite;
    }
    
    if (!G_copy.KuhnMunkres()) {
        cerr << "The input graph has no perfect matching!" << endl;
        return NotPerfectMatching;
    }

    /* Removal of inadmissibleEdges
     *
     */
    //GraphContainer matching_covered_graph = RemovalInadmissibleEdges(G);
    //G.ShowGraph("After the removal_inadmissible_edges");
    //vector<GraphContainer> matching_covered_components = FindConnectedComponents(matching_covered_graph);

    // The two lines below should be removed
    //vector<GraphContainer> matching_covered_components;
    //matching_covered_components.push_back(G_copy);

    /* Tight Cut Decoposition
     *
     */
    /*vector<GraphContainer> braces = DecomposeInTightCuts(matching_covered_components);

    int count = 0;
    for (vector<GraphContainer>::iterator it = braces.begin(); it != braces.end(); ++it) {
        auto stream = std::stringstream{};
        stream << "Brace " << count++;
        (*it).ShowGraph(stream.str());
    }*/

    /* Four Sum Decomposition
     *
     */
    //DecomposeInFourSum(G);

    //Planar Verification
    //is_planar(G);

    



    return IsPfaffian;
}