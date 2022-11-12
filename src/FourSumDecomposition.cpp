#include "FourSumDecomposition.hpp"

/*bool CheckQuadrilateral(const GraphContainer &G, vector<int> quadrilateral) {
    //check the map and the quadrilateral
}
*/
void dfs_compute_end_time(GraphContainer &G, int source, vector<int> &end_time, int &end_time_counter) {
    for(vector<int>::iterator it = G.graph[source]; it != G.graph[source].end(); ++it) {
        dfs_compute_end_time(G, *it, end_time, end_time_counter);
    }
    end_time[source] = end_time_counter;
}

vector<int> list_cut_vertices(const GraphContainer &G_const) {
    GraphContainer G = G_const;
    vector<int> cut_vertices;
    vector<int> end_time(G.n_vert, -1, 0);
    int end_time_counter = 0;
    //Computing end time
    dfs_compute_end_time(G, 0, end_time, end_time_counter);
    return cut_vertices;
}

vector<vector<int>> find_quadrilaterals(const GraphContainer &G_const, vector<int> the_3_vertices_2_white_1_black) {
    assert(the_3_vertices_2_white_1_black.size() == 3);

    GraphContainer G = G_const;
    G.ShowGraph("Before removal");

    // Fazer um mapeamento de ida e volta antes da remoção

    vector<int> map = G.RemoveVertices(the_3_vertices_2_white_1_black);
    cout << "Showing removed vertices" << endl;
    for(int i = 0; i < the_3_vertices_2_white_1_black.size(); ++i) {
        cout <<the_3_vertices_2_white_1_black[i] << endl;
    }
    cout << "Showing the map" << endl;
    for(int i = 0; i < map.size(); ++i) {
        cout << i << "-->" << map[i] << endl;
    }

    G.ShowGraph("Finding Quadrilaterals");
    vector<int> cut_vertices = list_cut_vertices(G);
    vector<int> cut_vertices_mapped(cut_vertices.size(), 0);

    for(int i = 0; i < cut_vertices.size(); ++i) {
        cut_vertices_mapped[i] = map[cut_vertices[i]];
    }
    // Converter cut_vertices para o cut_vertices_mapped
    
    vector<vector<int> > quadrilaterals;
    /*
    for(vector<int>::iterator i = cut_vertices.begin(); i != cut_vertices.end(); ++i) {
        vector<int> possible_quadrilateral = the_3_vertices_2_white_1_black;
        possible_quadrilateral.push_back(*i);

        int n_white = 0;
        for(vector<int>::iterator j = possible_quadrilateral.begin(); j != possible_quadrilateral.end(); ++j) {
            if(G_const.part[*j]) {
                n_white++;
            }
        }

        if(n_white == 2) {
            quadrilaterals.push_back(possible_quadrilateral); //possible quadrilateral turns into a quadrilateral
        }
    }
*/
    return quadrilaterals;
}

vector<vector<int>> find_all_quadrilaterals(const GraphContainer &G_const) {
    assert(G_const.bipartitionComputed);
    
    vector<vector<int> > all_3_vertices_2_white_1_black = list_all_3_vertices_2_white_1_black(G_const);
    vector<vector<int> > all_quadrilaterals;
    for(vector<vector<int> >::iterator i = all_3_vertices_2_white_1_black.begin(); i != all_3_vertices_2_white_1_black.end(); ++i) {
        vector<vector<int>> quadrilaterals = find_quadrilaterals(G_const, (*i));
        /*if (quadrilaterals.size() != 0) {
            for(vector<vector<int> >:iterator j = quadrilaterals.begin(); j != quadrilaterals.end(); ++j ) {
                all_quadrilaterals.push_back((*j));
            }
        }*/
    }

    //for()

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