#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct GraphContainer
{
    vector<vector<int>> graph;
    int *matching; //if mathing[5]=6, the edge {5,6} is in the matching, if matching[5]=-1 otherwise.
    int len;
    bool *part;
};

GraphContainer GraphInit();
void ShowGraph(GraphContainer &G, string graph_desc);
void CalculateBipartite(GraphContainer &G);
void BfsBipartite(GraphContainer &G, int source, bool *setted);
void KuhnMunkres(GraphContainer &G);

int main(int argc, char *argv[])
{
    GraphContainer G = GraphInit();

    if (G.len%2 != 0) {
        cout << "The graph G is pfaffian by emptiness" << endl;
        exit(0);
    }
}

GraphContainer GraphInit()
{
    GraphContainer G;
    int num_vertex, num_edges;
    cin >> num_vertex >> num_edges;

    // Constucting the conteiner graph
    G.len = num_vertex;
    G.graph.resize(G.len);
    G.part = (bool *)malloc(sizeof(bool) * G.len);
    G.matching = (int *)malloc(sizeof(int) * G.len);
    for (int i = 0; i < G.len; ++i)
    {
        G.matching[i] = -1;
        G.part[i] = false;
    }

    for (int i = 0; i < num_edges; ++i)
    {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        G.graph[vertex1].push_back(vertex2);
        G.graph[vertex2].push_back(vertex1);
    }

    ShowGraph(G, "Initial Graph");

    CalculateBipartite(G);

    return G;
}

void ShowGraph(GraphContainer &G, string graph_desc)
{
    int count = 0;
    cout << "----- " << graph_desc << " -----" << endl;
    for (vector<vector<int>>::iterator i = G.graph.begin(); i != G.graph.end(); ++i)
    {
        cout << count++ << ": ";
        for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j)
        {
            cout << *j << " ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
}

void CalculateBipartite(GraphContainer &G)
{
    // setted is a vector thar store information about if the partition of a vertex was setted.
    bool *setted = (bool *)malloc(sizeof(bool) * G.len);
    for (int i = 0; i < G.len; ++i)
    {
        setted[i] = false;
    }
    cout << "sei la pra que serve: " << *setted << endl;

    for (int source = 0; source < G.len; ++source)
    {
        if (setted[source] == false)
        {
            BfsBipartite(G, source, setted);
        }
    }

    free(setted);
}

void BfsBipartite(GraphContainer &G, int source, bool *setted)
{
    queue<int> my_queue;
    // 0 = white, 1 = gray, 2 = black
    int *color = (int *)malloc(sizeof(int) * G.len);
    for (int i = 0; i < G.len; ++i)
    {
        color[i] = 0; // white
    }

    color[source] = 1;
    G.part[source] = true;
    setted[source] = true;

    my_queue.push(source);

    while (!my_queue.empty())
    {
        int vertex = my_queue.front();
        cout << "passando por " << vertex << endl;
        my_queue.pop();
        color[vertex] = 2; // black
        for (vector<int>::iterator it = G.graph[vertex].begin(); it != G.graph[vertex].end(); ++it)
        {
            if (setted[*it] == true && G.part[vertex] == G.part[*it]) {
                cout << "The graph isn't bipartite pfaffian" << endl;
                exit(0);
            }
            if (color[*it] == 0)
            {
                cout << "Adicionando o vertice " << *it << " na fila" << endl;
                my_queue.push(*it);
                color[*it] = 1; // gray
                G.part[*it] = !G.part[vertex];
                setted[*it] = true;
            }
        }
    }

    free(color);
}

/*void KuhnMunkres(GraphContainer &G) {
    bool modified = true;
    while (modified) {
        modified = false;
        for (int i = 0; i < G.len; ++i) {
            if (G.matching[i] == -1) {
                
            }
        }
    }
}

bool BfsKuhnMunkres(GraphContainer &G, int source) {

}*/