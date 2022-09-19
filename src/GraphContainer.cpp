#include "GraphContainer.hpp"

/* Generate an empty GraphConteiner with no vertex, no matching
 * with the n_vert and matc_size iquals to zero.
 */
GraphContainer::GraphContainer() {
    n_vert = 0;
    matc_size = 0;
    isBipartite = false;
    bipartitionComputed = false;
}


/* Initialize a graph with "size" vertices, a partition with all vertices in the
 * same part, an empty matching. When matching[v] = -1 means the vertex v is not matched.
 */
GraphContainer::GraphContainer(int size) {
    graph.resize(size);
    part.resize(size, false);
    matching.resize(size, -1);
    n_vert = size;
    matc_size = 0;
    
}

void GraphContainer::GraphInitFromStdin()
{
    int num_vertices, num_edges;
    cin >> num_vertices >> num_edges;

    if (num_vertices % 2 != 0)
    {
        cout << "The graph G is pfaffian by emptiness" << endl;
        exit(0);
    }

    graph.resize(num_vertices);
    part.resize(num_vertices, false);
    matching.resize(num_vertices, -1);
    n_vert = num_vertices;
    matc_size = 0;

    for (int i = 0; i < num_edges; ++i)
    {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        AddEdge(vertex1, vertex2);
    }
}

void GraphContainer::AddEdge(int vertex1, int vertex2)
{
    graph[vertex1].push_back(vertex2);
    graph[vertex2].push_back(vertex1);
}

bool GraphContainer::ComputeBipartite()
{
    // setted is a vector that store information about if the partition of a vertex was setted.
    vector<bool> setted(n_vert, false);

    for (int source = 0; source < n_vert; ++source)
    {
        if (setted[source] == false)
        {
            if (!BfsBipartite(source, setted)) {
                return false;
            }
        }
    }
    return true;
    // delete setted
}

bool GraphContainer::BfsBipartite(int source, vector<bool> &setted)
{
    queue<int> my_queue;
    // 0 = white, 1 = gray, 2 = black
    vector<int> color(n_vert, 0); // white

    color[source] = 1;
    part[source] = true;
    setted[source] = true;

    my_queue.push(source);

    while (!my_queue.empty())
    {
        int vertex = my_queue.front();
        my_queue.pop();
        color[vertex] = 2; // black
        for (vector<int>::iterator it = graph[vertex].begin(); it != graph[vertex].end(); ++it)
        {
            if (setted[*it] == true && part[vertex] == part[*it]) // Use this information as 
            // return.
            {
                return false;
            }
            if (color[*it] == 0)
            {
                my_queue.push(*it);
                color[*it] = 1; // gray
                part[*it] = !part[vertex];
                setted[*it] = true;
            }
        }
    }

    // delelte color
    return true;
    
}

bool GraphContainer::KuhnMunkres()
{
    bool modified = true;
    while (modified)
    {
        modified = false;
        for (int i = 0; i < n_vert; ++i)
        {
            if (matching[i] == -1)
            {
                if (BfsAugmentPath(i))
                {
                    modified = true;
                }
            }
        }
    }

    int count = 0;
    for (vector<int>::iterator i = matching.begin(); i != matching.end(); ++i) {
        if (*i != -1) {
            count++;
        }
    }
    matc_size = count/2;
    return matc_size == n_vert/2;
}

bool GraphContainer::PerfectMatching() {
    return matc_size == n_vert/2;
}

bool GraphContainer::BfsAugmentPath(int source)
{
    int target = -1;
    queue<int> my_queue;

    // 0 = white, 1 = gray, 2 = black
    vector<int> distance(n_vert, 0);
    vector<int> color(n_vert, 0);
    vector<int> previous(n_vert, -1);

    color[source] = 1;
    distance[source] = 0;
    my_queue.push(source);

    while (!my_queue.empty() && target == -1)
    {
        int vertex = my_queue.front();
        my_queue.pop();
        color[vertex] = 2;

        if (distance[vertex] % 2 == 0)
        {
            for (vector<int>::iterator it = graph[vertex].begin(); it != graph[vertex].end(); ++it)
            {
                if (color[*it] == 0)
                {
                    my_queue.push(*it);
                    previous[*it] = vertex;
                    color[*it] = 1; // gray
                    distance[*it] = distance[vertex] + 1;
                    if (matching[*it] == -1)
                    {
                        target = *it;
                        break;
                    }
                }
            }
        }
        else
        {
            int v = matching[vertex];
            my_queue.push(v);
            previous[v] = vertex;
            color[v] = 1;
            distance[v] = distance[vertex] + 1;
        }
    }

    if (target != -1)
    {
        int i = target;

        while (previous[previous[i]] != -1)
        {
            matching[i] = previous[i];
            matching[previous[i]] = i;
            i = previous[previous[i]];
        }
        matching[i] = previous[i];
        matching[previous[i]] = i;
    }

    // free color, parent, distance

    return target != -1;
}

void GraphContainer::ShowGraph(string graph_desc)
{
    int count = 0;
    cout << "----- " << graph_desc << " -----" << endl;
    for (vector<vector<int>>::iterator i = graph.begin(); i != graph.end(); ++i)
    {
        cout << count++ << ": ";
        for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j)
        {
            cout << *j << " ";
        }
        cout << endl;
    }
    cout << "Matching: ";
    ;
    for (int i = 0; i < n_vert; ++i)
    {
        if (matching[i] != -1 && i < matching[i])
        {
            cout << "{" << i << ", " << matching[i] << "}, ";
        }
    }
    cout << endl;
    cout << "Parts: ";
    for (int i = 0; i < n_vert; ++i)
    {
        part[i] ? cout << i << " white, " : cout << i << " black, ";
    }
    cout << endl;
    cout << "-----------------------" << endl;
}

void GraphContainer::RemoveEdge(int v1, int v2)
{
    for (vector<int>::iterator i = graph[v1].begin(); i != graph[v1].end(); ++i)
    {
        if ((*i) == v2)
        {
            graph[v1].erase(i);
            break;
        }
    }

    for (vector<int>::iterator i = graph[v2].begin(); i != graph[v2].end(); ++i)
    {
        if ((*i) == v1)
        {
            graph[v2].erase(i);
            break;
        }
    }

    if (matching[v1] == v2)
    {
        matching[v1] = -1;
        matching[v2] = -1;
        matc_size--;
    }
}

void GraphContainer::IsolateVerteces(vector<int> verticesToIsolate) {
    vector<pair<int, int> > edge_list;
    for (vector<int>::iterator i = verticesToIsolate.begin(); i != verticesToIsolate.end(); ++i) {
        for (vector<int>::iterator j = graph[*i].begin(); j != graph[*i].end(); ++j) {
             if (find(verticesToIsolate.begin(), verticesToIsolate.end(), (*j)) == verticesToIsolate.end()) { // use verticesToIsolate.find(*j) != verticesToIsolate.end(), remove 269--273
                pair<int, int> edge(*i, *j);
                edge_list.push_back(edge);
            }

        }
    }

    for (vector<pair<int, int> >::iterator i = edge_list.begin(); i != edge_list.end(); ++i) {
        RemoveEdge((*i).first, (*i).second);
    }       
}

vector<pair<int,int>> GraphContainer::ListAllEdges() {
    vector<pair<int,int>> list;
    for (int i = 0; i < n_vert; ++i) {
        for (vector<int>::iterator j = graph[i].begin(); j != graph[i].end(); ++j) {
            if (i < (*j)) {
                //cout << i << " - " << (*j) << endl;
                pair<int, int> edge;
                edge.first = i;
                edge.second = (*j);
                list.push_back(edge);
            }
        }
    }

    return list;
}