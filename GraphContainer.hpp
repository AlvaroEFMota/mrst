#ifndef GRAPHCONTAINER_HPP
#define GRAPHCONTAINER_HPP

#include <vector>
#include <queue>
#include <iostream>
#include <sstream>

using namespace std;

class GraphContainer
{
public:
    vector<vector<int>> graph;
    vector<bool> part;
    vector<int> matching;
    int n_vert;    // number of verteces
    int matc_size; // size of the matching

    GraphContainer();
    GraphContainer(int size);
    void GraphInitFromStdin();
    void AddEdge(int vertex1, int vertex2);
    void ComputeBipartite();
    void KuhnMunkres();
    void ShowGraph(string graph_desc);
    void RemoveEdge(int v1, int v2);
    void IsolateVerteces(vector<int> vectors);
    bool PerfectMatching();

private:
    void BfsBipartite(int source, vector<bool> &setted);
    bool BfsAugmentPath(int source);
};

#endif