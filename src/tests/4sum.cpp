#include "../GraphContainer.hpp"
#include "../pfaffian.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    GraphContainer G;
    G.GraphInitFromStdin();
    G.ShowGraph("Initial Graph");

    return 0;
}