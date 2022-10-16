#include "FourSumDecomposition.hpp"

bool CheckQuadrilateral(const GraphContainer &G, vector<int> quadrilateral) {
    //check the map and the quadrilateral
}

vector<vector<int >> list_all_3_vertices_of_quadrilaterals(const GraphContainer &G) {
    vector<vector<int> > list_of_3_vertices;
    for (int i = 0; i < G.n_vert; ++i) {
        for (int j = i + 1; j < G.n_vert; ++j) {
            for (int k = j + 1; k < G.n_vert; ++k) {
                int part_value = Bool2Int[part[i]] + Bool2Int[part[j]] + Bool2Int[part[k]];
                if (part_value == 2 || part_value == 1) {
                    vector<int> vertices{ i, j, k};
                    list_of_3_vertices.push_back(vertices);
                }
            }
        }
    }
    return list_of_3_vertices;
}

vector<vector<int> > find_quadrilaterals(const Graphcontainer &G, vector<vector<int> > _3_vertices) {
    GraphContainer G_new = G;
    vector<vector<int> > quadrilaterals;
    G_new.RemoveVertices(_3_vertices);
    vector<int> cut_vertices = find_cut_vertices(G_new);
    for(vector<int>::iterator i = cut_vertices.begin(); i != cut_vertices.end(); ++i) {
        if(Bool2Int(G.part[_3_vertices[0]]) + Bool2Int(G.part[_3_vertices[0]]) + Bool2Int(G.part[_3_vertices[0]]) + Bool2Int(G.part[i]) == 2) {
            vector<int> qualdrilateral = *i;
            qualdrilateral.push_back(*i);
            quadrilaterals.push_back(qualdrilateral);
        }
    }
    return quadrilaterals;
}

vector<vector<int> > list_all_quadrilaterals(vector<vector<int>> list_of_3_vertices) {
    for(vector<vector> >::iterator it = list_of_3_vertices.begin; it != list_of_3_vertices.end(); ++it) {
        find_quadrilaterals()
    }
}

vector<vector<int>> find_quadrilaterals(const GraphContainer &G, vector<int> vertices_of_quadrilaterals) {
    assert(vertices_of_quadrilaterals.size() == 3);

    GraphContainer G_new = G;
    G_new.RemoveVertices(vertices_of_quadrilaterals);
}

vector<vector<int>> find_all_quadrilaterals(const GraphContainer &G) {
    assert(G.bipartitionComputed);
    vector<vector<int> > all_3_vertices_of_quadrilaterals = list_all_3_vertices_of_quadrilaterals(G);
    vector<vector<int> > all_quadrilaterals;
    for(vector<vector<int> >::iterator i = all_3_vertices_of_quadrilaterals.begin(); i != all_3_vertices_of_quadrilaterals.end(); ++i) {
        vector<vector<int>> quadrilaterals = find_quadrilaterals(G, (*i));
        if (quadrilaterals.size() != 0) {
            for(vector<vector<int> >::iterator j = quadrilaterals.begin(); j != quadrilaterals.end(); ++j ) {
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
s
    vector<vector<int> > all_quadrilaterals = find_all_quadrilaterals(G);
    
    for(vector<vector<int> >::iterator i = all_quadrilaterals.begin(); i != all_quadrilaterals.end(); ++i) {
        for(vector<int>::iterator j = i->begin(); j != i->end(); ++j) {
            cout << (*j) << ' ' <<;
        }
        cout << endl;
    }

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