#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct GraphContainer
{
    vector<vector<int>> graph;
    int *matching; // if mathing[5]=6, the edge {5,6} is in the matching, if matching[5]=-1 otherwise.
    int len;
    bool *part;

    void remove_vertex(int v)
    {
        // deleting vertex v
        // remove v from neighbohood of others verteces
        for (vector<vector<int>>::iterator i = graph.begin(); i != graph.end(); ++i)
        {
            for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j)
            {
                if (*j == v){
                    (*i).erase(j);
                    break;
                }
            }
        }
        // erase v from graph (hence the verteces will be shifted)
        graph.erase(std::next(graph.begin(),v));

        // subtract 1 from adjacent verteces who is greater than v
        for (vector<vector<int>>::iterator i = graph.begin(); i != graph.end(); ++i)
        {
            for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); ++j)
            {
                if (*j > v){
                    *j-=1;
                }
            }
        }

        // shifting the color array
        for (int i = v; i < len-1; ++i) {
            part[i] = part[i+1];
        }

        // fixing the matching
        if (matching[v] != -1) {

            for (int i = 0; i < len; ++i) {
                if (matching[i] == v){
                    matching[i] = -1;
                }
                if (matching[i] > v){
                    matching[i] -= 1;
                }
            }
            matching[v] = -1;
        }

        // shifting the matching
        for (int i = v; i < len-1; ++i) {
            matching[i] = matching[i+1];
        }

        // resizing the lenght
        len -= 1;
    }
};

#endif