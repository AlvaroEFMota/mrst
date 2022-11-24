#include "FourSumDecomposition.hpp"

bool sort_end_time_descendent_compare(pair<int,int> p1, pair<int,int> p2) {
    return p1.second > p2.second;
}

void dfs_build_graph(const GraphContainer &G, int vertex, vector<int> &color, vector<pair<int, int> > &edges, vector<int> &Q, vector<pair<int, int>> &end_time, int &end_time_count) {
    for(vector<int>::const_iterator it = G.graph[vertex].begin(); it != G.graph[vertex].end(); ++it) {
        if (color[*it] == 0) {
            cout << "Arvore " << vertex << "-->" << *it << endl;
            color[*it] = 1;
            Q[vertex] = *it;
            edges.push_back(make_pair(vertex, *it));
            dfs_build_graph(G, *it, color, edges, Q, end_time, end_time_count);
        } else if (Q[*it] != -1 && Q[*it] != vertex && color[*it] == 1){
            cout << "Em [" << vertex << ", " << *it << "] Encontrou vértice da árvore: " << *it <<". Adicionado " << vertex << "-->" << Q[*it] << endl;
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
    dfs_build_graph(G, 0, color, edges, Q, end_time, end_time_count);
    
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
    
    ShowDigraph(inv_digraph, "Digraph");
    ShowVecPair(end_time, "End Time");

    pair<vector<int>, int> result = FindConnectedComponentsMapInDigraph(inv_digraph, end_time);
    vector<int> map_components = result.first;
    int component_number = result.second;

    for(int i = 0; i < map_components.size(); ++i) {
        cout << "$ " << i << " | " << map_components[i] << endl;
    }

    vector<bool> added(inv_digraph.size(), false);
    for (int i = 0; i < inv_digraph.size(); ++i) {
        for (vector<int>::iterator j = inv_digraph[i].begin(); j != inv_digraph[i].end(); ++j) {
            if (map_components[i] != map_components[*j]) {
                if(*j > 0 && !added[*j]) {
                    added[*j] = true;
                    cut_vertices.push_back(*j);
                    cout << "treating edge " << i<<", "<< *j << "  Look at " << *j << endl;
                }
            }
        }
    }
    /*
    for (auto i: end_time)
        cout << i.first << "--" << i.second << endl;

    for (auto edge: edges)
        inv_digraph[edge.second].push_back(edge.first); // adding inverted

    for (auto edge: edges)
        digraph[edge.first].push_back(edge.second); // adding inverted

    ShowDigraph(inv_digraph, "Inv Digraph");
    ShowDigraph(digraph, "Digraph");
    

    vector<int> component_mapping(G.n_vert, -1);
    int count = 0;
    for (auto comp: components) {
        for ( int i = 0; i < comp.size(); ++i) {
            if (comp[i].size() > 0) {
                       component_mapping[i] = count;
            }
        }
        count++;
    }
    cout << "Number of components: " << components.size() << endl;
    cout << "Showing the component mapping" << endl;
    for( int i = 0; i < G.n_vert; ++i) {
        cout << "Vertex: " << i << "  component: " << component_mapping[i] << endl;
    }
*/

    

    return cut_vertices;
}

vector<vector<int>> find_quadrilaterals(const GraphContainer &G_const, vector<int> the_3_vertices_2_white_1_black) {
    assert(the_3_vertices_2_white_1_black.size() == 3);

    GraphContainer G = G_const;
    G.ShowGraph("Before removal");

    // Fazer um mapeamento de ida e volta antes da remoção
    vector<int> map = G.RemoveVertices(the_3_vertices_2_white_1_black);
    //cout << "Showing removed vertices" << endl;
    //for(int i = 0; i < the_3_vertices_2_white_1_black.size(); ++i) {
        //cout <<the_3_vertices_2_white_1_black[i] << endl;
    //}
    cout << "Showing the map" << endl;
    for(int i = 0; i < map.size(); ++i) {
        cout << i << "-->" << map[i] << endl;
    }
    vector<vector<int> > quadrilaterals;

    //vector<GraphContainer> components = FindConnectedComponents(G);
    //if (components.size() == 1) { // Do not need this, the removal of three vertices of a brace produce a connected graph
    G.ShowGraph("Finding Quadrilaterals");

    vector<int> cut_vertices = list_cut_vertices(G);
    vector<int> cut_vertices_mapped(cut_vertices.size(), 0);

    // Converting cut_vertices to the cut_vertices_mapped
    for(int i = 0; i < cut_vertices.size(); ++i) {
        cut_vertices_mapped[i] = map[cut_vertices[i]];
    }

    // Printing the mapped vertices
    for(int i = 0; i < cut_vertices_mapped.size(); ++i) {
        cout << i << "-->" << cut_vertices_mapped[i] << endl;
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

    /*// Printing the mapped vertices
    for(auto q: quadrilaterals) {
        cout <<"[quad] " << endl;
        for(int i = 0; i < q.size(); ++i) {
            cout << q[i] << ", ";
        }
        cout << endl;
    }*/
    return quadrilaterals;
}

vector<vector<int>> find_all_quadrilaterals(const GraphContainer &G_const) {
    assert(G_const.bipartitionComputed);
    
    vector<vector<int> > all_3_vertices_2_white_1_black = list_all_3_vertices_2_white_1_black(G_const);
    
    /*cout << "Printing 3 vertices" << endl;
    for(auto vec_vertices: all_3_vertices_2_white_1_black) {
        for (auto v: vec_vertices) {
            cout << v << ", ";
        }
        cout << endl;
    }*/

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
    // cout << "Showing component_pair map before modiification" << endl;
    // for (int i = 0; i < component_pair.second.size(); ++i) {
    //     cout << i << " -|- " << component_pair.second[i] << endl;
    // }

    component_pair.first.ShowGraph(" before 4 Sum");
    // for (auto quadrilateral_vertex: quadrilateral) {
    //     int vertex = component_pair.first.AddVertex();
    //     component_pair.second[vertex] = quadrilateral_vertex;
    // }
    for (int i = 0; i < quadrilateral.size(); ++i) {
        component_pair.second[component_pair.first.graph.size()-4+i] = quadrilateral[i];
    }
    component_pair.first.ShowGraph(" between ");

    // component_pair.first.ShowGraph("component_pair");

    // cout << "Showing component_pair map after modiification" << endl;
    // for (int i = 0; i < component_pair.second.size(); ++i) {
    //     cout << i << " -|- " << component_pair.second[i] << endl;
    // }

    vector<int> inv_map(component_pair.second.size(), -1);
    for (int i = 0; i < inv_map.size(); ++i) {
        if (component_pair.second[i] != -1) {
            inv_map[component_pair.second[i]] = i;
        }
    }

    // cout << "Showing component_pair inv map" << endl;
    // for (int i = 0; i < component_pair.second.size(); ++i) {
    //     cout << i << " -|- " << inv_map[i] << endl;
    // }

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

    component_pair.first.ShowGraph("4 Sum");
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

    cout << "quadrilateral to be removed  ";
    for (int i = 0; i < quadrilateral_mapped.size(); ++i) {
        cout << quadrilateral_mapped[i] << " ";
    }
    cout << endl;
    //graph_pair.first.ShowGraph("Can Remove");
    // Remove the vertices 
    vector<int> removal_map = G_tmp.OnlyRemoveVertices(quadrilateral_mapped);// I need to convert quadrilateral to mapped_aquadrilateral before removal
    // for (int i = 0; i < 4; ++i) {
    //     removal_map.push_back(-1);
    // }
    vector<pair<GraphContainer, vector<int>>> components_pair = FindConnectedComponentsKeepReference(G_tmp, removal_map, FirstGraph);
    /*cout << "Showing the removal map" << endl;
    for(int i = 0; i < removal_map.size(); ++i) {
        cout << i << " ¬ " << removal_map[i] << endl;
    }*/

    bool reduction_prerequisite = true;
    if (components_pair.size() >= 3) {
        cout << "Found" << endl;

        cout << "Showing map" << endl;
        for(int i = 0; i < graph_pair.second.size(); ++i) {
            cout << i << " -- " << graph_pair.second[i] << endl;
        }

        for (auto component_pair: components_pair) {
            component_pair.first.ShowGraph("component");
            // cout << "Showing component map" << endl;
            // for (int i =0; i< component_pair.second.size(); ++i) {
            //     cout << i << " ## " << component_pair.second[i] << endl;
            // }
            if (component_pair.first.graph.size() < 2) {
                reduction_prerequisite = false;
            } // The size must have at last 2 vertices, because the brace must have at last 6 vertices (2 + quadrilateral)
        }
    } else {
        reduction_prerequisite = false;
    }
    if (reduction_prerequisite) {
        for (auto component_pair: components_pair) {
            //cout << "Updating and showing the map" << endl;
            for (int i = 0; i < component_pair.second.size(); ++i) {
                //cout<< i << " before update " << component_pair.second[i] << endl;
                if (component_pair.second[i] != -1) {
                    component_pair.second[i] = graph_pair.second[component_pair.second[i]];
                }
                //cout<< i << " updated to " << component_pair.second[i] << endl;
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

    G.ShowGraph("FistGraph");
    components_pair.push_back(make_pair(G, initial_map));
    while(!components_pair.empty()) {
        pair<GraphContainer, vector<int>> component_pair = components_pair.back();

        components_pair.pop_back();
        bool match_quadrilateral = false;
        for(int i = 0; i < all_quadrilaterals.size() && !match_quadrilateral; ++i) {
            cout << "Calling for [" << all_quadrilaterals[i][0]<<", "<<all_quadrilaterals[i][1]<<", "<<all_quadrilaterals[i][2]<<", "<<all_quadrilaterals[i][3]<<"] for the graph size = "<< component_pair.first.graph.size()<<endl;
            vector<pair<GraphContainer, vector<int>>> braces = FourSumReduction(component_pair, all_quadrilaterals[i], G);
            cout << "Brace size = " << braces.size() << endl;
            if (braces.size() > 0){
                match_quadrilateral = true;
                for (auto brace: braces) {
                    brace.first.ShowGraph("Brace");
                    // for (int j = 0; j < brace.second.size(); ++j) {
                    //     cout << j << " @ " << brace.second[j] << endl;
                    // }
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

    for (auto comp: final_components_list) {
        comp.ShowGraph("Final");
    }

    return final_components_list;
}