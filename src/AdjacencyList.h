#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

class AdjacencyList {
private:
    unordered_map<string, int> url_to_id;
    vector<string> id_to_url;
    vector<vector<int>> incoming_edges; // index i holds a list of nodes that link to i
    vector<int> out_degree;

public:
    void addEdge(const string& from, const string& to) {
        int from_id = get_or_add_url(from);
        int to_id = get_or_add_url(to);

        incoming_edges[to_id].push_back(from_id);
        out_degree[from_id]++;
    }

    void computePageRank(int power_iterations) {
        int n = id_to_url.size();
        vector<double> rank(n, 1.0 / n);

        for (int iter = 0; iter < power_iterations; ++iter) {
            vector<double> new_rank(n, 0.0);

            for (int i = 0; i < n; ++i) {
                for (int j : incoming_edges[i]) {
                    new_rank[i] += rank[j] / out_degree[j];
                }
            }
            rank = new_rank;
        }

        // Prepare for output
        vector<pair<string, double>> results;
        for (int i = 0; i < n; ++i)
            results.push_back({id_to_url[i], rank[i]});

        sort(results.begin(), results.end()); // Alphabetical order

        for (auto& pair : results) {
            cout << pair.first << " " << fixed << setprecision(2) << pair.second << endl;
        }
    }

private:
    int get_or_add_url(const string& url) {
        if (url_to_id.count(url)) return url_to_id[url];
        int id = url_to_id.size();
        url_to_id[url] = id;
        id_to_url.push_back(url);
        incoming_edges.push_back({});
        out_degree.push_back(0);
        return id;
    }
};

#endif
