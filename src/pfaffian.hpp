#ifndef PFAFFIAN_HPP
#define PFAFFIAN_HPP
#include "GraphContainer.hpp"
#include "InadmissibleEdges.hpp"
#include "TightCutDecomposition.hpp"

enum return_type { IsPfaffian, NotPfaffian, NotBipartite, NotPerfectMatching };

/* Add description
 * Enumeração de resultados Não bipartido, sem emparelhamento perfeito, pfaffiano, não pfaffiano
 */
int BipartitePfaffianVerification(const GraphContainer &G);

#endif