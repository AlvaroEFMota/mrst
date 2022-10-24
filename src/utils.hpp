#ifndef UTILS_HPP
#define UTILS_HPP

#include "GraphContainer.hpp"
#include <assert.h>
#include <stack>

vector<pair<pair<int,int>,pair<int,int>>> list_all_pair_of_edges_not_adjacent(const GraphContainer &G);
vector<vector<int> > list_all_3_vertices_of_quadrilaterals(const GraphContainer &G);
void xyz(const GraphContainer &G_const);

#endif