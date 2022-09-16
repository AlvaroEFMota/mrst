#include "TightCutDecomposition.hpp"

vector<GraphContainer> TightCutReduction(GraphContainer &G) {
    vector<pair<pair<int,int>,pair<int,int>>> pair_edges = list_all_pair_of_edges_not_adjacent(G);
    vector<bool> shores;
    for (vector<pair<pair<int,int>,pair<int,int>>>::iterator pair_edge = pair_edges.begin(); pair_edge != pair_edges.end(); ++pair_edge) {
        GraphContainer G_tmp = G;
        vector<int> vertices1 = {(*pair_edge).first.first,(*pair_edge).first.second};
        vector<int> vertices2 = {(*pair_edge).second.first,(*pair_edge).second.second};
        G_tmp.IsolateVerteces(vertices1);
        G_tmp.IsolateVerteces(vertices2);
        G_tmp.KuhnMunkres();
        if (!G_tmp.PerfectMatching()){
            cout << "par de arestas do corte justo " << "{" << (*pair_edge).first.first <<", " << (*pair_edge).first.second <<"}, {" << (*pair_edge).second.first << ", " << (*pair_edge).second.second << "}" << endl;
            G_tmp.ShowGraph("tmp");
            vector<int> removed_vertices = {(*pair_edge).first.first,(*pair_edge).first.second,(*pair_edge).second.first,(*pair_edge).second.second};
            shores = FindShores(G_tmp, removed_vertices);
            break;
        };
    }
    /*for (int i = 0; i < shores.size(); ++i) {
        cout << "Vertex: " << i << "  praia: "<<  shores[i] << endl;
    }*/

    vector<GraphContainer> contractions_graph = CContraction(G, shores);
    return contractions_graph;
}

vector<GraphContainer> CContraction(GraphContainer &G, vector<bool> &shores) {
    vector<GraphContainer> contractions_graph;
    contractions_graph.push_back(GenerateShoreGraph(G, shores, true));
    contractions_graph.push_back(GenerateShoreGraph(G, shores, false));
    return contractions_graph;
}

GraphContainer GenerateShoreGraph(GraphContainer &G, vector<bool> &shores, bool shore_type){
    int shore_len = 0;

    for (vector<bool>::iterator i = shores.begin(); i != shores.end(); ++i) {
        if (*i == shore_type)
            shore_len++;
    }

    GraphContainer G_shore(shore_len+1);
    int contracted_vertex = shore_len; // the last vertex of a graph with shore_len+1 vertices is shore_len vertex

    vector<int> map(G.n_vert, -1);
    int map_counter = 0;
    for (int i = 0; i < shores.size(); ++i) {
        if (shores[i] == shore_type) {
            map[i] = map_counter;
            map_counter++; 
        }
    }

    vector<pair<int, int> > all_edges = G.ListAllEdges();
    vector<pair<int, int> > shore_edges;
    vector<pair<int, int> > cut_edges;

    for (vector<pair<int, int> >::iterator edge = all_edges.begin(); edge != all_edges.end(); ++edge) {
        if (shores[(*edge).first] == shore_type && shores[(*edge).second] == shore_type) {
            shore_edges.push_back(*edge);
            cout << "shore edge: {" << (*edge).first << ", " << (*edge).second << "}" << endl;
        }
        else if (shores[(*edge).first] == shore_type || shores[(*edge).second] == shore_type) {
            cut_edges.push_back(*edge);
            cout << "cut edge: {" << (*edge).first << ", " << (*edge).second << "}" << endl;
        }
    }

    /*for (int i = 0; i < map.size(); ++i) {
        cout << "map [" << i <<" -> "<< map[i] <<"]"<< endl;
    }*/

    for (vector<Edge>::iterator edge = shore_edges.begin(); edge != shore_edges.end(); ++edge) {
        G_shore.AddEdge(map[(*edge).first], map[(*edge).second]);
    }

    for (vector<Edge>::iterator edge = cut_edges.begin(); edge != cut_edges.end(); ++edge) {
        if (map[(*edge).first] == -1) {
            G_shore.AddEdge(contracted_vertex, map[(*edge).second]);
        } else {
            G_shore.AddEdge(map[(*edge).first], contracted_vertex);
        }
    }
    
    //G_shore.ShowGraph("Shore graph");
    
    return G_shore;
}

vector<pair<pair<int,int>,pair<int,int>>> list_all_pair_of_edges_not_adjacent(GraphContainer &G) {
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

vector<bool> FindShores(GraphContainer &G, vector<int> removed_vertices) {
    vector<bool> shores(G.n_vert, false);
    bool found = false;
    int source = -1;
    for(int i = 0; i < G.n_vert && !found; ++i) {
        if (G.matching[i] == -1) {
            found = true;
            source = i;       
        }
    }

    vector<int> vertices = BfsFindShore(G, source);

    for (vector<int>::iterator i = vertices.begin(); i != vertices.end(); ++i) {
        shores[*i] = true;
    }

    // Adding removed vertices
    for (vector<int>::iterator i = removed_vertices.begin(); i != removed_vertices.end(); ++i) {
        if (G.part[*i] != G.part[source]) {
            shores[*i] = true;
        }
    }
    return shores;
}

vector<int> BfsFindShore(GraphContainer &G, int source) {
    vector<int> shore_vec;
    int target = -1;
    queue<int> my_queue;

    // 0 = white, 1 = gray, 2 = black
    vector<int> distance(G.n_vert, 0);
    vector<int> color(G.n_vert, 0);

    color[source] = 1;
    distance[source] = 0;
    my_queue.push(source);
    shore_vec.push_back(source);

    while (!my_queue.empty() && target == -1)
    {
        int vertex = my_queue.front();
        my_queue.pop();
        color[vertex] = 2;

        if (distance[vertex] % 2 == 0)
        {
            for (vector<int>::iterator it = G.graph[vertex].begin(); it != G.graph[vertex].end(); ++it)
            {
                if (color[*it] == 0)
                {
                    my_queue.push(*it);
                    color[*it] = 1; // gray
                    distance[*it] = distance[vertex] + 1;
                    if (G.matching[*it] == -1)
                    {
                        target = *it;
                        break;
                    }
                }
            }
        }
        else
        {
            int v = G.matching[vertex];
            my_queue.push(v);
            color[v] = 1;
            distance[v] = distance[vertex] + 1;
        }
    }
    for(int i = 0; i < G.n_vert; i++) {
        if (color[i] == 2) {
            shore_vec.push_back(i);
        }
    }
    return shore_vec;
}