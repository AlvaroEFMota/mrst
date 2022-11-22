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
    vector<int> vertices_test = {4, 10, 5};
    vector<int> map = G.RemoveVertices(vertices_test);
    //vector<int> map = G.RemoveVertices(the_3_vertices_2_white_1_black);
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
    exit(0);
    
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

vector<pair<GraphContainer, vector<int>>> FourSumReduction(const pair<GraphContainer, vector<int>> &graph_map, vector<int> quadrilateral) {
    GraphContainer G_tmp = graph_map.first;
    vector<int> removal_map = G_tmp.RemoveVertices(quadrilateral);
    vector<GraphContainer> components = FindConnectedComponents(G_tmp);

    bool reduction_prerequisite = true;

    if (components.size() > 3) {
        for (auto component: components) {
            if (component.graph.size() < 2) {
                reduction_prerequisite = false;
            } // The size must have at last 2 vertices, because the brace must have at last 6 vertices (2 + quadrilateral)
        }
    } else {
        reduction_prerequisite = false;
    }

    vector<pair<GraphContainer, vector<int>>> resultant_components;

    if (reduction_prerequisite) {
        
    }

    

}

vector<GraphContainer> DecomposeInFourSum(const GraphContainer &G_const) {
    GraphContainer G = G_const;
    vector<pair<GraphContainer, vector<int>>> components_pair;
    vector<GraphContainer> final_components_list;
    if (!G.bipartitionComputed)
        G.ComputeBipartite();

    vector<vector<int> > all_quadrilaterals = find_all_quadrilaterals(G);
    
    /*cout << "Printing the quadrilaterals found" << endl;
    for (auto quadrilateral: all_quadrilaterals) {
        for (auto vertex: quadrilateral) {
            cout << " ~ "<< vertex;
        }
        cout << endl;
    }*/

    vector<int> initial_map(G.n_vert);
    for (int i = 0; i < initial_map.size(); ++i) {
        initial_map[i] = i;
    }

    components_pair.push_back(make_pair(G, initial_map));
    while(!components_pair.empty()) {
        pair<GraphContainer, vector<int>> component_pair = components_pair.back();

        components_pair.pop_back();

        for(int i = 0; i < all_quadrilaterals.size(); ++i) {
            FourSumReduction(component_pair, all_quadrilaterals[i]);
        }
    }

    return final_components_list;
}