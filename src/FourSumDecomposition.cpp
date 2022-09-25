#include "FourSumDecomposition.hpp"

bool CheckQuadrilateral(const GraphContainer &G, vector<int> quadrilateral) {
    //check the map and the quadrilateral
}

vector<vector<int>> find_quadrilaterals(const GraphContainer &G, vector<int> vertices_of_quadrilaterals) {
    assert(vertices_of_quadrilaterals.size() == 3);

    GraphContainer G_new = G;
    G_new.RemoveVertices(vertices_of_quadrilaterals)
}

vector<vector<int>> find_all_quadrilaterals(cost GraphContainer &G) {
    assert(G.bipartitionComputed);
    vector<vector<int> > all_3_vertices_of_quadrilaterals = list_all_3_vertices_of_quadrilaterals(G);
    vector<vector<int> > all_quadrilaterals;
    for(vector<vector<int> >::iterator i = all_3_vertices_of_quadrilaterals.begin(); i != all_3_vertices_of_quadrilaterals.end(); ++i) {
        vector<vector<int>> quadrilaterals = find_quadrilaterals(G, (*i));
        if (quadrilaterals.size() != 0) {
            for(vector<vector<int> >:iterator j = quadrilaterals.begin(); j != quadrilaterals.end(); ++j ) {
                all_quadrilaterals.push_back((*j));
            }
        }
    }
    return all_quadrilaterals;
}

vector<GraphContainer> FourSumReduction(const GraphContainer &G, vector<int> quadrilateral) {

}

vector<GraphContainer> DecomposeInFourSum(const GraphContainer &G) {
    vector<GraphContainer> components;
    vector<GraphContainer> final_components_list;
    if (!G.bipartitionComputed)
        G.ComputeBipartite();

    vector<vector<int> > all_quadrilateral = find_all_quadrilaterals(G);
    
    /*components.push_back(G);
    while(!components.empty()) {
        GraphContainer G_tmp = components.back();
        components.pop_back();

        for(int i = 0; i < all_quadrilaterals.size(); ++i) {
            if (CheckQuadrilateral(G_tmp, all_quadrilaterals[i])) {
                FourSumReduction(G_tmp, all_quadrilaterals[i]);
            }
        }
    }*/


}