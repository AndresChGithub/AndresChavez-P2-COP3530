#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"
#include "AdjacencyList.h"

using Catch::Approx;

TEST_CASE("Basic two-page link", "[pagerank][basic]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");
    g.computePageRank(1);

    auto result = g.getRanks();

    REQUIRE(result.size() == 2);
    REQUIRE(result["a.com"] == Approx(0.0).margin(0.01));
    REQUIRE(result["b.com"] == Approx(1.0).margin(0.01));
}

TEST_CASE("Page pointing to itself", "[pagerank][loop]") {
    AdjacencyList g;
    g.addEdge("loop.com", "loop.com");
    g.computePageRank(5);

    auto result = g.getRanks();

    REQUIRE(result.size() == 1);
    REQUIRE(result["loop.com"] == Approx(1.0).margin(0.01));
}

TEST_CASE("Page with no incoming links", "[pagerank][dangling]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");
    g.addEdge("a.com", "c.com");

    g.computePageRank(10);
    auto result = g.getRanks();

    REQUIRE(result.size() == 3);
    REQUIRE(result["a.com"] == Approx(0.0).margin(0.01));
    REQUIRE(result["b.com"] + result["c.com"] == Approx(1.0).margin(0.01));
}

TEST_CASE("Disconnected graph components", "[pagerank][components]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");   // Component 1
    g.addEdge("x.com", "y.com");   // Component 2

    g.computePageRank(2);
    auto result = g.getRanks();

    REQUIRE(result.size() == 4);
    REQUIRE(result["b.com"] > result["a.com"]);
    REQUIRE(result["y.com"] > result["x.com"]);
}

TEST_CASE("Stable rank after multiple iterations", "[pagerank][convergence]") {
    AdjacencyList g;
    g.addEdge("a.com", "b.com");
    g.addEdge("b.com", "c.com");
    g.addEdge("c.com", "a.com");

    g.computePageRank(100);  // simulate convergence

    auto result = g.getRanks();
    REQUIRE(result.size() == 3);

    REQUIRE(result["a.com"] == Approx(result["b.com"]).margin(0.01));
    REQUIRE(result["b.com"] == Approx(result["c.com"]).margin(0.01));
}
