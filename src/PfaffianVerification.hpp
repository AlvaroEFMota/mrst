#ifndef PFAFFIANVERIFICATION_HPP
#define PFAFFIANVERIFICARION_HPP

#include "GraphContainer.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

bool is_all_braces_pfaffians(const vector<GraphContainer> braces);

#endif