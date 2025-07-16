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
    vector<vector<int>> incoming_edges; // index i holds list of nodes that link to i
    vector<int> out_degree;
    vector<double> rank; // store the latest ranks

public:
    void addEdge(const string& from, const string& to) {
        int from_id = get_or_add_url(from);
        int to_id = get_or_add_url(to);

        incoming_edges[to_id].push_back(from_id);
        out_degree[from_id]++;
    }

    void computePageRank(int power_iterations) {
        int n = id_to_url.size();
        rank.assign(n, 1.0 / n); // initialize ranks
        double d = 0.85;

        for (int iter = 0; iter < power_iterations; ++iter) {
            vector<double> new_rank(n, (1.0 - d) / n);

            double dangling_sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (out_degree[j] == 0) {
                    dangling_sum += rank[j];
                }
            }

            for (int i = 0; i < n; ++i) {
                for (int j : incoming_edges[i]) {
                    if (out_degree[j] > 0) {
                        new_rank[i] += d * rank[j] / out_degree[j];
                    }
                }
                // Distribute dangling rank
                new_rank[i] += d * dangling_sum / n;
            }

            rank = new_rank;
        }
    }


    unordered_map<string, double> getRanks() const {
        unordered_map<string, double> result;
        for (size_t i = 0; i < id_to_url.size(); ++i) {
            result[id_to_url[i]] = rank[i];
        }
        return result;
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
