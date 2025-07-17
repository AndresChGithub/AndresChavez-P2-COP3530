#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "PageRanker.h"

using namespace std;

int main() {
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines >> power_iterations;

    PageRanker graph;

    for (int i = 0; i < no_of_lines; i++) {
        cin >> from >> to;
        graph.addEdge(from, to);
    }

    graph.computePageRank(power_iterations);

    unordered_map<string, double> ranks = graph.getRanks();

    // Convert to vector for sorting
    vector<pair<string, double>> sorted_ranks(ranks.begin(), ranks.end());
    sort(sorted_ranks.begin(), sorted_ranks.end()); // sort alphabetically by URL

    for (const auto& pair : sorted_ranks) {
        cout << pair.first << " " << fixed << setprecision(2) << pair.second << endl;
    }

    return 0;
}
