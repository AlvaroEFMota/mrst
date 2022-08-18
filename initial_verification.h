#ifndef INITIAL_VERIFICATION_H
#define INITIAL_VERIFICATION_H

#include "types.h"

using namespace std;

GraphContainer GraphInit();
void ShowGraph(GraphContainer &G, string graph_desc);
void CalculateBipartite(GraphContainer &G);
void BfsBipartite(GraphContainer &G, int source, bool *setted);
bool KuhnMunkres(GraphContainer &G);
bool BfsAugmentPath(GraphContainer &G, int source);


#endif