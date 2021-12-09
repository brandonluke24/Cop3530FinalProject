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

// Graph class mainly taken from Brandon's Graph Implentation in Stepik 7.1
class Graph
{
private:

    //Using map structure from Aman slides
    map<int, vector<pair<int, int>>> graph;

    // Graph ADJACENCY LIST data structure here 
public:
    // Map M stores the number of adjacencies
    map<int, int> m;
    // Map Col stores a Color pair
    map<int, pair<int, string>> col; 
    void insertEdge(int from, int to, int weight);
    vector<int> getAdjacent(int vertex);
    int getIndegree(int vertex);
    int getOutdegree(int vertex);
    int costliestEdge();
    int mostAdjacents();
    void greedyColoring(map<int, string> c, int numbcolors_);
    void WelshPowellColoring(map<int, string> c, int numbcolors_);
};
// Inserts edge between two vertices into graph
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

// Returns vector of the neighboring adjacencies of a vertex
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

// Function returns the in degree of a given vertex
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

// Function returns the out degree of a given vertex
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

// For a weighted graph, this function returns the maximum weight of an edge
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

// Basic Greedy coloring algorithm that colors each vertex the first color available
void Graph::greedyColoring(map<int, string> c, int numbcolors_) {
    //auto its = graph.begin();
    //int max = its->second.at(0).second;
    // Iterate through Graph
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        int ccount = 0;
        map<int, int> holder;
        // Store colors of neighbors
        for (int i = 0; i < it->second.size(); i++) {

            holder.emplace(col.at(it->second.at(i).first).first, 0);

        }
        // Finds the first color available that's not already coloring a neighbor
        for (int j = 1; j <= numbcolors_; j++) {
            if (holder.find(j) == holder.end()) {
                pair<int, string> p;
                p.first = j;
                p.second = c.at(j);
                col.at(it->first) = p;
                break;
            }
        } 
        // Inserts that color into color map
        if (col.at(it->first).first == 0) {
            pair<int, string> p;
            p.first = 1;
            p.second = c.at(1);
            col.at(it->first) = p;
        }
            
        
        
    }
}

// Modified Welsh Powell Greedy Algorithm, sorts by descending adjacencies and then iterates in that order finding the first available color
void Graph::WelshPowellColoring(map<int, string> c, int numbcolors_) {
    multimap<int, int> reverse;
    //Creates a multimap that stores the number of adjacencies as key and vertices as values
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (graph.find(it->first) != graph.end()) {
            reverse.emplace(it->second, it->first);
        }
    }
    // Iterate through multimap in descending order using (r) reverse functions
    for (auto it = reverse.rbegin(); it != reverse.rend(); ++it) {
        int ccount = 0;
        map<int, int> holder;
        // Checks color of neighbors
        for (int i = 0; i < graph.at(it->second).size(); i++) {

            holder.emplace(col.at(graph.at(it->second).at(i).first).first, 0);

        }
        // Colors Vertex the first available color
        for (int j = 1; j <= numbcolors_; j++) {
            if (holder.find(j) == holder.end()) {
                pair<int, string> p;
                p.first = j;
                p.second = c.at(j);
                col.at(it->second) = p;
                break;
            }
        }
    }
    // Attempted full Welsh Powell
    /*int i = 1;
    
    for (auto it = reverse.rbegin(); it != reverse.rend(); ++it) {
        map<int, int> neighbor;
        pair<int, string> p;
        if (i = 7) {
            i = 1;
        }
        p.first = i;
        p.second = c.at(i);
        col.emplace(it->second, p);
        neighbor.emplace(it->second,0);
        auto itx = graph.find(it->second);
        if (itx != graph.end()) {

            //it->second.push(arr[i]);

            for (int i = 0; i < graph.at(it->second).size(); i++) {
                neighbor.emplace(graph.at(it->second).at(i).first,0);
            }
            //std::sort(store.begin(), store.end());
        }
        reverse.erase(it->second);
        for (auto its = reverse.rbegin(); its != reverse.rend(); its++) {
            if (neighbor.find(its->second) == neighbor.end()) {
                col.emplace(its->second, p);
                neighbor.emplace(its->second, 0);
                auto itx = graph.find(its->second);
                if (itx != graph.end()) {

                    //it->second.push(arr[i]);

                    for (int i = 0; i < graph.at(its->second).size(); i++) {
                        neighbor.emplace(graph.at(its->second).at(i).first, 0);
                    }
                    //std::sort(store.begin(), store.end());
                }
                reverse.erase(its->second);
}
            /*if (visited.find(its->second) == visited.end()) {
               // visited.emplace(its->second);
               // reverse.erase(its->second);
            //}
        }
        
        i++;
    }*/
}

// Function does nothing
int Graph::mostAdjacents()
{
    return 0;
    
}

int main()
{
    
    // Welcome Menu
    cout << "Welcome to our Final Project for Cop 3530!" << endl;
    cout << "We will compare two different graph coloring algorithms. One is a basic greedy algorithm and the other is a modified Welsh Powell Algorithm" << endl;
    cout << "We will insert 100,000 Vertexes into an undirected graph and give each a maximum of five adjacencies." << endl;
    cout << "Our color wheel will have six colors: red, blue, green, yellow, orange, and purple " << endl << endl;
    
    // Initialize Graph
    Graph g;

    // Create Map to hold our color wheel
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

    // Seed Map m with 0 neighbors
    for (int i = 1; i <= 100000; i++) {

        g.m.emplace(i, 0);
    }
    // Seed color map with null color
    for (int i = 1; i <= 100000; i++) {
        pair<int, string> x;
        x.first = 0;
        x.second = "";
        g.col.emplace(i, x);
    }

    // For 100,000 vertices, insert between 1 and 5 randomized edges
    for (int i = 1; i <= 100000; i++) {
        std::random_device random;
        std::mt19937 rng(random());
        std::uniform_int_distribution<int> range(1, 5);
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

    // Check to ensure a maximum of 5 Adjacencies
    /*int max = 0;
    for (int i = 1; i <= 100000; i++) {
        if (g.m.at(i) > max) {
            max = g.m.at(i);
        }
    }*/
    //cout << max; Checking max neighbors from random assignment
    //vector<int> v = g.getAdjacent(1); 
    //cout << 
    // Copy Graph over to another for separate Welsh Powell Comparison
    Graph gW = g;

    // Conduct Timing Comparison
    cout << "Timing comparison between Basic Greedy Algorithm and modified Welsh Powell Algorithm " << endl;

    auto start = std::chrono::high_resolution_clock::now();
    
    g.greedyColoring(color, numbcolors);
    auto stop = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Basic Greedy Algorithm Time: " << time.count() << " milliseconds" << endl;

    start = std::chrono::high_resolution_clock::now();

    gW.WelshPowellColoring(color, numbcolors);
    stop = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Modified Welsh Powell Greedy Algorithm Time: " << time.count() << " milliseconds" << endl << endl;

    // Displays sample of first 10 vertices & neighbors and their coloring for Basic Greedy colored graph
    cout << "Basic Greedy Algorithm Color Display: First 10 Vertices and Neighbors" << endl;
   
    for (int i = 1; i <= 10; i++) {
        cout << "Vertex: " << i << " - Color: " <<  g.col.at(i).second << endl;
        vector<int> v = g.getAdjacent(i);
        cout << "Neighbors: ";
        for (int j = 0; j < v.size(); j++) {
            cout <<  v.at(j) << " - Color: " << g.col.at(v.at(j)).second;
            if (j != v.size() - 1) {
                cout << ", ";
            }
            //cout << v.at(j) << " ";
            //cout << g.col.at(v.at(j)).first << endl;   
           // vector<int> k = g.getAdjacent(v.at(j));
            //for (int z = 0; z < k.size(); z++) {
               // cout << k.at(z) << " ";
            //}
            //cout << endl;
        }
        cout << endl;
    }
    cout << endl;

    // Test seeding
    /*for (int i = 1; i <= 100000; i++) {

        gW.m.emplace(i, 0);
    }
    for (int i = 1; i <= 100000; i++) {
        pair<int, string> x;
        x.first = 0;
        x.second = "";
        gW.col.emplace(i, x);
    }
    for (int i = 1; i <= 100000; i++) {
        std::random_device random;
        std::mt19937 rng(random());
        std::uniform_int_distribution<int> range(1, 5);
        int adjacencies = range(random);
        for (int j = 0; j < adjacencies; j++) {
            std::random_device rando;
            std::mt19937 rng(rando());
            std::uniform_int_distribution<int> ranges(1, 100000);
            int adjacentVertex = ranges(rando);
            int check = gW.m.at(adjacentVertex) + 1;
            int checki = gW.m.at(i) + 1;
            if (check <= 5 && checki <= 5) {
                gW.insertEdge(i, adjacentVertex, 0);
                gW.insertEdge(adjacentVertex, i, 0);
                gW.m.at(adjacentVertex) = check;
                gW.m.at(i) = checki;
            }

        }

    }*/
    
    // Displays sample of first 10 vertices & neighbors and their coloring for Modified Welsh Powell Greedy colored graph
    cout << "Modified Welsh Powell Greedy Algorithm Color Display: First 10 Vertices and Neighbors" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << "Vertex: " << i << " - Color: " << gW.col.at(i).second << endl;
        vector<int> v = gW.getAdjacent(i);
        cout << "Neighbors: ";
        for (int j = 0; j < v.size(); j++) {
            cout << v.at(j) << " - Color: " << gW.col.at(v.at(j)).second;
            if (j != v.size() - 1) {
                cout << ", ";
            }
            //cout << v.at(j) << " ";
            //cout << g.col.at(v.at(j)).first << endl;   
           // vector<int> k = g.getAdjacent(v.at(j));
            //for (int z = 0; z < k.size(); z++) {
               // cout << k.at(z) << " ";
            //}
            //cout << endl;
        }
        cout << endl;

    }
    cout << endl;

    // Create counts and record the number of each color used for both algorithms  and print out their respective values
    cout << "Color breakdown for both algorithms" << endl;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int count5 = 0;
    int count6 = 0;
    for (auto i = g.col.begin(); i != g.col.end(); ++i) {
        if (i->second.first == 1) {
            count1++;
        }
        if (i->second.first == 2) {
            count2++;
        }
        if (i->second.first == 3) {
            count3++;
        }
        if (i->second.first == 4) {
            count4++;
        }
        if (i->second.first == 5) {
            count5++;
        }
        if (i->second.first == 6) {
            count6++;
        }
    }
    cout << "Basic Greedy Algorithm Color Count:" << endl;
    cout << "Red: " << count1 << ", Blue: " << count2 << ", Green: " << count3 << ", Yellow: " << count4 << ", Orange: " << count5 << ", Purple: " << count6 << endl;

    count1 = 0;
    count2 = 0;
    count3 = 0;
    count4 = 0;
    count5 = 0;
    count6 = 0;
    for (auto i = gW.col.begin(); i != gW.col.end(); ++i) {
        if (i->second.first == 1) {
            count1++;
        }
        if (i->second.first == 2) {
            count2++;
        }
        if (i->second.first == 3) {
            count3++;
        }
        if (i->second.first == 4) {
            count4++;
        }
        if (i->second.first == 5) {
            count5++;
        }
        if (i->second.first == 6) {
            count6++;
        }
    }
    cout << "Modified Welsh Powell Greedy Algorithm Color Count:" << endl;
    cout << "Red: " << count1 << ", Blue: " << count2 << ", Green: " << count3 << ", Yellow: " << count4 << ", Orange: " << count5 << ", Purple: " << count6 << endl;

   
}