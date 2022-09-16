#ifndef INADMISSIBLEEDGES_HPP
#define INADMISSIBLEEDGES_HPP

#include "GraphContainer.hpp"

vector<pair<int,int>> ListAllEdges(GraphContainer &G); // Move to GraphContainer!
void RemovalInadmissibleEdges(GraphContainer &G); // use const GraphContainer &G. Return Graphcontainer
vector<GraphContainer> ConnectedComponents(GraphContainer &G);
// lines 7 and 8 grafos cobertos por emparelhamentos do grafo.
GraphContainer FindComponent(GraphContainer &G, int source, vector<bool> &treated);
// 10 -> remove from here, keep on .cpp

#endif
