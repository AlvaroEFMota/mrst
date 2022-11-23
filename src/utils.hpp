#ifndef UTILS_HPP
#define UTILS_HPP

#include "GraphContainer.hpp"
#include <assert.h>
#include <stack>

vector<pair<pair<int,int>,pair<int,int>>> list_all_pair_of_edges_not_adjacent(const GraphContainer &G);
vector<vector<int> > list_all_3_vertices_2_white_1_black(const GraphContainer &G);
void dfs_digraph_generation(const GraphContainer G_const, int source);
void xyz(const GraphContainer &G_const);
int BoolToInt(bool value);
pair<vector<int>, int> FindConnectedComponentsMapInDigraph(const vector<vector<int> > &digraph, vector<pair<int, int>> end_time);
void ShowDigraph(vector<vector<int> > digraph, string str);
void ShowVecPair(vector<pair<int, int> > vec_pair, string str);
vector<pair<GraphContainer, vector<int>>> FindConnectedComponentsKeepReference(const GraphContainer &G, vector<int> &quadrilateral_removal_map);
#endif