#include "pfaffian.hpp"

int BipartitePfaffianVerification(const GraphContainer &G){
    GraphContainer G_copy = G;
    /* Initial verification
    */

    if (G.n_vert % 2 != 0)
    {
        cout << "The graph G is pfaffian by emptiness" << endl;
        return true;
    }

    /*
     * Check whether the input graph is bipartite and matching covered.
     */
    if (!G_copy.ComputeBipartite()) {
        cout << "The input graph isn't bipartite!" << endl;
        return false;
    }
    
    if (!G_copy.KuhnMunkres()) {
        cout << "The input graph has no perfect matching!" << endl;
        return true;
    }

    /* Removal of inadmissibleEdges
     *
     */
    GraphContainer matching_covered_graph = RemovalInadmissibleEdges(G);
    vector<GraphContainer> matching_covered_components = FindConnectedComponents(matching_covered_graph);

    cout << "Removal of inadmissible edges" << endl;
    for (auto graph: matching_covered_components) {
        graph.ShowGraph("Component");
    }
    // The two lines below should be removed
    //vector<GraphContainer> matching_covered_components;
    //matching_covered_components.push_back(G_copy);

    /* Tight Cut Decoposition
     *
     */
    vector<GraphContainer> braces = DecomposeInTightCuts(matching_covered_components);
    cout << "Tight cut decomposition" << endl;
    int count = 0;
    for (vector<GraphContainer>::iterator it = braces.begin(); it != braces.end(); ++it) {
        auto stream = std::stringstream{};
        stream << "Brace " << count++;
        (*it).ShowGraph(stream.str());
    }

    /* Four Sum Decomposition
     *
     */
    vector<GraphContainer> final_brace_list = DecomposeAllBracesInFourSum(braces);
    cout << "4 sum decomposition" << endl;
    int count2 = 0;
    for (auto brace: final_brace_list) {
        auto stream = std::stringstream{};
        stream << "final Brace " << count2++;
        brace.ShowGraph(stream.str());
    }
    
    bool pfaffian = is_all_braces_pfaffians(final_brace_list);

    return pfaffian;
}