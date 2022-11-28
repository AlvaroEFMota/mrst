#include "PfaffianVerification.hpp"

bool is_planar(const GraphContainer &G_const) {
    using namespace boost;

    typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int> > graph;

    graph G(G_const.graph.size());

    for (int i = 0; i < G_const.graph.size(); ++i) {
        for (auto j: G_const.graph[i]) {
            add_edge(i, j, G);
        }
    }

    if (boyer_myrvold_planarity_test(G)) {
        return true;
    }
    return false;
}

int v_most_mapped_neighbours(const GraphContainer &G, const vector<bool> &mapped) {
    int melhor = -1;
    int maximo = -1;
    for (int v = 0; v < G.n_vert; ++v) {
        if (!mapped[v]) {
            int conta_vizinhos_mapeados = 0;
            for (auto w: G.graph[v]) {
                if (mapped[w]) {
                    conta_vizinhos_mapeados++;
                }
            }
            if (conta_vizinhos_mapeados > maximo) {
                maximo = conta_vizinhos_mapeados;
                melhor = v;
            }
        }
    }
    return melhor;
}
bool coerente_com_ja_mapeado(const GraphContainer &G, const GraphContainer &H, int vG, int vH,
                            vector<bool> &mapped, vector<int> &map) {
    for (auto u: G.graph[vG]) {
        if (mapped[u] && find(H.graph[vH].begin(), H.graph[vH].end(), map[u]) == H.graph[vH].end()) {
            return false;
        }
    }
    return true;
}

bool isomorfism_verification_rec(const GraphContainer &G, const GraphContainer &H, vector<bool> &mapped,
                                vector<bool> &mapped_image, int n_mapped, vector<int> &map,
                                vector<int> &inv_map) {
    if (n_mapped == G.n_vert) return true;
    int current = v_most_mapped_neighbours(G, mapped);
    for (int w=0; w<H.n_vert; ++w) {
        if (!mapped_image[w]) {
            mapped[current] = true;
            mapped_image[w] = true;
            map[current] = w;
            inv_map[w] = current;
            if (coerente_com_ja_mapeado(G, H, current, w, mapped, map)) {
                if (isomorfism_verification_rec(G, H, mapped, mapped_image, n_mapped+1, map, inv_map)) {
                    return true;
                }
            }
            mapped[current] = false;
            mapped_image[w] = false;
            map[current] = -1;
            inv_map[w] = -1;
        }
    }
    return false;
}

bool isomorfism_verification(const GraphContainer &G, const GraphContainer &heawood) {
    if (G.n_vert != heawood.n_vert) return false;

    vector<bool> mapped(heawood.n_vert, false);
    vector<bool> mapped_image(heawood.n_vert, false);
    int n_mapped = 0;
    vector<int> map(heawood.n_vert, -1);
    vector<int> inv_map(heawood.n_vert, -1);
    return isomorfism_verification_rec(G, heawood, mapped, mapped_image, n_mapped, map, inv_map);
}

// bool isomorfism_verification(const GraphContainer &G, const GraphContainer &heawood, vector<int> label_map, vector<bool> used, int used_counter, int G_vertex, int label) {
//     //cout << "Chamou a função com os parametros used_counter: " << used_counter << "  G_vertex: " << G_vertex << "  label: " << label << endl;
//     label_map[G_vertex] = label;
//     used[label] = true;
//     used_counter++;
//     for (auto neighbor: G.graph[G_vertex]) {
//         if(label_map[neighbor] == -1) {
//             for (auto h_vertex: heawood.graph[label]){
//                 //cout << "testing " << h_vertex << endl;
//                 if (!used[h_vertex]) {
//                     //cout << "Chamando o vértice " << neighbor << " de " << h_vertex << endl;
//                     if (isomorfism_verification(G, heawood, label_map, used, used_counter, neighbor, h_vertex)) { return true; }
//                 }
//             }
//             return false;
//         } else {

//             // Check if is there a label not filled
//             bool filled = true;
//             for (auto v: G.graph[neighbor]){
//                 if (label_map[v] == -1) {
//                     filled = false;
//                 }
//             }

//             if (filled) {
//                 for (auto vertex: G.graph[neighbor]){
//                     // Check if is there not label_map[vertex] in heawood.graph[label_map[neighbor]]
//                     if (find(heawood.graph[label_map[neighbor]].begin(),
//                             heawood.graph[label_map[neighbor]].end(),
//                             label_map[vertex]) == heawood.graph[label_map[neighbor]].end()) {
//                         return false;
//                     }
//                 }
//             }
//             // check if it completed the map
//             if (used_counter == 14) {
//                 cout << "Permutation" << endl;
//                 for (int j = 0; j < label_map.size(); ++j) {
//                     cout << j << " -- " << label_map[j] << endl;
//                 }
//                 return true;
//             }
//         }
//     }
//     return false;
// }

GraphContainer get_heawood_graph() {
    GraphContainer heawood(14);
    heawood.AddEdge(0, 1);
    heawood.AddEdge(0, 5);
    heawood.AddEdge(1, 2);
    heawood.AddEdge(1, 10);
    heawood.AddEdge(2, 3);
    heawood.AddEdge(2, 7);
    heawood.AddEdge(3, 4);
    heawood.AddEdge(3, 12);
    heawood.AddEdge(4, 5);
    heawood.AddEdge(4, 9);
    heawood.AddEdge(5, 6);
    heawood.AddEdge(6, 7);
    heawood.AddEdge(6, 11);
    heawood.AddEdge(7, 8);
    heawood.AddEdge(8, 9);
    heawood.AddEdge(8, 13);
    heawood.AddEdge(9, 10);
    heawood.AddEdge(10, 11);
    heawood.AddEdge(11, 12);
    heawood.AddEdge(12, 13);
    heawood.AddEdge(13, 0);
    return heawood;
}

bool headwood_verification(const GraphContainer G) {
    return isomorfism_verification(G, get_heawood_graph());
    // if (G.graph.size() != 14) return false;
    // for (int i = 0; i < G.graph.size(); ++i) {
    //     if (G.graph[i].size() != 3) {
    //         return false;
    //     }
    // }
    // GraphContainer heawood = get_heawood_graph();
    // heawood.ShowGraph("Heawood");
    // vector<bool> used(14, false);
    // vector<int> label_map(14, -1);
    // int used_counter = 0;
    
    // for (int i = 0; i < heawood.graph.size(); ++i) {
    //     //cout << "#### Root ##########" << endl;
    //     if (isomorfism_verification(G, heawood, label_map, used, used_counter, 0, i)) {
    //         return true;
    //     }
    // }
    // return false;
}

bool is_brace_pfaffian(const GraphContainer brace) {
    return headwood_verification(brace) || is_planar(brace);
}

bool is_all_braces_pfaffians(const vector<GraphContainer> braces) {
    bool pfaffian = true;

    for (auto brace: braces) {
        if(!is_brace_pfaffian(brace)) {
            pfaffian = false;
        }
    }
    return pfaffian;
}