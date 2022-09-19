#include "InadmissibleEdges.hpp"

GraphContainer FindComponent(const GraphContainer &G, int source, vector<bool> &treated) {
    vector<int> map(G.n_vert, 0);
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

    GraphContainer component(n_vertices);

    for (vector<pair<int, int> >::iterator edge = edge_list.begin(); edge != edge_list.end(); ++edge) {
        component.AddEdge(map[(*edge).first], map[(*edge).second]);
    }
    return component;
}

GraphContainer RemovalInadmissibleEdges(const GraphContainer &G) {
    GraphContainer G_new = G;
    vector<pair<int, int>> list = G_new.ListAllEdges();
    for (vector<pair<int, int>>::iterator i = list.begin(); i != list.end(); ++i) {
        GraphContainer G_tmp = G_new;
        vector<int> vertices;
        vertices.push_back((*i).first);
        vertices.push_back((*i).second);
        G_tmp.IsolateVerteces(vertices);
        G_tmp.KuhnMunkres();
        
        if (!G_tmp.PerfectMatching()){ // it's not a perfect_matching
            cout << "Removed the inadmissble edge {" << (*i).first << ", " << (*i).second << "}" << endl;
            G_new.RemoveEdge((*i).first, (*i).second);
        }
    }
    return G_new;
}

vector<GraphContainer> FindConnectedComponents(const GraphContainer &G) {
    vector<GraphContainer> connected_components;
    vector<bool> treated(G.n_vert, false);

    for (int i = 0; i < G.n_vert; ++i) {
        if (treated[i] == false) {
            GraphContainer component;
            component = FindComponent(G, i, treated);
            connected_components.push_back(component);
        }
    }
    return connected_components;
}