#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "AdjacencyList.h"

// Name: Andres Chavez
// UFID: 26934004

TEST_CASE("Basic two-page link", "[pagerank][basic]") {
    // Testing basic one-way link from miko.com to suisei.com
    // All rank should end up in suisei.com since she's the only one being pointed to
    AdjacencyList g;
    g.addEdge("miko.com", "suisei.com");
    g.computePageRank(1);

    auto result = g.getRanks();

    REQUIRE(result.size() == 2);
    REQUIRE(result["miko.com"] == 0.0);
    REQUIRE(result["suisei.com"] == 0.5);
}

TEST_CASE("Page pointing to itself", "[pagerank][loop]") {
    // Checking behavior of a self-loop — polka.com links to herself only
    // She should retain all the rank through every iteration
    AdjacencyList g;
    g.addEdge("polka.com", "polka.com");
    g.computePageRank(5);

    auto result = g.getRanks();

    REQUIRE(result.size() == 1);
    REQUIRE(result["polka.com"] == 1.0);
}

TEST_CASE("Page with no incoming links", "[pagerank][dangling]") {
    // botan.com links to lamy.com and nene.com, but no one links to her
    // She should have a rank of 0, and lamy/nene split her rank
    AdjacencyList g;
    g.addEdge("botan.com", "lamy.com");
    g.addEdge("botan.com", "nene.com");

    g.computePageRank(10);
    auto result = g.getRanks();

    REQUIRE(result.size() == 3);
    REQUIRE(result["botan.com"] == 0.0);
    REQUIRE(result["lamy.com"] + result["nene.com"] == 0.0);
}

TEST_CASE("Disconnected graph components", "[pagerank][components]") {
    // Two separate link pairs: subaru.com → okayu.com and fuwawa.com → mococo.com
    // The pages being linked to should get higher ranks than the ones linking
    AdjacencyList g;
    g.addEdge("subaru.com", "okayu.com");
    g.addEdge("fuwawa.com", "mococo.com");

    g.computePageRank(2);
    auto result = g.getRanks();

    REQUIRE(result.size() == 4);
    REQUIRE(result["okayu.com"] == result["subaru.com"]);
    REQUIRE(result["mococo.com"] == result["fuwawa.com"]);
}

TEST_CASE("Stable rank after multiple iterations", "[pagerank][convergence]") {
    // Circular loop: pekora.com → korone.com → marine.com → pekora.com
    // After enough iterations, all pages should have equal rank
    AdjacencyList g;
    g.addEdge("pekora.com", "korone.com");
    g.addEdge("korone.com", "marine.com");
    g.addEdge("marine.com", "pekora.com");

    g.computePageRank(100);

    auto result = g.getRanks();
    REQUIRE(result.size() == 3);

    REQUIRE(result["pekora.com"] == result["korone.com"]);
    REQUIRE(result["korone.com"] == result["marine.com"]);
}
