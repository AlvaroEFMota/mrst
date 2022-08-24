#ifndef INADMISSIBLEEDGES_HPP
#define INADMISSIBLEEDGES_HPP

#include "GraphContainer.hpp"

vector<pair<int,int>> ListAllEdges(GraphContainer &G);
void RemovalInadmissibleEdges(GraphContainer &G);
vector<GraphContainer> ConnectedComponents(GraphContainer &G);
GraphContainer FindComponent(GraphContainer &G, int source, vector<bool> &treated);

#endif
