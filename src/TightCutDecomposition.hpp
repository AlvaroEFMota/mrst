#ifndef TIGHTCUTDECOMPOSITION_HPP
#define TIGHTCUTDECOMPOSITION_HPP

#include "GraphContainer.hpp"
#include "InadmissibleEdges.hpp" // separate the function ListAllEdges from InadmissibleEgdes file

vector<pair<pair<int,int>,pair<int,int>>> list_all_pair_of_edges_not_adjacent(GraphContainer &G);
vector<GraphContainer> TightCutReduction(GraphContainer &G);
vector<bool> FindShores(GraphContainer &G, vector<int> removed_vertices);
vector<int> BfsFindShore(GraphContainer &G, int source); // make it private
vector<GraphContainer> CContraction(GraphContainer &G, vector<bool> &shores);
GraphContainer GenerateShoreGraph(GraphContainer &G, vector<bool> &shores, bool shore);
vector<GraphContainer> TightCutDecompositionFunction(vector<GraphContainer> &covered_matching_graphs);
#endif