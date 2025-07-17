#ifndef PAGERANKER_H
#define PAGERANKER_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

class PageRanker {
private:

    map<string,int> url_to_id;
    vector<string> id_to_url;
    vector<vector<int>> incoming_edges; // the adjacency list
    vector<int> out_degree; // to count the number of outgoing degrees
    vector<double> rank; // store the latest ranks

public:

    void addEdge(const string& from, const string& to) {
        int from_id = getOrAddURL(from);
        int to_id = getOrAddURL(to);

        // this adds an edge: "from" -> "to"
        incoming_edges[to_id].push_back(from_id);
        out_degree[from_id]++;
    }

    void computePageRank(int power_iterations) {
        int n = id_to_url.size();
        if (n == 0) return;

        rank = vector<double>(n, 1.0 / n);

        int num_iterations = power_iterations - 1;
        if (num_iterations < 0) {
            num_iterations = 0;
        }

        for (int iter = 0; iter < num_iterations; iter++) {
            // Create a new rank vector filled with 0s
            vector<double> new_rank;
            new_rank.resize(n, 0.0);

            // For each node in the graph
            for (int target = 0; target < n; target++) {
                // Go through each node that links to this target node
                vector<int> sources = incoming_edges[target];
                for (int i = 0; i < sources.size(); i++) {
                    int source = sources[i];

                    // Only count if the source has outgoing links
                    if (out_degree[source] > 0) {
                        new_rank[target] += rank[source] / out_degree[source];
                    }
                }
            }

            // Save the updated ranks
            rank = new_rank;
        }
    }

    // returns map<URL,rank> sorted by URL when iterated
    map<string, double> getRanks() const {
        
        map<string, double> result;

        for (size_t i = 0; i < id_to_url.size(); ++i) {
            result[id_to_url[i]] = rank[i];
        }

        return result;

    }

private:
    int getOrAddURL(const string& url) {

        if (url_to_id.find(url) != url_to_id.end()) {
            return url_to_id[url];
        }

        int id = url_to_id.size();
        url_to_id[url] = id;
        id_to_url.push_back(url);
        incoming_edges.push_back({});
        out_degree.push_back(0);
        return id;
    }
};

#endif
