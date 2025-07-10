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
    void computePageRank(int powerIterations) {
        int N = adjList.size();
        if (N == 0) return;

        // Initialize all ranks to 1/N
        for (const auto& pair : adjList) {
            ranks[pair.first] = 1.0 / N;
        }

        // Dummy page rank computation: does nothing for now
        for (int i = 0; i < powerIterations; ++i) {
            unordered_map<string, double> newRanks = ranks;

            // STUB: this is where you'd implement rank propagation
            // For now, copy same values
            ranks = newRanks;
        }
    }

    // Returns a map of URL to its final rank
    map<string, double> getRanks() const {
        // Convert unordered_map to ordered map for deterministic test output
        return map<string, double>(ranks.begin(), ranks.end());
    }
};

#endif // ADJACENCYLIST_H
