#include "../GraphContainer.hpp"
#include "../pfaffian.hpp"
#include <iostream>
#include <random>
#include <math.h>

using namespace std;

#define SAMPLE_NUMBER 1
#define MAX_NUM_VERTICES 2000

GraphContainer generate_random_graph(int n_vert, int n_edge) {
    GraphContainer random_graph(n_vert);

    /*vector<pair<int, int> > all_possible_edges;
    for (int i = 0; i < n_vert; ++i) {
        for (int j = i+1; j < n_vert; ++j) {
            all_possible_edges.push_back(make_pair(i, j));
        }
    }*/

    /*//Shuffle edges
    for (int i = n_vert-1; i >= 0; --i) {
        int drawn_index = rand()%n_vert;
        // Swaping the indexes contents
        pair<int, int> temporary = all_possible_edges[i];
        all_possible_edges[i] = all_possible_edges[drawn_index];
        all_possible_edges[drawn_index] = temporary;
    }

    // Choosing the first n_edge elements to construct the graph
    if (n_edge < all_possible_edges.size()) {
        for (int i = 0; i < n_edge; ++i) {
            random_graph.AddEdge(all_possible_edges[i].first, all_possible_edges[i].second);
        }
    } else {
        for (int i = 0; i < all_possible_edges.size(); ++i) {
            random_graph.AddEdge(all_possible_edges[i].first, all_possible_edges[i].second);
        }
    }*/

    int maximum_attempts = int(float(n_edge)*0.05);
    int egde_count = 0;
    while (egde_count < n_edge) {
        int drawn_vertex1 = rand()%n_vert;
        int drawn_vertex2= rand()%n_vert;

        int attempts = 0;
        while (attempts < maximum_attempts) {
            if(!random_graph.ExistEdge(drawn_vertex1, drawn_vertex2)) {
                random_graph.AddEdge(drawn_vertex1, drawn_vertex2);
                ++egde_count;
                break;
           }
           drawn_vertex2 = (drawn_vertex2+1)%n_vert;
           ++attempts;
        }
    }



    return random_graph;
}

int main() {

    srand((unsigned)time(NULL));
    
    /*int pfaffian_counter = 0;
    for (int i = 565; 2*i <= MAX_NUM_VERTICES; ++i) {
        int new_i = 2*i;
        // int n_total_edge = (new_i*(new_i-1))/2;
        int n_total_edge = new_i+sqrt(new_i-1);
        // int n_total_edge = new_i*sqrt(new_i-1);
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
                }
            }
            if (n_tests != 0)
                cout << new_i<<"\t"<<j<< "\t" <<fixed<< time_sum/float(n_tests)<< endl;

        }
    }*/

    /*int num_edge = 12000;
    for (int vertex = 0; vertex < 100000/64; ++vertex) {
        int new_vertex = vertex*64;
        GraphContainer G = generate_random_graph(new_vertex, num_edge);
        const clock_t begin_time = clock();
        if (BipartitePfaffianVerification(G)) {
            float interval_time = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
            cout << new_vertex <<"\t"<<num_edge<< "\t" <<fixed<< interval_time<< endl;
        }
    }*/
    
    /*int num_vertex = 12000;
    for (int edge = 0; edge < 100000000/128; ++edge) {
        int new_edge = edge*128;
        GraphContainer G = generate_random_graph(num_vertex, new_edge);
        const clock_t begin_time = clock();
        if (BipartitePfaffianVerification(G)) {
            float interval_time = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
            cout << num_vertex<<"\t"<<new_edge<< "\t" <<fixed<< interval_time<< endl;
        }
    }*/


    for (int vertex = 1 ; vertex < 100000000/128; ++vertex) {
        /*m=1,5n m=2n m=4n m=10n m=n^(1,5) m=0,1*n^2*/
        int new_vertex = vertex*128;
        int edge = int(pow(new_vertex, 1.5));
        // int edge = int(0.1*pow(new_vertex, 2));
        GraphContainer G = generate_random_graph(new_vertex, edge);

        const clock_t begin_time = clock();
        BipartitePfaffianVerification(G);
        float interval_time = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
        cout << new_vertex<<"\t"<<edge<< "\t" <<fixed<< interval_time<< endl;
    }
    
    return 0;
}