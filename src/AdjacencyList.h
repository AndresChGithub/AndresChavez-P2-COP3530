#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include <unordered_map>

using namespace std;

class AdjacencyList {
private:
    unordered_map<string, set<string>> adjList;
    unordered_map<string, double> ranks;

public:
    // Add a directed edge from 'from' to 'to'
    void addEdge(const string& from, const string& to) {
        adjList[from].insert(to);
        // Ensure both nodes exist in the map
        if (adjList.find(to) == adjList.end()) {
            adjList[to] = {};
        }
    }

    // Compute the PageRank using 'powerIterations' steps

    void computePageRank(int powerIterations);

    // string PageRank(int n); <--- this is the one they (the project template) want me to add for my tests I think
    // computePageRank is meant to replace PageRank, its already sorta implemented so I dont want to delete it....
    //

    // Returns a map of URL to its final rank
    map<string, double> getRanks() const {
        // Convert unordered_map to ordered map for deterministic test output
        return map<string, double>(ranks.begin(), ranks.end());
    }
};

#endif // ADJACENCYLIST_H
