#include "initial_verification.h"
#include "types.h"

using namespace std;

vector<pair<int,int>> list_all_edges(GraphContainer &G);
void removal_inadmissible_edges(GraphContainer &G);

int main(int argc, char *argv[])
{
    GraphContainer G = GraphInit();

    if (G.len % 2 != 0)
    {
        cout << "The graph G is pfaffian by emptiness" << endl;
        exit(0);
    }

    ShowGraph(G, "Initialized Graph");
    G.remove_vertex(7);
    G.remove_vertex(3);
    KuhnMunkres(G);
    ShowGraph(G, "Vertex 7 and 3 removed");
    G.remove_edge(2,4);
    KuhnMunkres(G);
    ShowGraph(G, "Edge (2,4) removed");
    removal_inadmissible_edges(G);
    ShowGraph(G, "After th removal_inadmissible_edges");
}

void removal_inadmissible_edges(GraphContainer &G) {
    vector<pair<int, int>> list = list_all_edges(G);
    for (vector<pair<int, int>>::iterator i = list.begin(); i != list.end(); ++i) {
        cout << (*i).first << "--" << (*i).second << endl;
        GraphContainer G_tmp = G.clone();
        vector<int> vertices;
        vertices.push_back((*i).first);
        vertices.push_back((*i).second);
        G_tmp.remove_vertex_vector(vertices);
        if (!KuhnMunkres(G_tmp)){ // it's not a perfect_matching
            cout << "Removed the inadmissble edge {" << (*i).first << ", " << (*i).second << "}" << endl;
            G.remove_edge((*i).first, (*i).second);
        }
    }
}

vector<pair<int,int>> list_all_edges(GraphContainer &G) {
    vector<pair<int,int>> list;
    for (int i = 0; i < G.graph.size(); ++i) {
        for (vector<int>::iterator j = G.graph[i].begin(); j != G.graph[i].end(); ++j) {
            cout << i << " - " << (*j) << endl;
            bool add = true;
            for (vector<pair<int, int>>::iterator k = list.begin(); k != list.end(); ++k) {
                if (((*k).first == i && (*k).second == (*j)) || ((*k).second == i && (*k).first == (*j))) {
                    add = false;
                }
            }
            if (add) {
                pair<int, int> edge;
                edge.first = i;
                edge.second = (*j);
                list.push_back(edge);
            }
        }
    }

    return list;
}