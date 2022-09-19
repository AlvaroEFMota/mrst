#ifndef TIGHTCUTDECOMPOSITION_HPP
#define TIGHTCUTDECOMPOSITION_HPP

#include "GraphContainer.hpp"

// Add descriptions here
vector<pair<pair<int,int>,pair<int,int>>> list_all_pair_of_edges_not_adjacent(const GraphContainer &G); // move to graph utils file
vector<GraphContainer> TightCutReduction(const GraphContainer &G); // private, may be public
vector<GraphContainer> CContraction(const GraphContainer &G, vector<bool> &shores); // private, may be public or not
vector<GraphContainer> DecomposeInTightCut(const vector<GraphContainer> &covered_matching_graphs); //Ok
#endif