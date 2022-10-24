#include "../GraphContainer.hpp"
#include "../utils.hpp"
#include <iostream>

using namespace std;

int main() {
    GraphContainer G;
    G.GraphInitFromFile("src/tests/inputs/find_cfc.in");
    G.ShowGraph("Finding CFC");
    xyz(G);
}