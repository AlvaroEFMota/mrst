#include "utils.hpp"

vector<pair<pair<int,int>,pair<int,int>>> list_all_pair_of_edges_not_adjacent(const GraphContainer &G_const) {
    vector<pair<int,int> > edges_list = G_const.ListAllEdges();
    vector<pair<pair<int, int>, pair<int, int> > > list_pair_edges;
    for (int i = 0; i < edges_list.size(); ++i) {
        for (int j = i+1; j < edges_list.size(); ++j) {
            if(edges_list[i].first != edges_list[j].first &&
                edges_list[i].first != edges_list[j].second &&
                edges_list[i].second != edges_list[j].first &&
                edges_list[i].second != edges_list[j].second) {
                list_pair_edges.push_back(make_pair(edges_list[i], edges_list[j]));
            }
        }
    }

    /*for (vector<pair<pair<int, int>, pair<int, int> > >:: iterator it = list_pair_edges.begin(); it != list_pair_edges.end(); ++it) {
        cout << "[{" << (*it).first.first << ", " << (*it).first.second << "}, {" << (*it).second.first << ", " << (*it).second.second <<"}]" << endl;
    }*/

    return list_pair_edges;
}

int BoolToInt(bool value) {
    if (value)
        return 1;
    return 0;
}

vector<vector<int> > list_all_3_vertices_of_quadrilaterals(const GraphContainer &G_const) {
    assert(G_const.bipartitionComputed);

    vector<vector<int>> all_3_vertices_of_quadrilaterials;

    for(int i = 0; i < G_const.n_vert; ++i) {
        for(int j = i+1; j < G_const.n_vert; ++j) {
            for(int k = j+1; k < G_const.n_vert; ++k) {
                int sum = BoolToInt(G_const.part[i])+BoolToInt(G_const.part[j])+BoolToInt(G_const.part[k]);
                if(sum == 1 || sum == 2) {
                    vector<int> vertices = {i,j,k};
                    all_3_vertices_of_quadrilaterials.push_back(vertices);
                }
            }
        }
    }

    return all_3_vertices_of_quadrilaterials;
}