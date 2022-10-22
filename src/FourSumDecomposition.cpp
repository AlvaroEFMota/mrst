#include "FourSumDecomposition.hpp"

/*bool CheckQuadrilateral(const GraphContainer &G, vector<int> quadrilateral) {
    //check the map and the quadrilateral
}
*/

vector<vector<int>> find_quadrilaterals(const GraphContainer &G_const, vector<int> the_3_vertices_of_quadrilaterals) {
    assert(the_3_vertices_of_quadrilaterals.size() == 3);

    GraphContainer G = G_const;
    G.ShowGraph("Before removel");
    cout << "Quad " << the_3_vertices_of_quadrilaterals[0] << " " << the_3_vertices_of_quadrilaterals[1] << " " << the_3_vertices_of_quadrilaterals[2] << endl;
    G.RemoveVertices(the_3_vertices_of_quadrilaterals);
    G.ShowGraph("Finding Quadrilaterals");
    exit(0);

}

vector<vector<int>> find_all_quadrilaterals(const GraphContainer &G_const) {
    assert(G_const.bipartitionComputed);
    
    vector<vector<int> > all_3_vertices_of_quadrilaterals = list_all_3_vertices_of_quadrilaterals(G_const);
    vector<vector<int> > all_quadrilaterals;
    for(vector<vector<int> >::iterator i = all_3_vertices_of_quadrilaterals.begin(); i != all_3_vertices_of_quadrilaterals.end(); ++i) {
        vector<vector<int>> quadrilaterals = find_quadrilaterals(G_const, (*i));
        /*if (quadrilaterals.size() != 0) {
            for(vector<vector<int> >:iterator j = quadrilaterals.begin(); j != quadrilaterals.end(); ++j ) {
                all_quadrilaterals.push_back((*j));
            }
        }*/
    }

    return all_quadrilaterals;
}

/*vector<GraphContainer> FourSumReduction(const GraphContainer &G, vector<int> quadrilateral) {

}*/

vector<GraphContainer> DecomposeInFourSum(const GraphContainer &G_const) {
    GraphContainer G = G_const;
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

    return final_components_list;
}