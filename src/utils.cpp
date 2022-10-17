#include "utils.hpp"

vector<pair<pair<int,int>,pair<int,int>>> list_all_pair_of_edges_not_adjacent(const GraphContainer &G) {
    vector<pair<int,int> > edges_list = G.ListAllEdges();
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

vector<vector<int >> list_all_3_vertices_of_quadrilaterals(const GraphContainer &G) {
    vector<vector<int> > list_of_3_vertices;
    for (int i = 0; i < G.n_vert; ++i) {
        for (int j = i + 1; j < G.n_vert; ++j) {
            for (int k = j + 1; k < G.n_vert; ++k) {
                int part_value = BoolToInt[G.part[i]] + BoolToInt[G.part[j]] + BoolToInt[G.part[k]];
                if (part_value == 2 || part_value == 1) {
                    vector<int> vertices{i, j, k};
                    list_of_3_vertices.push_back(vertices);
                }
            }
        }
    }

    return list_of_3_vertices;
}