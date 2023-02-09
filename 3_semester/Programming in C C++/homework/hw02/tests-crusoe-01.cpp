#include "catch.hpp"

#include "crusoe.hpp"
#include "tests-helper.hpp"

#include <vector>
#include <random>
#include <ctime>

/*
   Testy pro stage-01.

   Testy testuji zakladni sadu funkci trid vertex a graph
   (viz popis v graph.hpp].

   Kvůli omezení se na tuto sadu metod vám tyto testy neodhalí všechny
   chyby, ale měly by jich najít většinu. V dalších krocích se očekává,
   že vám metody z tohoto kroku fungují.
*/

TEST_CASE("Default constructed list passes basic accessors", "[stage1][basic]") {
    graph g;
    REQUIRE(g.empty());
    REQUIRE(g.size() == 0);
    REQUIRE(g.num_edge() == 0);
}

TEST_CASE("Trivial use of add_vertex", "[stage1][basic]") {
    graph g;
    g.add_vertex(20, 20);
    REQUIRE(g.size() == 1);
    REQUIRE_FALSE(g.empty());

    g.add_vertex(60, 20);
    REQUIRE(g.size() == 2);

    g.add_vertex(20, 60);
    REQUIRE(g.size() == 3);
    save_graph(g);
}

TEST_CASE("add_vertex and add_edge", "[stage1][basic]") {
    graph g;
    g.add_vertex(20, 20);
    g.add_vertex(60, 20);
    g.add_vertex(20, 60);
    g.add_vertex(60, 60);
    REQUIRE(g.size() == 4);

    g.add_edge(3, 2);
    REQUIRE(g.is_edge(3, 2));
    REQUIRE(g.is_edge(2, 3));
    g.add_edge(3, 1);
    REQUIRE(g.is_edge(3, 1));
    REQUIRE(g.is_edge(1, 3));
    REQUIRE_FALSE(g.is_edge(1, 2));
    REQUIRE_FALSE(g.is_edge(0, 4));
    REQUIRE_FALSE(g.is_edge(-1, 3));
    save_graph(g);
}

TEST_CASE("add_vertex when the edge does not exist", "[stage1][basic]") {
    graph g;
    g.add_vertex(20, 20);
    g.add_vertex(60, 20);
    g.add_vertex(20, 60);
    g.add_vertex(60, 60);
    REQUIRE(g.size() == 4);

    g.add_edge(3, 2);
    REQUIRE(g.is_edge(3, 2));
    REQUIRE(g.is_edge(2, 3));
    REQUIRE(g.num_edge() == 1);
    g.add_edge(2, 3);
    REQUIRE(g.num_edge() == 1);

    g.add_edge(1, 3);
    REQUIRE(g.is_edge(3, 1));
    REQUIRE(g.is_edge(1, 3));
    REQUIRE(g.num_edge() == 2);
    g.add_edge(1, 3);
    REQUIRE(g.num_edge() == 2);
    REQUIRE_FALSE(g.is_edge(1, 2));
    REQUIRE_FALSE(g.is_edge(0, 4));
    REQUIRE_FALSE(g.is_edge(-1, 3));
    save_graph(g);
}

TEST_CASE("add_vertex with color", "[stage1][colored]") {
    graph g;
    g.add_vertex(20, 20, "red");
    g.add_vertex(60, 20, "#FF6DE1");
    g.add_vertex(20, 60, "olive");
    g.add_vertex(60, 60, "#0000FF");
    REQUIRE(g.size() == 4);

    REQUIRE(g.vertex_color(0) == "red");
    REQUIRE(g.vertex_color(1) == "#FF6DE1");
    REQUIRE(g.vertex_color(2) == "olive");
    REQUIRE(g.vertex_color(3) == "#0000FF");
    save_graph(g);
}

TEST_CASE("add_edge with color", "[stage1][colored]") {
    graph g;
    g.add_vertex(20, 20);
    g.add_vertex(60, 20);
    g.add_vertex(20, 60);
    REQUIRE(g.size() == 3);
    g.add_edge(2, 0);
    g.add_edge(1, 0);
    REQUIRE(g.num_edge() == 2);
    g.add_vertex(60, 60);
    REQUIRE(g.size() == 4);

    g.add_edge(3, 2);
    g.add_edge(3, 1);
    REQUIRE(g.num_edge() == 4);
    g.add_edge(3, 0, "red");
    g.add_edge(2, 1, "orange");
    REQUIRE(g.num_edge() == 6);

    REQUIRE(g.edge_color(1, 2) == "orange");
    REQUIRE(g.edge_color(0, 3) == "red");
    REQUIRE(g.edge_color(0, 1) == "#000000");
    REQUIRE(g.is_edge(1, 2));
    REQUIRE(g.edge_color(1, 2) == "orange");
    REQUIRE_FALSE(g.is_edge(0, 4));
    REQUIRE(g.edge_color(0, 4) == "#FFFFFF");
    save_graph(g);
}

TEST_CASE("set_vertex_color", "[stage1][colored]") {
    graph g;
    g.add_vertex(20, 128);
    g.add_vertex(20, 100);
    g.add_vertex(40, 80);
    g.add_vertex(68, 80);
    g.add_vertex(88, 100);
    g.add_vertex(88, 128);
    g.add_vertex(68, 148);
    g.add_vertex(40, 148);
    REQUIRE(g.size() == 8);
    REQUIRE_FALSE(g.empty());

    for (size_t i = 0; i < g.size(); i += 2)
        g.set_vertex_color(i, "yellow");
    REQUIRE(g.vertex_color(0) == "yellow");
    REQUIRE(g.vertex_color(1) == "#000000");
    REQUIRE(g.vertex_color(2) == "yellow");

    g.set_vertex_color(10, "yellow");
    REQUIRE(g.vertex_color(10) == "#FFFFFF");
    save_graph(g);
}

TEST_CASE("set_edge_color", "[stage1][colored]") {
    graph g;
    g.add_vertex(20, 128);
    g.add_vertex(20, 100);
    g.add_vertex(40, 80);
    g.add_vertex(68, 80);
    g.add_vertex(88, 100);
    g.add_vertex(88, 128);
    g.add_vertex(68, 148);
    g.add_vertex(40, 148);
    REQUIRE(g.size() == 8);
    REQUIRE_FALSE(g.empty());

    for (size_t i = 0; i < g.size(); ++i) {
        g.add_edge(i, (i + 1) % g.size());
        if (i % 2) {
            g.set_edge_color(i, (i + 1) % g.size(), "magenta");
            g.set_vertex_color(i, "yellow");
        }
    }
    for (size_t i = 0; i < g.size(); ++i) {
        if (i % 2)
            REQUIRE(g.edge_color((i - 1) % g.size(), i) == "#000000");
        else
            REQUIRE(g.edge_color((i - 1) % g.size(), i) == "magenta");
    }
    g.set_edge_color(0, 10, "magenta");
    REQUIRE_FALSE(g.edge_color(0, 10) == "magenta");
    REQUIRE("#FFFFFF" == g.edge_color(0, 10));
    save_graph(g);
}

TEST_CASE("More complex test cases", "[stage1][complex]") {
    std::random_device dev;
    std::minstd_rand rng(time(NULL));
    std::uniform_int_distribution<std::minstd_rand::result_type> dist(0,1);

    for (int k = 1; k <= 10; ++k) {
        graph g;
        std::vector<std::pair<size_t, size_t>> edges;
        for (size_t i = 0; i < 3 * k; ++i)
            for (size_t j = 0; j < 3 * k; ++j) {
                g.add_vertex(j * 25 + 10, i * 25 + 10);
                size_t num = g.size() - 1;
                if (j > 0 && dist(rng)) {
                    g.add_edge(num, num - 1);
                    edges.emplace_back(num, num - 1);
                }
                if (i > 0 && dist(rng)) {
                    g.add_edge(num, num - 3 * k);
                    edges.emplace_back(num, num - 3 * k);
                };
            };
        REQUIRE(edges.size() == g.num_edge());
        if (k == 6)
            save_graph(g);
        for (size_t i = 0; i < edges.size(); ++i) {
            REQUIRE(g.is_edge(edges[i].second, edges[i].first));
        }
    }
}
