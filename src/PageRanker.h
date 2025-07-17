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

    map<string, int> url_to_id;
    vector<string> id_to_url;
    vector<vector<int>> incoming_edges; // the adjacency list
    vector<int> out_degree; // to count the number of outgoing degrees
    vector<double> rank; // store the latest ranks

public:

    void addEdge(const string& from, const string& to) {
        int from_id = get_or_add_url(from);
        int to_id = get_or_add_url(to);

        // this adds an edge: "from" -> "to"
        incoming_edges[to_id].push_back(from_id);
        out_degree[from_id]++;
    }

    void computePageRank(int power_iterations) {

        int n = id_to_url.size();

        rank = vector<double>(n, 1.0 / n);

        for (int iter = 0; iter < power_iterations; ++iter) {
            vector<double> new_rank(n, 0.0);

            // Compute new ranks based on incoming links
            for (int i = 0; i < n; ++i) {

                for (int j : incoming_edges[i]) {

                    if (out_degree[j] > 0) {
                        new_rank[i] += rank[j] / out_degree[j];
                    }

                }

            }

            // Normalize manually (sum all values then divide)
            double sum = 0.0;

            for (int i = 0; i < n; ++i) {
                sum += new_rank[i];
            }

            for (int i = 0; i < n; ++i) {
                new_rank[i] /= sum;
            }

            rank = new_rank;

        }
    }

    map<string, double> getRanks() const {
        
        map<string, double> result;

        for (size_t i = 0; i < id_to_url.size(); ++i) {
            result[id_to_url[i]] = rank[i];
        }

        return result;

    }

private:

    int get_or_add_url(const string& url) {
        // basically, if the URL already exists, return its ID
        // if the function sees that its a new URL, it process it correctly

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
