#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct GraphContainer{
    vector<vector<int>> graph;
    std::pair<int,int> matching;
    int len;
    bool *part;
};

GraphContainer GraphInit();
void ShowGraph(GraphContainer G, string graph_desc);

int main(int argc, char *argv[]) {
    GraphContainer G = GraphInit();
}

GraphContainer GraphInit(){
    GraphContainer G;
    int num_vertex, num_edges;
    cin >> num_vertex >> num_edges;

    //Constucting the conteiner graph
    G.len = num_vertex;
    G.graph.resize(G.len);
    G.part = (bool*) malloc(sizeof(bool)*G.len);
    for (int i = 0; i < G.len; ++i) {
        G.part[i] = false;
    }

    for (int i =0; i < num_edges; ++i) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        G.graph[vertex1].push_back(vertex2);
    }

    ShowGraph(G, "Initial Graph");

    return G;
}

void ShowGraph(GraphContainer G, string graph_desc) {
    int count = 0;
    cout << "----- " << graph_desc << " -----" << endl;
    for (vector<vector<int>>::iterator i = G.graph.begin(); i != G.graph.end(); ++i){
        cout << count++ << ": ";
        for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j){
            cout << *j << " ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
}