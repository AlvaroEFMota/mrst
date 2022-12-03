#include "pfaffian.hpp"

int BipartitePfaffianVerification(const GraphContainer &G){
    GraphContainer G_copy = G;
    /* Initial verification
    */

    if (G.n_vert % 2 != 0)
    {
        cerr << "The graph G is pfaffian by emptiness" << endl;
        return true;
    }

    /*
     * Check whether the input graph is bipartite and matching covered.
     */
    if (!G_copy.ComputeBipartite()) {
        cerr << "The input graph isn't bipartite!" << endl;
        return false;
    }
    
    if (!G_copy.KuhnMunkres()) {
        cerr << "The input graph has no perfect matching!" << endl;
        return true;
    }

    /* Removal of inadmissibleEdges
     *
     */
    GraphContainer matching_covered_graph = RemovalInadmissibleEdges(G);
    vector<GraphContainer> matching_covered_components = FindConnectedComponents(matching_covered_graph);

    /* Tight Cut Decoposition
     *
     */
    vector<GraphContainer> braces = DecomposeInTightCuts(matching_covered_components);
    int count = 0;

    /* Four Sum Decomposition
     *
     */
    vector<GraphContainer> final_brace_list = DecomposeAllBracesInFourSum(braces);
    int count2 = 0;
    
    bool pfaffian = is_all_braces_pfaffians(final_brace_list);

    return pfaffian;
}