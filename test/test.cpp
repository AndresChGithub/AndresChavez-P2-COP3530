#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "AdjacencyList.h"

// Andres Chavez , 26934004

TEST_CASE("Basic two-page link", "[pagerank][basic]") {
    AdjacencyList g;
    g.addEdge("miko.com", "suisei.com");
    g.computePageRank(1);

    auto result = g.getRanks();

    REQUIRE(result.size() == 2);
    REQUIRE(result["miko.com"] == 0.0);
    REQUIRE(result["suisei.com"] == 1.0);
}

TEST_CASE("Page pointing to itself", "[pagerank][loop]") {
    AdjacencyList g;
    g.addEdge("loop.com", "loop.com");
    g.computePageRank(5);

    auto result = g.getRanks();

    REQUIRE(result.size() == 1);
    REQUIRE(result["loop.com"] == 1.0);
}

TEST_CASE("Page with no incoming links", "[pagerank][dangling]") {
    AdjacencyList g;
    g.addEdge("Botan.com", "Lamy.com");
    g.addEdge("Botan.com", "Nene.com");

    g.computePageRank(10);
    auto result = g.getRanks();

    REQUIRE(result.size() == 3);
    REQUIRE(result["Botan.com"] == 0.0);
    REQUIRE(result["Lamy.com"] + result["Nene.com"] == 1.0);
}

TEST_CASE("Disconnected graph components", "[pagerank][components]") {
    AdjacencyList g;
    g.addEdge("Subaru.com", "Okayu.com");     // Component 1
    g.addEdge("Fuwawa.com", "Mococo.com");    // Component 2

    g.computePageRank(2);
    auto result = g.getRanks();

    REQUIRE(result.size() == 4);
    REQUIRE(result["Okayu.com"] > result["Subaru.com"]);
    REQUIRE(result["Mococo.com"] > result["Fuwawa.com"]);
}

TEST_CASE("Stable rank after multiple iterations", "[pagerank][convergence]") {
    AdjacencyList g;
    g.addEdge("Pekora.com", "Korone.com");
    g.addEdge("Korone.com", "Marine.com");
    g.addEdge("Marine.com", "Pekora.com");

    g.computePageRank(100);  // simulate convergence

    auto result = g.getRanks();
    REQUIRE(result.size() == 3);

    REQUIRE(result["Pekora.com"] == result["Korone.com"]);
    REQUIRE(result["Korone.com"] == result["Marine.com"]);
}