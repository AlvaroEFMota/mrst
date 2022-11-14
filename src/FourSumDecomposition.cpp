#include "FourSumDecomposition.hpp"

/*bool CheckQuadrilateral(const GraphContainer &G, vector<int> quadrilateral) {
    //check the map and the quadrilateral
}
*/

bool sort_end_time_descendent_compare(pair<int,int> p1, pair<int,int> p2) {
    return p1.second > p2.second;
}

/*void dfs_compute_end_time(const GraphContainer &G, int source, vector<pair<int,int>> &end_time, int &end_time_counter, vector<int> &color, vector<pair<int, int> > &edges, vector<int> &Q) {
    for(vector<int>::const_iterator it = G.graph[source].begin(); it != G.graph[source].end(); ++it) {
        if (color[*it] == 0) {
            cout << "Arvore " << source << "-->" << *it << endl;
            color[*it] = 1;
            Q[source] = *it;
            edges.push_back(make_pair(source, *it));
            dfs_compute_end_time(G, *it, end_time, end_time_counter, color, edges, Q);
        } else if (Q[*it] != -1 && color[*it] == 2){
            cout << "Em [" << source << ", " << *it << "] Encontrou vértice da árvore: " << *it << endl;
            edges.push_back(make_pair(source, Q[*it]));
        }
    }
    color[source] = 2;
    end_time.push_back(make_pair(source, end_time_counter));
    end_time_counter++;
}*/

void dfs_build_inv_digraph(const GraphContainer &G, int vertex, vector<int> &color, vector<pair<int, int> > &edges, vector<int> &Q, vector<pair<int, int>> &end_time, int &end_time_count) {
    for(vector<int>::const_iterator it = G.graph[vertex].begin(); it != G.graph[vertex].end(); ++it) {
        if (color[*it] == 0) {
            cout << "Arvore " << vertex << "-->" << *it << endl;
            color[*it] = 1;
            Q[vertex] = *it;
            edges.push_back(make_pair(vertex, *it));
            dfs_build_inv_digraph(G, *it, color, edges, Q, end_time, end_time_count);
        } else if (Q[*it] != -1 && Q[*it] != vertex && color[*it] == 1){
            cout << "Em [" << vertex << ", " << *it << "] Encontrou vértice da árvore: " << *it <<". Adicionado " << vertex << "-->" << Q[*it] << endl;
            edges.push_back(make_pair(vertex, Q[*it]));
        }
    }
    color[vertex] = 2;
    end_time.push_back(make_pair(vertex, end_time_count));
    end_time_count++;
}

vector<vector<int>> build_inv_digraph(const GraphContainer &G, vector<pair<int, int>> &end_time, int &end_time_count) {
    vector<int> color(G.n_vert, 0);
    vector<pair<int, int> > edges;
    vector<int> Q(G.n_vert, -1);
    vector<vector<int>> digraph(G.n_vert);

    color[0] = 1;
    dfs_build_inv_digraph(G, 0, color, edges, Q, end_time, end_time_count);
    
    for (auto edge: edges) {
        digraph[edge.second].push_back(edge.first);
    }

    return digraph;
}

vector<int> list_cut_vertices(const GraphContainer &G) {
    vector<int> cut_vertices;

    vector<pair<int, int>> end_time;
    int end_time_count = 0;

    vector<vector<int>> inv_digraph = build_inv_digraph(G, end_time, end_time_count);
    sort(end_time.begin(), end_time.end(), sort_end_time_descendent_compare);
    
    ShowDigraph(inv_digraph, "Digraph");
    ShowVecPair(end_time, "End Time");

    pair<vector<int>, int> result = FindConnectedComponentsInDigraphPreservingLabel(inv_digraph, end_time);
    vector<int> map_components = result.first;
    int component_nnumber = result.second;

    for(int i = 0; i < map_components.size(); ++i) {
        cout << "$ " << i << " | " << map_components[i] << endl;
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
    cout << "Showing removed vertices" << endl;
    for(int i = 0; i < the_3_vertices_2_white_1_black.size(); ++i) {
        cout <<the_3_vertices_2_white_1_black[i] << endl;
    }
    cout << "Showing the map" << endl;
    for(int i = 0; i < map.size(); ++i) {
        cout << i << "-->" << map[i] << endl;
    }
    vector<GraphContainer> components = FindConnectedComponents(G);
    vector<vector<int> > quadrilaterals;

    //if (components.size() == 1) { // Do not need this, the removal of three vertices of a brace produce a connected graph
    G.ShowGraph("Finding Quadrilaterals");

    vector<int> cut_vertices = list_cut_vertices(G);
    vector<int> cut_vertices_mapped(cut_vertices.size(), 0);

    for(int i = 0; i < cut_vertices.size(); ++i) {
        cut_vertices_mapped[i] = map[cut_vertices[i]];
    }
    exit(0);
    // Converter cut_vertices para o cut_vertices_mapped
    
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
    } */

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