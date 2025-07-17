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
    vector<double> rank;    // store the latest ranks

public:

    void addEdge(const string& from, const string& to) {
        int u = get_or_add_url(from);
        int v = get_or_add_url(to);

        // this adds an edge: "from" -> "to"
        incoming_edges[v].push_back(u);
        out_degree[u]++;
    }

    void computePageRank(int power_iterations) {
        int n = id_to_url.size();
        if (n == 0) return;

        rank = vector<double>(n, 1.0 / n);

        // we need (p − 1) matrix multiplies to get r(p−1)
        int iters = max(0, power_iterations - 1);
        for (int iter = 0; iter < iters; ++iter) {
            vector<double> new_rank(n, 0.0);

            // simple M · r: each v sums over its in-neighbors u
            for (int v = 0; v < n; ++v) {
                for (int u : incoming_edges[v]) {
                    if (out_degree[u] > 0) {
                        new_rank[v] += rank[u] / out_degree[u];
                    }
                }
            }
            // using the normalization described in the project
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

    // returns map<URL,rank> sorted by URL when iterated
    map<string, double> getRanks() const {
        
        map<string, double> result;

        for (size_t i = 0; i < id_to_url.size(); ++i) {
            result[id_to_url[i]] = rank[i];
        }

        return result;

    }

private:
    int get_or_add_url(const string& url) {

        if (url_to_id.find(url) != url_to_id.end()) {
            return url_to_id[url];
        }

        int id = url_to_id.size();
        url_to_id[url] = id;
        id_to_url.push_back(url);
        incoming_edges.emplace_back();
        out_degree.push_back(0);
        return id;
    }
};

#endif
