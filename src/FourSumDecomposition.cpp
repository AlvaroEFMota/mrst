#include "FourSumDecomposition.hpp"

bool sort_end_time_descendent_compare(pair<int,int> p1, pair<int,int> p2) {
    return p1.second > p2.second;
}

void dfs_build_graph(const GraphContainer &G, int vertex, vector<int> &color, vector<pair<int, int> > &edges, vector<int> &Q, vector<pair<int, int>> &end_time, int &end_time_count) {
    for(vector<int>::const_iterator it = G.graph[vertex].begin(); it != G.graph[vertex].end(); ++it) {
        if (color[*it] == 0) {
            color[*it] = 1;
            Q[vertex] = *it;
            edges.push_back(make_pair(vertex, *it));
            dfs_build_graph(G, *it, color, edges, Q, end_time, end_time_count);
        } else if (Q[*it] != -1 && Q[*it] != vertex && color[*it] == 1){
            edges.push_back(make_pair(vertex, Q[*it]));
        }
    }
    color[vertex] = 2;
    end_time.push_back(make_pair(vertex, end_time_count));
    end_time_count++;
}

pair<vector<vector<int>>, vector<vector<int>>> build_digraph_and_inverted_digraph(const GraphContainer &G, vector<pair<int, int>> &end_time, int &end_time_count) {
    vector<int> color(G.n_vert, 0);
    vector<pair<int, int> > edges;
    vector<int> Q(G.n_vert, -1);
    vector<vector<int>> digraph(G.n_vert);
    vector<vector<int>> inv_digraph(G.n_vert);

    color[0] = 1;
    for(int i = 0; i < G.n_vert; ++i){ //This for is because the G graph can be disconnected
        if (color[i] == 0) {
            dfs_build_graph(G, i, color, edges, Q, end_time, end_time_count);
        }
    }
    
    for (auto edge: edges) {
        digraph[edge.first].push_back(edge.second);
        inv_digraph[edge.second].push_back(edge.first);
    }

    return make_pair(digraph, inv_digraph);
}

vector<int> list_cut_vertices(const GraphContainer &G) {
    vector<int> cut_vertices;

    vector<pair<int, int>> end_time;
    int end_time_count = 0;

    pair<vector<vector<int>>, vector<vector<int>>> graphs = build_digraph_and_inverted_digraph(G, end_time, end_time_count);
    vector<vector<int>> digraph = graphs.first;
    vector<vector<int>> inv_digraph = graphs.second;
    sort(end_time.begin(), end_time.end(), sort_end_time_descendent_compare);
    
    pair<vector<int>, int> result = FindConnectedComponentsMapInDigraph(inv_digraph, end_time);
    vector<int> map_components = result.first;
    int component_number = result.second;

    vector<bool> added(inv_digraph.size(), false);
    for (int i = 0; i < inv_digraph.size(); ++i) {
        for (vector<int>::iterator j = inv_digraph[i].begin(); j != inv_digraph[i].end(); ++j) {
            if (map_components[i] != map_components[*j]) {
                if(*j > 0 && !added[*j]) {
                    added[*j] = true;
                    cut_vertices.push_back(*j);
                }
            }
        }
    }

    return cut_vertices;
}

vector<vector<int>> find_quadrilaterals(const GraphContainer &G_const, vector<int> the_3_vertices_2_white_1_black) {
    assert(the_3_vertices_2_white_1_black.size() == 3);

    GraphContainer G = G_const;

    vector<int> map = G.RemoveVertices(the_3_vertices_2_white_1_black);
    vector<vector<int> > quadrilaterals;


    vector<int> cut_vertices = list_cut_vertices(G);
    vector<int> cut_vertices_mapped(cut_vertices.size(), 0);

    // Converting cut_vertices to the cut_vertices_mapped
    for(int i = 0; i < cut_vertices.size(); ++i) {
        cut_vertices_mapped[i] = map[cut_vertices[i]];
    }

    for(vector<int>::iterator i = cut_vertices_mapped.begin(); i != cut_vertices_mapped.end(); ++i) {
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

    return quadrilaterals;
}

vector<vector<int>> find_all_quadrilaterals(const GraphContainer &G_const) {
    assert(G_const.bipartitionComputed);
    
    vector<vector<int> > all_3_vertices_2_white_1_black = list_all_3_vertices_2_white_1_black(G_const);
    
    vector<vector<int> > all_quadrilaterals;
    for(vector<vector<int> >::iterator i = all_3_vertices_2_white_1_black.begin(); i != all_3_vertices_2_white_1_black.end(); ++i) {
        vector<vector<int>> quadrilaterals = find_quadrilaterals(G_const, (*i));
        if (quadrilaterals.size() != 0) {
            for(vector<vector<int> >::iterator j = quadrilaterals.begin(); j != quadrilaterals.end(); ++j ) {
                all_quadrilaterals.push_back((*j));
            }
        }
    }

    return all_quadrilaterals;
}

pair<GraphContainer, vector<int>> add_quadrilateral(pair<GraphContainer, vector<int>> component_pair, vector<int> quadrilateral, const GraphContainer FirstGraph) {
    
    for (int i = 0; i < quadrilateral.size(); ++i) {
        component_pair.second[component_pair.first.graph.size()-4+i] = quadrilateral[i];
    }

    component_pair.first.ShowGraph("component_pair");

    vector<int> inv_map(component_pair.second.size(), -1);
    for (int i = 0; i < inv_map.size(); ++i) {
        if (component_pair.second[i] != -1) {
            inv_map[component_pair.second[i]] = i;
        }
    }

    for (auto quadrilateral_vertex: quadrilateral) {
        for (auto neightbor: FirstGraph.graph[quadrilateral_vertex]) {
            if (inv_map[neightbor] != -1) {
                component_pair.first.AddEdge(inv_map[quadrilateral_vertex], inv_map[neightbor]);
            }
        }
    }

    for (int i = 0; i < quadrilateral.size()-1; ++i) {
        for (int j = i+1; j < quadrilateral.size(); ++j) {
            if(FirstGraph.part[quadrilateral[i]] != FirstGraph.part[quadrilateral[j]]) {
                component_pair.first.AddEdge(inv_map[quadrilateral[i]], inv_map[quadrilateral[j]]);
            }
        }
    }

    component_pair.first.ShowGraph("Brace");
    return component_pair;
}

vector<pair<GraphContainer, vector<int>>> FourSumReduction(const pair<GraphContainer, vector<int>> &graph_pair, vector<int> quadrilateral, const GraphContainer &FirstGraph) {
    vector<pair<GraphContainer, vector<int>>> resultant_components;
    GraphContainer G_tmp = graph_pair.first;

    // convert quadrilateral using a map
    // create a inv_map
    vector<int> inv_map(FirstGraph.graph.size(), -1);
    for (int i = 0; i < inv_map.size(); ++i) {
        if (graph_pair.second[i] != -1) {
            inv_map[graph_pair.second[i]] = i;
        }
    }

    vector<int> quadrilateral_mapped;
    for (auto vertex: quadrilateral) {
        if (inv_map[vertex] == -1) {
            return resultant_components;
        }
        quadrilateral_mapped.push_back(inv_map[vertex]);
    }

    vector<int> removal_map = G_tmp.OnlyRemoveVertices(quadrilateral_mapped);// I need to convert quadrilateral to mapped_aquadrilateral before removal
    vector<pair<GraphContainer, vector<int>>> components_pair = FindConnectedComponentsKeepReference(G_tmp, removal_map, FirstGraph);
    // }

    bool reduction_prerequisite = true;
    if (components_pair.size() >= 3) {
        for (auto component_pair: components_pair) {
            if (component_pair.first.graph.size() < 6) {
                reduction_prerequisite = false;
            } // The size must have at last 2 vertices, because the brace must have at last 6 vertices (2 + quadrilateral)
        }
    } else {
        reduction_prerequisite = false;
    }
    if (reduction_prerequisite) {
        for (auto component_pair: components_pair) {
            for (int i = 0; i < component_pair.second.size(); ++i) {
                if (component_pair.second[i] != -1) {
                    component_pair.second[i] = graph_pair.second[component_pair.second[i]];
                }
            }

            pair<GraphContainer, vector<int>> brace_pair = add_quadrilateral(component_pair, quadrilateral, FirstGraph);
            resultant_components.push_back(brace_pair);
        }
    }
    return resultant_components;
}

vector<GraphContainer> DecomposeInFourSum(const GraphContainer &G_const) {
    GraphContainer G = G_const;
    vector<pair<GraphContainer, vector<int>>> components_pair;
    vector<GraphContainer> final_components_list;
    if (!G.bipartitionComputed)
        G.ComputeBipartite();

    vector<vector<int> > all_quadrilaterals = find_all_quadrilaterals(G);
    
    vector<int> initial_map(G.n_vert);
    for (int i = 0; i < initial_map.size(); ++i) {
        initial_map[i] = i;
    }

    // G.ShowGraph("FistGraph");
    components_pair.push_back(make_pair(G, initial_map));
    while(!components_pair.empty()) {
        pair<GraphContainer, vector<int>> component_pair = components_pair.back();

        components_pair.pop_back();
        bool match_quadrilateral = false;
        for(int i = 0; i < all_quadrilaterals.size() && !match_quadrilateral; ++i) {
            vector<pair<GraphContainer, vector<int>>> braces = FourSumReduction(component_pair, all_quadrilaterals[i], G);
            if (braces.size() > 0){
                match_quadrilateral = true;
                for (auto brace: braces) {
                    components_pair.push_back(brace);
                }
                //remove the used quadrilateral
                all_quadrilaterals.erase(std::next(all_quadrilaterals.begin(), i));
            }
        }

        if (!match_quadrilateral){
            final_components_list.push_back(component_pair.first);
        }

    }

    return final_components_list;
}

vector<GraphContainer> DecomposeAllBracesInFourSum(const vector<GraphContainer> braces) {
    vector<GraphContainer> final_list;
    for (auto brace: braces) {
        vector<GraphContainer> response = DecomposeInFourSum(brace);
        if (response.size() > 0) {
           for (auto item: response) {
            final_list.push_back(item);
           }
        } else {
            final_list.push_back(brace);
        }
    }
    return final_list;
}