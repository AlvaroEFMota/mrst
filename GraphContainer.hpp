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
    vector<vector<int>> graph; // graph[v] has the list of neighbours of v
    vector<bool> part; // part[v]= which part of the bipartition of G vertex v is in
    vector<int> matching; // matching[v]=u if and only if (u,v) is in M. Otherwise, when v is unmatched, matching[v]=-1
    int n_vert;    // number of verteces
    int matc_size; // size of the matching

    /* The empty constructor*/
    GraphContainer();

    /* Returns a graph with n_vertices vertices, with an empty matching 
     * and all vertices on the same part of a bipartition */
    GraphContainer(int n_vertices);

    /* Read from the stdin the first two integers which describes the number of vertices
     * (n_vertices) and the number of edges (n_edges), respectively. Each of the folowing
     * n_edges lines describe one edge with two integers u and w, representing
     * non oriented edge (u,w). both u and w must be in [0, n_vertices-1] and the number
     * edges must be equal n_edges. Returns a GraphContainer object containing the
     * graph described in it, an empty matching, all vertices in the same part of
     * the bipartition and the n_vert and matc_size iquals to 0.
     **/
    void GraphInitFromStdin();

    /* Receive an not oriented edge described through the vertices vertex1 and
     * vertex2 and add such edge on the graph. The duplicate edge will
     * be descarted and the vertex1 must be different from vertex2.
     **/
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