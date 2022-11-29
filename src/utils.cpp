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

vector<vector<int> > list_all_3_vertices_2_white_1_black(const GraphContainer &G_const) {
    assert(G_const.bipartitionComputed);

    vector<vector<int>> all_3_vertices_2_white_1_black;

    for(int i = 0; i < G_const.n_vert; ++i) {
        if(G_const.part[i]) {

            for(int j = i+1; j < G_const.n_vert; ++j) {
                if(G_const.part[j]) {

                    for(int k = 0; k < G_const.n_vert; ++k) {
                        if(!G_const.part[k]) {
                            vector<int> vertices = {i, j, k};
                            all_3_vertices_2_white_1_black.push_back(vertices);
                        }
                    }
                }
            }
        }
    }

    return all_3_vertices_2_white_1_black;
}

void dfs_digraph_generation_rec(const GraphContainer &G_const, vector<vector<int> > &digraph, int vertex, vector<int> &color, vector<int> &successor) {
    color[vertex] = 1;
    for(vector<int>::const_iterator i = G_const.graph[vertex].begin(); i != G_const.graph[vertex].end(); ++i) {
        if (color[*i] == 0) {
            // cout << "Entrou em " << *i <<" Add " << vertex << "->" << *i << endl;
            color[*i] = 1;
            successor[vertex] = *i;
            digraph[vertex].push_back(*i);
            dfs_digraph_generation_rec(G_const, digraph, *i, color, successor);

        } else if (color[*i] == 1) {
            if(vertex != successor[*i]) {
                // cout << "Em " << vertex << " foi encontrado o vértice cinza " << *i << " Adicionando " << vertex <<"->"<< successor[*i] << endl;
                digraph[vertex].push_back(successor[*i]);
            }
        }
    } 
    color[vertex] = 2;
}

void dfs_digraph_generation(const GraphContainer G_const, int source) {
    vector<vector<int> > digraph(G_const.n_vert);
    // 0 = white, 1 = gray, 2 = black
    vector<int> color(G_const.n_vert, 0);
    vector<int> successor(G_const.n_vert, -1);
    dfs_digraph_generation_rec(G_const, digraph, 0, color, successor);

    // for(int i = 0; i < digraph.size(); ++i) {
        // cout << i << ": ";
        // for(vector<int>::iterator j = digraph[i].begin(); j != digraph[i].end(); ++j){
            // cout << *j << " ";
        // }
        // cout << endl;
    // }
    
}

void FindComponentMapInDigraph(const vector<vector<int> > &digraph, int source, vector<bool> &treated, vector<int> &map_vertex_component, int component_idx) {
    vector<int> color(digraph.size(), 0); // white
    
    queue<int> my_queue;
    my_queue.push(source);
    color[source] = 1;
    map_vertex_component[source] = component_idx;

    while (!my_queue.empty()) {
        int v = my_queue.front();
        //cout << "Find the " << v << endl;
        my_queue.pop();
        color[v] = 2;
        treated[v] = true;
        map_vertex_component[v] = component_idx;
        for (vector<int>::const_iterator i = digraph[v].begin(); i != digraph[v].end(); ++i) {  
            if (color[*i] == 0 && !treated[*i]) {
                my_queue.push(*i);
                color[*i] = 1;
            }

        }
    }
}
pair<vector<int>, int> FindConnectedComponentsMapInDigraph(const vector<vector<int> > &digraph, vector<pair<int, int>> end_time) {
    int component_idx = 0;
    vector<int> map_vertex_component(digraph.size(), -1);
    vector<bool> treated(digraph.size(), false);

    for (auto pair: end_time) {
        if (!treated[pair.first]) {
            //cout << "Starting from " << pair.first << " with the index " << component_idx << endl;
            FindComponentMapInDigraph(digraph, pair.first, treated, map_vertex_component, component_idx);
            component_idx++;
        }
    }

    return make_pair(map_vertex_component, component_idx);
}

void ShowDigraph(vector<vector<int> > digraph, string str) {
    cout << "----------------" << str << "---------------" << endl;
    for(int i = 0; i < digraph.size(); ++i) {
        cout << "| " << i << ": ";
        for(vector<int>::iterator j = digraph[i].begin(); j != digraph[i].end(); ++j) {
            cout << *j << " ";
        }
        cout << endl;
    }
}

void ShowVecPair(vector<pair<int, int> > vec_pair, string str) {
    cout << "===== " << str << " =====" << endl;
    for(auto pair: vec_pair) {
        cout << "$ " << pair.first << "->" << pair.second << endl;
    }
}

pair<GraphContainer, vector<int>> FindComponentKeepReference(const GraphContainer &G, int source, vector<bool> &treated, vector<int> &quadrilateral_removal_map, const GraphContainer &FirstGraph) {
    vector<int> map(FirstGraph.n_vert, -1);
    int n_vertices = 0;
    vector<pair<int, int> > edge_list;

    vector<int> color(G.n_vert, 0); // white
    
    queue<int> my_queue;
    my_queue.push(source);
    color[source] = 1;

    while (!my_queue.empty()) {
        int v = my_queue.front();
        my_queue.pop();
        map[v] = n_vertices; 
        n_vertices += 1;
        color[v] = 2;
        treated[v] = true;
        for (vector<int>::const_iterator i = G.graph[v].begin(); i != G.graph[v].end(); ++i) {  
            if (color[*i] == 0) {
                my_queue.push(*i);
                color[*i] = 1;
            }

            if (v < *i) {
                edge_list.push_back(make_pair(v, *i));
            }

        }
    }

    GraphContainer component(n_vertices+4);

    for (vector<pair<int, int> >::iterator edge = edge_list.begin(); edge != edge_list.end(); ++edge) {
        component.AddEdge(map[(*edge).first], map[(*edge).second]);
    }

    vector<int> return_map(FirstGraph.n_vert, -1);
    for(int i = 0; i < return_map.size(); ++i) {
        if (map[i] != -1) {
            return_map[map[i]] = quadrilateral_removal_map[i];
        }
    }
    return make_pair(component, return_map);
}

vector<pair<GraphContainer, vector<int>>> FindConnectedComponentsKeepReference(const GraphContainer &G, vector<int> &quadrilateral_removal_map, const GraphContainer &FirstGraph) {
    vector<pair<GraphContainer, vector<int>>> connected_components_pair;
    vector<bool> treated(G.n_vert, false);

    for (int i = 0; i < G.n_vert; ++i) {
        if (treated[i] == false) {
            pair<GraphContainer,vector<int>> component_pair;
            component_pair = FindComponentKeepReference(G, i, treated, quadrilateral_removal_map, FirstGraph);
            connected_components_pair.push_back(component_pair);
        }
    }
    return connected_components_pair;
}

//void AddVertexMap(GraphContainer &G, int map_reference) {
    
//}