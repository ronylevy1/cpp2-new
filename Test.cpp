//roniki04@gmail.com
//ronylevy

#include "Algorithms.hpp"
#include "Graph.hpp"
#include "doctest.h"

TEST_CASE("Valid addition of graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 6},
        {7, 0}};
    g2.loadGraph(graph2);

    ariel::Graph result = g1 + g2;

    vector<vector<int>> expected = {
        {0, 8},
        {10, 0}};

    CHECK(result.getGraph() == expected);
}

TEST_CASE("Invalid addition of graphs with different sizes") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 6, 7},
        {8, 0, 10},
        {8, 9, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 + g2);
}

TEST_CASE("Valid addition assignment of graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 6},
        {7, 0}};
    g2.loadGraph(graph2);

    g1 += g2;

    vector<vector<int>> expected = {
        {0, 8},
        {10, 0}};

    CHECK(g1.getGraph() == expected);
}

TEST_CASE("Invalid addition assignment of graphs with different sizes") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 6, 7},
        {8, 0, 10},
        {8, 9, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 += g2);
}

TEST_CASE("Unary plus operator returns a copy of the graph") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2},
        {3, 0}};
    g.loadGraph(graph);

    ariel::Graph result = +g;

    CHECK(result.getGraph() == graph);
}

TEST_CASE("Prefix increment operator increments all non-zero values by one") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2},
        {3, 0}};
    g.loadGraph(graph);

    ++g;

    vector<vector<int>> expected = {
        {0, 3},
        {4, 0}};

    CHECK(g.getGraph() == expected);
}

TEST_CASE("Postfix increment operator increments all non-zero values by one and returns a copy of the original graph") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2},
        {3, 0}};
    g.loadGraph(graph);

    ariel::Graph result = g++;

    vector<vector<int>> expected = {
        {0, 3},
        {4, 0}};

    CHECK(g.getGraph() == expected);
    CHECK(result.getGraph() == graph);
}

TEST_CASE("Valid subtraction of graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 6},
        {7, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2},
        {3, 0}};
    g2.loadGraph(graph2);

    ariel::Graph result = g1 - g2;

    vector<vector<int>> expected = {
        {0, 4},
        {4, 0}};

    CHECK(result.getGraph() == expected);
}

TEST_CASE("Invalid subtraction of graphs with different sizes") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 6},
        {7, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2, 3},
        {4, 0, 6},
        {4, 5, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 - g2);
}

TEST_CASE("Valid subtraction assignment of graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 6},
        {7, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2},
        {3, 0}};
    g2.loadGraph(graph2);

    g1 -= g2;

    vector<vector<int>> expected = {
        {0, 4},
        {4, 0}};

    CHECK(g1.getGraph() == expected);
}

TEST_CASE("Invalid subtraction assignment of graphs with different sizes") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 6},
        {7, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2, 3},
        {4, 0, 6},
        {4, 5, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 -= g2);
}

TEST_CASE("Unary minus operator returns a copy of the graph with all values negated") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2},
        {3, 0}};
    g.loadGraph(graph);

    ariel::Graph result = -g;

    vector<vector<int>> expected = {
        {0, -2},
        {-3, 0}};

    CHECK(result.getGraph() == expected);
}

TEST_CASE("Prefix decrement operator decrements all non-zero values by one") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 6},
        {7, 0}};
    g.loadGraph(graph);

    --g;

    vector<vector<int>> expected = {
        {0, 5},
        {6, 0}};

    CHECK(g.getGraph() == expected);
}

TEST_CASE("Postfix decrement operator decrements all non-zero values by one and returns a copy of the original graph") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 6},
        {7, 0}};
    g.loadGraph(graph);

    ariel::Graph result = g--;

    vector<vector<int>> expected = {
        {0, 5},
        {6, 0}};

    CHECK(g.getGraph() == expected);
    CHECK(result.getGraph() == graph);
}
#include "Graph.hpp"
#include "doctest.h"

TEST_CASE("operator< with equal graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2},
        {3, 0}};
    g2.loadGraph(graph2);

    CHECK((g1 < g2) == false);
}

TEST_CASE("operator< with different graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {0, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 8},
        {7, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);

    graph1 = {
        {0, 2},
        {0, 0}};
    g1.loadGraph(graph1);

    graph2 = {
        {0, 0, 2},
        {0, 0, 0},
        {7, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);
}

TEST_CASE("operator== with equal graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2},
        {3, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 == g2);
}

TEST_CASE("operator== with different graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 6},
        {7, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 == g2);
}

TEST_CASE("operator!= with equal graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2},
        {3, 0}};
    g2.loadGraph(graph2);

    CHECK((g1 != g2) == false);
}

TEST_CASE("operator!= with different graphs") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 6},
        {7, 0}};
    g2.loadGraph(graph2);

    CHECK_FALSE(g1 != g2);
}

TEST_CASE("operator* with scalar multiplication") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2},
        {3, 0}};
    g.loadGraph(graph);

    double scalar = 2.0;
    ariel::Graph result = g * scalar;

    vector<vector<int>> expected = {
        {0, 4},
        {6, 0}};

    CHECK(result.getGraph() == expected);
}

TEST_CASE("operator* with matrix multiplication (valid size)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 1},
        {3, 0, 5},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 6, 1},
        {7, 0, 3},
        {2, 3, 0}};
    g2.loadGraph(graph2);

    ariel::Graph result = g1 * g2;

    vector<vector<int>> expected = {
        { 0, 3, 6},
        {10, 0, 3},
        {21, 12,0}};

    CHECK(result.getGraph() == expected);
}

TEST_CASE("operator* with matrix multiplication (invalid size)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2},
        {3, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 6, 7},
        {8, 0, 10},
        {8, 9, 0},
    };
    g2.loadGraph(graph2);
    CHECK_THROWS(g1 * g2);
}

TEST_CASE("operator*= with scalar multiplication") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2},
        {3, 0}};
    g.loadGraph(graph);

    double scalar = 2.0;
    g *= scalar;

    vector<vector<int>> expected = {
        {0, 4},
        {6, 0}};

    CHECK(g.getGraph() == expected);
}

TEST_CASE("operator*= with matrix multiplication") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 8, 9},
        {4, 0, 6},
        {1, 2, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 6},
        {7, 0, 3},
        {5, 3, 0}};
    g2.loadGraph(graph2);

    g1 *= g2;

    vector<vector<int>> expected = {
        {0, 27, 24},
        {30, 0, 24},
        {14, 1, 0}};

    CHECK(g1.getGraph() == expected);
}

TEST_CASE("operator/= with scalar division") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 4},
        {6, 0}};
    g.loadGraph(graph);

    double scalar = 2.0;
    g /= scalar;

    vector<vector<int>> expected = {
        {0, 2},
        {3, 0}};

    CHECK(g.getGraph() == expected);
}

TEST_CASE("operator/= with scalar division by zero") {
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 4},
        {6, 0}};
    g.loadGraph(graph);

    double scalar = 0.0;
    CHECK_THROWS(g /= scalar);
}
