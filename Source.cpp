#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <math.h>
#include <chrono>
#include <random>
using namespace std;


class Graph
{
private:

    //Using map structure from Aman slides
    map<int, vector<pair<int, int>>> graph;

    // Graph ADJACENCY LIST data structure here 
public:
    map<int, int> m;
    map<int, pair<int, string>> col;
    void insertEdge(int from, int to, int weight);
    vector<int> getAdjacent(int vertex);
    int getIndegree(int vertex);
    int getOutdegree(int vertex);
    int costliestEdge();
    int mostAdjacents();
    void greedyColoring(map<int, string> c, int numbcolors_);
};

void Graph::insertEdge(int from, int to, int weight)
{
    vector<pair<int, int>> s;
    std::pair<int, int> x;
    x.first = to;
    x.second = weight;
    auto it = graph.find(from);
    if (it != graph.end()) {
        graph.at(from).push_back(x);
        //it->second.push(arr[i]);
    }
    else {
        s.push_back(x);
        graph.emplace(from, s);
    }
//graph.at(from) = graph.at(from).push_back(x);
/*
     TODO: insertEdge() adds a new edge between the from and to vertex.
     You will not know how many vertices there may be.
     insertEdge does not output or print anything
*/
}

vector<int> Graph::getAdjacent(int vertex)
{
    vector<int> store;
    /*for (auto it = graph.begin(); it != graph.end(); ++it) {

        for (int i = 0; i < it->second.size(); i++) {
            if (it->second.at(i).first == vertex) {
                store.push_back(it->first);
            }
        }
    }*/
    auto it = graph.find(vertex);
    if (it != graph.end()) {

        //it->second.push(arr[i]);

        for (int i = 0; i < graph.at(vertex).size(); i++) {
            store.push_back(graph.at(vertex).at(i).first);
        }
        std::sort(store.begin(), store.end());
    }
    //TODO: getAdjacent() returns a sorted vector of all vertices that are connected to a vertex
    return store;
}

int Graph::getIndegree(int vertex)
{
    /*
        TODO: getIndegree() returns the indegree of vertex
    */
    int count = 0;
    for (auto it = graph.begin(); it != graph.end(); ++it) {

        for (int i = 0; i < it->second.size(); i++) {
            if (it->second.at(i).first == vertex) {
                count++;
            }
        }
    }
    return count;
}

int Graph::getOutdegree(int vertex)
{
    auto it = graph.find(vertex);
    if (it == graph.end()) {

        //it->second.push(arr[i]);

        return 0;
    }
    /*
        TODO: getOutdegree() returns the outdegree of vertex
    */
    return graph.at(vertex).size();
}

int Graph::costliestEdge()
{
    auto its = graph.begin();
    int max = its->second.at(0).second;
    for (auto it = graph.begin(); it != graph.end(); ++it) {

        for (int i = 0; i < it->second.size(); i++) {
            if (it->second.at(i).second > max) {
                max = it->second.at(i).second;
            }
        }
    }
    return max;
    //TODO: costliestEdge() returns the edge weight of the costliest edge
}
void Graph::greedyColoring(map<int, string> c, int numbcolors_) {
    auto its = graph.begin();
    int max = its->second.at(0).second;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        int ccount = 0;
        map<int, int> holder;
        for (int i = 0; i < it->second.size(); i++) {

            holder.emplace(col.at(it->second.at(i).first).first, 0);

        }
        for (int j = 1; j <= numbcolors_; j++) {
            if (holder.find(j) == holder.end()) {
                pair<int, string> p;
                p.first = j;
                p.second = c.at(j);
                col.at(it->first) = p;
                break;
            }
        }
        if (col.at(it->first).first == 0) {
            pair<int, string> p;
            p.first = 1;
            p.second = c.at(1);
            col.at(it->first) = p;
        }
            
        
        
    }
}

int Graph::mostAdjacents()
{
    return 0;
    //TODO: costliestEdge() returns the edge weight of the costliest edge
}

int main()
{
    //DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK
    Graph g;
    map<int, string> color;
    color.emplace(0, "");
    color.emplace(1, "Red");
    color.emplace(2, "Blue");
    color.emplace(3, "Green");
    color.emplace(4, "Yellow");
    color.emplace(5, "Orange");
    color.emplace(6, "Purple");
    //color.emplace(7, "Pink");
    int numbcolors = 6;

    for (int i = 1; i <= 100000; i++) {

        g.m.emplace(i, 0);
    }
    for (int i = 1; i <= 100000; i++) {
        pair<int, string> x;
        x.first = 0;
        x.second = "";
        g.col.emplace(i, x);
    }

    for (int i = 1; i <= 100000; i++) {
        std::random_device random;
        std::mt19937 rng(random());
        std::uniform_int_distribution<int> range(0, 5);
        int adjacencies = range(random);
        for (int j = 0; j < adjacencies; j++) {
            std::random_device rando;
            std::mt19937 rng(rando());
            std::uniform_int_distribution<int> ranges(1, 100000);
            int adjacentVertex = ranges(rando);
            int check = g.m.at(adjacentVertex) + 1;
            int checki = g.m.at(i) + 1;
            if (check <= 5 && checki <= 5) {
                g.insertEdge(i, adjacentVertex, 0);
                g.insertEdge(adjacentVertex, i, 0);
                g.m.at(adjacentVertex) = check;
                g.m.at(i) = checki;
            }

        }

    }
    int max = 0;
    for (int i = 1; i <= 100000; i++) {
        if (g.m.at(i) > max) {
            max = g.m.at(i);
        }
    }
    cout << max;
    //vector<int> v = g.getAdjacent(1); 
    //cout << 
    g.greedyColoring(color, numbcolors);
    for (int i = 99990; i <= 100000; i++) {
        cout << g.col.at(i).second << endl << i << endl;
        vector<int> v = g.getAdjacent(i);
        for (int j = 0; j < v.size(); j++) {
            cout << v.at(j) << " " << g.col.at(v.at(j)).second << " ";
            //cout << v.at(j) << " ";
            //cout << g.col.at(v.at(j)).first << endl;   
            vector<int> k = g.getAdjacent(v.at(j));
            for (int z = 0; z < k.size(); z++) {
               // cout << k.at(z) << " ";
            }
            cout << endl;
        }

    }
    /*int noOfLines, operation, vertex, to, fro, weight, source, j;
    vector<int> arr;
    int arrSize;
    Graph g;
    cin >> noOfLines;
    for (int i = 0; i < noOfLines; i++)
    {
        cin >> operation;
        switch (operation)
        {
        case 1:
            cin >> fro;
            cin >> to;
            cin >> weight;
            g.insertEdge(fro, to, weight);
            break;
        case 2:
            cin >> fro;
            cin >> to;
            cout << g.isEdge(fro, to) << "\n";
            break;
        case 3:
            cin >> fro;
            cin >> to;
            cout << g.getWeight(fro, to) << "\n";
            break;
        case 4:
            cin >> vertex;
            arr = g.getAdjacent(vertex);
            arrSize = arr.size();
            j = 0;
            while (j < arrSize)
            {
                cout << arr[j] << " ";
                j++;
            }
            cout << "\n";
            break;
        case 5:
            g.printGraph();
            cout << "\n";
            break;
        }
    }*/
}