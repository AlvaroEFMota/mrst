#ifndef GRAPHCONTAINER_HPP
#define GRAPHCONTAINER_HPP

#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

typedef pair<int, int> Edge;

class GraphContainer
{
private:
    bool BfsBipartite(int source, vector<bool> &setted);
    bool BfsAugmentPath(int source);
    bool isBipartite;
    void RemoveVertex(int v);
public:
    vector<vector<int>> graph; // graph[v] has the list of neighbours of v
    vector<bool> part; // part[v]= which part of the bipartition of G vertex v is in
    vector<int> matching; // matching[v]=u if and only if (u,v) is in M. Otherwise, when v is unmatched, matching[v]=-1
    int n_vert;    // number of verteces
    int matc_size; // size of the matching
    bool bipartitionComputed;
    vector<int> map; // used to map old vertex indexes to new vertex indexes
    bool isMapped;

    /* The empty constructor
     */
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
     * 
     * example of k33 input graph
     * ----- input.txt -----
     * 6 9
     * 0 3
     * 0 4
     * 0 5
     * 1 3
     * 1 4
     * 1 5
     * 2 3
     * 2 4
     * 2 5
     */
    void GraphInitFromStdin();

    /* Receive an not oriented edge described through the vertices vertex1 and
     * vertex2 and add such edge on the graph. The duplicate edge will
     * be discarded and the vertex1 must be different from vertex2.
     * vertex2 will be added in graph[vertex1] list, if it is not already there, and vice versa.
     * ( devo adicionar a alteração feita no grafo!!!!)
     **/
    void AddEdge(int vertex1, int vertex2);

    /* Compute the parts of the bipartition of the current graph. Returns false if the graph is not
     * bipartite. Returns true otherwise, and completes part field with an appropriate bipartition.
     * It returns true if the graph is bipartite, end false otherwise.
     */
    bool ComputeBipartite(); // return bool describing whether the graph is bipartite.

    /* Find the maximum matching in the current graph, if already exist any
     * matching in the current GraphContainer struct, then this algorithm will use such mathing
     * to find the maximum matching. Returns true if the mathing is perfect, returns false otherwise.
     */
    bool KuhnMunkres(); // Separete this function in another file. ##########

    /* Show the graph, the partition and the matchings.
     **/
    void ShowGraph(string graph_desc);

    /* Remove an edge of the current graph. Tt removes the edges (v1,v2) and (v2,v1), if the
     * vertices v1 and v2 are matched, the matching[v1] and matching[v2] will be setted to -1,
     * and the matc_size will be subtracted 1.
     */
    void RemoveEdge(int v1, int v2);

    /* Remove all the in the cut edges of vectors
     */
    void IsolateVerteces(vector<int> vectors);

    /* Verify if the current matching is a perfect matching. Return true if yes and false if not
     */
    bool PerfectMatching(); // change name to HasPerfectMatching. Use Kuhn Munkres algorithm inside it

    vector<pair<int,int>> ListAllEdges() const ;

    void RemoveVertices(vector<int> vertices);
};

#endif