#include "../GraphContainer.hpp"
#include "../pfaffian.hpp"
#include <iostream>
#include <random>

using namespace std;

#define SAMPLE_NUMBER 1
#define MAX_NUM_VERTICES 1000

GraphContainer generate_random_graph(int n_vert, int n_edge) {
    GraphContainer random_graph(n_vert);

    vector<pair<int, int> > all_possible_edges;
    for (int i = 0; i < n_vert; ++i) {
        for (int j = i+1; j < n_vert; ++j) {
            all_possible_edges.push_back(make_pair(i, j));
        }
    }

    //Shuffle edges
    for (int i = n_vert-1; i >= 0; --i) {
        int drawn_index = rand()%n_vert;
        // Swaping the indexes contents
        pair<int, int> temporary = all_possible_edges[i];
        all_possible_edges[i] = all_possible_edges[drawn_index];
        all_possible_edges[drawn_index] = temporary;
    }

    // Choosing the first n_edge elements to construct the graph
    for (int i = 0; i < n_edge; ++i) {
        random_graph.AddEdge(all_possible_edges[i].first, all_possible_edges[i].second);
    }

    return random_graph;
}

int main() {

    srand((unsigned)time(NULL));
    int pfaffian_counter = 0;
    for (int i = 3; 2*i <= MAX_NUM_VERTICES; ++i) {
        int new_i = 2*i;
        int n_total_edge = (new_i*(new_i-1))/2;
        for (int j = new_i/2; j < n_total_edge; ++j) {
            float time_sum = 0.0;
            int n_tests = 0;
            for(int k = 0; k < SAMPLE_NUMBER; ++k) {
                GraphContainer G = generate_random_graph(new_i,j);
                const clock_t begin_time = clock();
                if (BipartitePfaffianVerification(G)) {
                    float interval_time = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
                    time_sum += interval_time;
                    n_tests++;
                    pfaffian_counter++;
                    // cerr << "#################################### [OK] Pfaffian Verification n: "<<new_i<<" m: "<<j<<" sample: "<<k<< " pfaffians: " << pfaffian_counter << "  time: "<< interval_time << endl;
                } else {
                    //if(k%10000 == 0)
                     //cerr << "#################################### [FAIL] Pfaffian Verification  n: "<<new_i<<" m: "<<j<<" sample: "<<k<< " pfaffians: " << pfaffian_counter<< endl;
                }
            }
            if (n_tests != 0)
                cerr << "[TIME COMPLEXITY]\tn: "<<new_i<<"\tm: "<<j<< "\ttime: " <<fixed<< time_sum/float(n_tests) << "\tseconds\t found: " << n_tests << endl;

        }
    }

    
    return 0;
}