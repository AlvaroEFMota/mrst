#ifndef TIGHTCUTDECOMPOSITION_HPP
#define TIGHTCUTDECOMPOSITION_HPP

#include "GraphContainer.hpp"
#include "InadmissibleEdges.hpp" // separate the function ListAllEdges from InadmissibleEgdes file

vector<pair<pair<int,int>,pair<int,int>>> list_all_pair_of_edges_not_adjacent(GraphContainer &G);
vector<GraphContainer> TightCutReduction(GraphContainer &G);
vector<bool> FindShores(GraphContainer &G, vector<int> removed_vertices);
vector<int> BfsFindShore(GraphContainer &G, int source);

#endif