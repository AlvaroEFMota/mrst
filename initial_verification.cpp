#include "initial_verification.h"

GraphContainer GraphInit()
{
    GraphContainer G;
    int num_vertex, num_edges;
    cin >> num_vertex >> num_edges;

    // Constucting the conteiner graph
    G.len = num_vertex;
    G.graph.resize(G.len);
    G.part = (bool *)malloc(sizeof(bool) * G.len);
    G.matching = (int *)malloc(sizeof(int) * G.len);
    for (int i = 0; i < G.len; ++i)
    {
        G.matching[i] = -1;
        G.part[i] = false;
    }

    for (int i = 0; i < num_edges; ++i)
    {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        G.graph[vertex1].push_back(vertex2);
        G.graph[vertex2].push_back(vertex1);
    }

    ShowGraph(G, "Initial Graph");

    CalculateBipartite(G);
    KuhnMunkres(G);

    return G;
}

void ShowGraph(GraphContainer &G, string graph_desc)
{
    int count = 0;
    cout << "----- " << graph_desc << " -----" << endl;
    for (vector<vector<int>>::iterator i = G.graph.begin(); i != G.graph.end(); ++i)
    {
        cout << count++ << ": ";
        for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j)
        {
            cout << *j << " ";
        }
        cout << endl;
    }
    cout << "-------- Matching ----------" << endl;
    for (int i = 0; i < G.len ; ++i)
    {
        if (G.matching[i] != -1)
        {
            cout << i << " " << G.matching[i] << endl;
        }
    }
    cout << "----------Parts-------------" << endl;
    for (int i = 0; i < G.len; ++i)
    {
        if (G.part[i] == false)
        {
            cout << i << " black" << endl;
        }
        else
        {
            cout << i << " white" << endl;
        }
    }
    cout << "-----------------------" << endl;
}

void CalculateBipartite(GraphContainer &G)
{
    // setted is a vector thar store information about if the partition of a vertex was setted.
    bool *setted = (bool *)malloc(sizeof(bool) * G.len);
    for (int i = 0; i < G.len; ++i)
    {
        setted[i] = false;
    }
    cout << "sei la pra que serve: " << *setted << endl;

    for (int source = 0; source < G.len; ++source)
    {
        if (setted[source] == false)
        {
            BfsBipartite(G, source, setted);
        }
    }

    free(setted);
}

void BfsBipartite(GraphContainer &G, int source, bool *setted)
{
    queue<int> my_queue;
    // 0 = white, 1 = gray, 2 = black
    int *color = (int *)malloc(sizeof(int) * G.len);
    for (int i = 0; i < G.len; ++i)
    {
        color[i] = 0; // white
    }

    color[source] = 1;
    G.part[source] = true;
    setted[source] = true;

    my_queue.push(source);

    while (!my_queue.empty())
    {
        int vertex = my_queue.front();
        cout << "passando por " << vertex << endl;
        my_queue.pop();
        color[vertex] = 2; // black
        for (vector<int>::iterator it = G.graph[vertex].begin(); it != G.graph[vertex].end(); ++it)
        {
            if (setted[*it] == true && G.part[vertex] == G.part[*it])
            {
                cout << "The graph isn't bipartite pfaffian" << endl;
                exit(0);
            }
            if (color[*it] == 0)
            {
                cout << "Adicionando o vertice " << *it << " na fila" << endl;
                my_queue.push(*it);
                color[*it] = 1; // gray
                G.part[*it] = !G.part[vertex];
                setted[*it] = true;
            }
        }
    }

    free(color);
}

bool KuhnMunkres(GraphContainer &G)
{
    bool modified = true;
    int perfect_matching;
    while (modified)
    {
        for (int i = 0; i < G.len && modified; ++i)
        {
            perfect_matching = true;
            if (G.matching[i] == -1)
            {
                perfect_matching = false;
                modified = BfsAugmentPath(G, i);
            }
        }
        if (perfect_matching)
        {
            modified = false;
        }
    }
    cout << "emparelhamento perfeito? " << perfect_matching << endl;
    return perfect_matching;
}

bool BfsAugmentPath(GraphContainer &G, int source)
{
    cout << "BfsAugmentPath(source=" << source << ")" << endl;
    int target = -1;
    cout << "inicio alvo " << target << endl;
    queue<int> my_queue;

    // 0 = white, 1 = gray, 2 = black
    int *control = (int *)malloc(sizeof(int) * G.len);
    int *color = (int *)malloc(sizeof(int) * G.len);
    int *previous = (int *)malloc(sizeof(int) * G.len);
    for (int i = 0; i < G.len; ++i)
    {
        previous[i] = -1;
        color[i] = 0; // white
        control[i] = 0;
    }

    color[source] = 1;
    control[source] = 0;
    my_queue.push(source);

    while (!my_queue.empty() && target == -1)
    {
        int vertex = my_queue.front();
        cout << "desempilhado: "<< vertex << endl;
        my_queue.pop();
        color[vertex] = 2;

        if (control[vertex] % 2 == 0)
        {
            for (vector<int>::iterator it = G.graph[vertex].begin(); it != G.graph[vertex].end(); ++it)
            {
                if (color[*it] == 0)
                {
                    cout << "Adicionando o vertice " << *it << " na fila" << endl;
                    my_queue.push(*it);
                    previous[*it] = vertex;
                    color[*it] = 1; // gray
                    control[*it] = control[vertex] + 1;
                    if (G.matching[*it] == -1)
                    {
                        target = *it;
                        break;
                    }
                }
            }
        }
        else
        {
            int v = G.matching[vertex];
            my_queue.push(v);
            cout << "Adicionando o vertice " << v << " da arestado emparelhamento na fila" << endl;
            previous[v] = vertex;
            color[v] = 1;
            control[v] = control[vertex] + 1;
        }
    }

    if (target != -1)
    {
        int i = target;

        while (previous[previous[i]] != -1)
        {
            G.matching[i] = previous[i];
            G.matching[previous[i]] = i;
            cout << "novo emparelhamento " << i << " " << previous[i] << endl;
            i = previous[previous[i]];
        }
        G.matching[i] = previous[i];
        G.matching[previous[i]] = i;
        cout << "novo emparelhamento " << i << " " << previous[i] << endl;
    }
    cout << "fim alvo " << target << endl;
    return target != -1;
}