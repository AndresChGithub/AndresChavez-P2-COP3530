#include <iostream>
#include "AdjacencyList.h"

using namespace std;

// prints the PageRank of all pages after p powerIterations in ascending
// alphabetical order of webpages and rounding rank to two decimal places
// string AdjacencyList::PageRank(int n){
//     // optionally, store your output in a string/stringstream and then return it from this function after printing so that it is easier to test with Catch
//     string result;

//     // do your page rank

//     cout << result;
//     return result;
// }

// ^^^ all this came here with the template of the project, not deleting for now.

void AdjacencyList::computePageRank(int powerIterations) {
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