#include "catch.hpp"

#include "crusoe.hpp"
#include "tests-helper.hpp"
/*
    Testy pro stage-02.

    Testy testuji metody:
    - get_vertex
    - is_achievable
    - color_component
    - path
    - color_path


    Testy v tomto kroku predpokladaji, ze metody testovane v minulem
    kroku funguji spravne, a tudiz se na nich mohou stavet testy pro dalsi
    funkcionalitu.

*/

TEST_CASE("Graph component - four vertices", "[stage2][component]") {
    graph g;
    g.add_vertex(20, 20);
    g.add_vertex(60, 20);
    g.add_vertex(20, 60);
    g.add_vertex(60, 60);
    std::vector<size_t> comp;

    SECTION("One vertex") {
        g.is_achievable(0, comp);
        REQUIRE_FALSE(comp.empty());
        REQUIRE(comp.size() == 1);
        REQUIRE(comp[0] == 0);
        REQUIRE(colored_and_save(g, comp));
        REQUIRE(g.get_vertex(0).get_color() == "red");
    }
    SECTION("Two vertices") {
        g.add_edge(0, 1);
        g.is_achievable(0, comp);
        REQUIRE_FALSE(comp.empty());
        REQUIRE(comp.size() == 2);
        REQUIRE(comp[0] == 0);
        REQUIRE(comp[1] == 1);
        REQUIRE(colored_and_save(g, comp));
        REQUIRE(g.get_vertex(0).get_color() == "red");
        REQUIRE(g.get_vertex(1).get_color() == "red");
        REQUIRE(g.get_vertex(0).get_edge_color(1) == "red");
    }

    SECTION("Two vertices") {
        g.add_edge(0, 3);
        g.is_achievable(0, comp);
        REQUIRE_FALSE(comp.empty());
        REQUIRE(comp.size() == 2);
        REQUIRE(comp[0] == 0);
        REQUIRE(comp[1] == 3);
        REQUIRE(colored_and_save(g, comp));
        REQUIRE(g.get_vertex(0).get_color() == "red");
        REQUIRE(g.get_vertex(3).get_color() == "red");
        REQUIRE(g.get_vertex(0).get_edge_color(3) == "red");
        REQUIRE(g.get_vertex(3).get_edge_color(0) == "red");
    }

    SECTION("Three vertices") {
        g.add_edge(2, 0);
        g.add_edge(0, 1);
        g.is_achievable(0, comp);
        REQUIRE(comp.size() == 3);
        REQUIRE(colored_and_save(g, comp));
        REQUIRE(g.get_vertex(0).get_color() == "red");
        REQUIRE(g.get_vertex(1).get_color() == "red");
        REQUIRE(g.get_vertex(2).get_color() == "red");
        REQUIRE(g.get_vertex(2).get_edge_color(0) == "red");
        REQUIRE(g.get_vertex(1).get_edge_color(0) == "red");
        REQUIRE(g.get_vertex(1).get_edge_color(2) == "#FFFFFF");
    }

    SECTION("Four vertices") {
        g.add_edge(2, 0);
        g.add_edge(0, 1);
        g.add_edge(3, 1);
        g.is_achievable(0, comp);
        REQUIRE(comp.size() == 4);
        REQUIRE(colored_and_save(g, comp));
    }

    SECTION("Four vertices") {
        g.add_edge(2, 0);
        g.add_edge(0, 1);
        g.add_edge(3, 1);
        g.add_edge(3, 2);
        g.is_achievable(0, comp);
        REQUIRE(comp.size() == 4);
        REQUIRE(colored_and_save(g, comp));
    }
}

TEST_CASE("Graph component - nine vertices", "[stage2][component]") {
    graph g;
    g.add_vertex(20, 20);
    g.add_vertex(60, 20);
    g.add_vertex(100, 20);
    g.add_vertex(20, 60);
    g.add_vertex(60, 60);
    g.add_vertex(100, 60);
    g.add_vertex(20, 100);
    g.add_vertex(60, 100);
    g.add_vertex(100, 100);
    std::vector<size_t> comp;

    SECTION("One vertex") {
        g.is_achievable(0, comp);
        REQUIRE_FALSE(comp.empty());
        REQUIRE(comp.size() == 1);
        REQUIRE(comp[0] == 0);
        REQUIRE(colored_and_save(g, comp));
    }
    SECTION("Two vertices") {
        g.add_edge(5, 0);
        g.is_achievable(0, comp);
        REQUIRE_FALSE(comp.empty());
        REQUIRE(comp.size() == 2);
        REQUIRE(comp[0] == 0);
        REQUIRE(comp[1] == 5);
        REQUIRE(colored_and_save(g, comp));
    }

    SECTION("Three vertices") {
        g.add_edge(4, 0);
        g.add_edge(0, 1);
        g.is_achievable(0, comp);
        REQUIRE(comp.size() == 3);
        REQUIRE(colored_and_save(g, comp));
    }

    SECTION("Seven vertices") {
        g.add_edge(3, 0);
        g.add_edge(0, 1);
        g.add_edge(3, 4);
        g.add_edge(1, 2);
        g.add_edge(1, 4);
        g.add_edge(3, 6);
        g.add_edge(7, 6);
        g.add_edge(4, 7);
        g.is_achievable(0, comp);
        REQUIRE(comp.size() == 7);
        REQUIRE(colored_and_save(g, comp));
    }

    SECTION("Five vertices") {
        g.add_edge(3, 0);
        g.add_edge(3, 4);
        g.add_edge(4, 1);
        g.add_edge(3, 6);
        g.add_edge(1, 0);
        g.is_achievable(0, comp);
        REQUIRE(comp.size() == 5);
        REQUIRE(colored_and_save(g, comp));
    }
}

TEST_CASE("Graph component - nine vertices, a lot of components", "[stage2][component]") {
    graph g;
    g.add_vertex(20, 20);
    g.add_vertex(60, 20);
    g.add_vertex(100, 20);
    g.add_vertex(20, 60);
    g.add_vertex(60, 60);
    g.add_vertex(100, 60);
    g.add_vertex(20, 100);
    g.add_vertex(60, 100);
    g.add_vertex(100, 100);
    g.add_edge(3, 0);
    g.add_edge(3, 4);
    g.add_edge(3, 6);
    g.add_edge(1, 2);
    g.add_edge(2, 5);
    g.add_edge(8, 5);
    g.add_edge(7, 8);

    SECTION("Component of vertex 0") {
        std::vector<size_t> comp;
        g.is_achievable(0, comp);
        REQUIRE(comp.size() == 4);
        REQUIRE(colored_and_save(g, comp));
    }

    SECTION("Component of vertex 5") {
        std::vector<size_t> comp;
        g.is_achievable(5, comp);
        REQUIRE(comp.size() == 5);
        REQUIRE(colored_and_save(g, comp));
    }

    SECTION("Component of other vertices") {
        std::vector<size_t> res = {4, 5, 5, 4, 4, 5, 4, 5, 5};
        for (size_t i = 0; i < 9; ++i) {
            std::vector<size_t> comp;
            g.is_achievable(i, comp);
            REQUIRE(comp.size() == res[i]);
            REQUIRE(is_component(g, comp));
        }
        std::vector<size_t> comp;
        g.is_achievable(5, comp);
        REQUIRE(colored_and_save(g, comp));
    }
}

TEST_CASE("Graph component - random", "[stage2][component]") {
    const size_t tests = 100;

    SECTION("Component of all vertices - graph 3x3") {
        const size_t graph_size = 3;
        for (size_t i = 0; i < tests; ++i) {
            graph g = generate(graph_size);
            for (size_t j = 0; j < graph_size * graph_size; ++j) {
                std::vector<size_t> comp;
                g.is_achievable(j, comp);
                REQUIRE(is_component(g, comp));
            }
        }
        graph g = generate(graph_size);
        std::vector<size_t> comp;
        g.is_achievable(5, comp);
        REQUIRE(colored_and_save(g, comp));
    }

    SECTION("Component of all vertices - graph 5x5") {
        const size_t graph_size = 5;
        for (size_t i = 0; i < tests; ++i) {
            graph g = generate(graph_size);
            for (size_t j = 0; j < graph_size * graph_size; ++j) {
                std::vector<size_t> comp;
                g.is_achievable(j, comp);
                REQUIRE(is_component(g, comp));
            }
        }
        graph g = generate(graph_size);
        std::vector<size_t> comp;
        g.is_achievable(5, comp);
        REQUIRE(colored_and_save(g, comp));
    }

    SECTION("Component of all vertices - graph 10x10 and bigger") {
        const size_t graph_size = 10;
        std::random_device dev;
        std::minstd_rand rng(time(NULL));
        std::uniform_int_distribution<std::minstd_rand::result_type> dist(0, 2 * graph_size);
        for (size_t i = 0; i < tests; ++i) {
            size_t my_size = graph_size + (i / 2);
            graph g = generate(my_size);
            std::vector<size_t> comp;
            g.is_achievable(dist(rng), comp);
            REQUIRE(is_component(g, comp));
            comp.clear();
            g.is_achievable(2 * dist(rng), comp);
            REQUIRE(is_component(g, comp));
            comp.clear();
            g.is_achievable(4 * dist(rng), comp);
            REQUIRE(is_component(g, comp));
        }
        graph g = generate(graph_size + 5);
        std::vector<size_t> comp;
        g.is_achievable(5, comp);
        REQUIRE(colored_and_save(g, comp, "lightblue"));
        REQUIRE(g.get_vertex(5).get_color() == "lightblue");
        for (auto& i : g.get_vertex(5).get_neighbour()) {
            REQUIRE(i.second == "lightblue");
            for (auto& j : g.get_vertex(i.first).get_neighbour())
                REQUIRE(j.second == "lightblue");
        }
    }
}

TEST_CASE("Graph path - four vertices", "[stage2][path]") {
    graph g;
    g.add_vertex(20, 20);
    g.add_vertex(60, 20);
    g.add_vertex(20, 60);
    g.add_vertex(60, 60);
    std::vector<size_t> pth;

    SECTION("One vertex") {
        pth = g.path(0, 1);
        REQUIRE(pth.empty());
        REQUIRE(colored_and_save(g, pth, "red", false));
    }
    SECTION("Two vertices") {
        g.add_edge(0, 1);
        pth = g.path(0, 1);
        REQUIRE_FALSE(pth.empty());
        REQUIRE(pth.size() == 2);
        REQUIRE(pth[0] == 0);
        REQUIRE(pth[1] == 1);
        REQUIRE(colored_and_save(g, pth, "red", false));
        REQUIRE(g.get_vertex(0).get_edge_color(1) == "red");
    }

    SECTION("Two vertices") {
        g.add_edge(0, 3);
        pth = g.path(0, 3);
        REQUIRE_FALSE(pth.empty());
        REQUIRE(pth.size() == 2);
        REQUIRE(pth[0] == 0);
        REQUIRE(pth[1] == 3);
        REQUIRE(colored_and_save(g, pth, "green", false));
        REQUIRE(g.get_vertex(0).get_edge_color(3) == "green");
        REQUIRE(g.get_vertex(3).get_edge_color(0) == "green");
    }

    SECTION("Three vertices") {
        g.add_edge(2, 0);
        g.add_edge(0, 1);
        pth = g.path(2, 1);
        REQUIRE(pth.size() == 3);
        REQUIRE(colored_and_save(g, pth, "blue", false));
        REQUIRE(g.get_vertex(2).get_edge_color(0) == "blue");
        REQUIRE(g.get_vertex(1).get_edge_color(0) == "blue");
        REQUIRE(g.get_vertex(0).get_edge_color(1) == "blue");
        REQUIRE(g.get_vertex(1).get_edge_color(2) == "#FFFFFF");
    }

    SECTION("Three vertices") {
        g.add_edge(2, 0);
        g.add_edge(0, 1);
        pth = g.path(0, 3);
        REQUIRE(pth.size() == 0);
        REQUIRE(colored_and_save(g, pth, "blue", false));
        REQUIRE(g.get_vertex(1).get_edge_color(2) == "#FFFFFF");
    }

    SECTION("Four vertices") {
        g.add_edge(2, 0);
        g.add_edge(0, 1);
        g.add_edge(3, 1);
        pth = g.path(2, 3);
        REQUIRE(pth.size() == 4);
        REQUIRE(colored_and_save(g, pth, "green", false));
    }
}

TEST_CASE("Graph path - nine vertices", "[graph_nine][path]") {
    graph g;
    g.add_vertex(20, 20);
    g.add_vertex(60, 20);
    g.add_vertex(100, 20);
    g.add_vertex(20, 60);
    g.add_vertex(60, 60);
    g.add_vertex(100, 60);
    g.add_vertex(20, 100);
    g.add_vertex(60, 100);
    g.add_vertex(100, 100);
    std::vector<size_t> pth;

    SECTION("Three vertices") {
        g.add_edge(4, 0);
        g.add_edge(0, 1);
        pth = g.path(1, 4);
        REQUIRE(pth.size() == 3);
        REQUIRE(pth[0] == 1);
        REQUIRE(pth[1] == 0);
        REQUIRE(pth[2] == 4);
        REQUIRE(colored_and_save(g, pth, "blue", false));
    }

    SECTION("Seven vertices") {
        g.add_edge(3, 0);
        g.add_edge(0, 1);
        g.add_edge(3, 4);
        g.add_edge(1, 2);
        g.add_edge(1, 4);
        g.add_edge(3, 6);
        g.add_edge(7, 6);
        g.add_edge(4, 7);
        pth = g.path(2, 6);
        REQUIRE(pth.size() == 5);
        REQUIRE(colored_and_save(g, pth, "blue", false));
    }

    SECTION("Five vertices") {
        g.add_edge(3, 0);
        g.add_edge(3, 4);
        g.add_edge(4, 1);
        g.add_edge(3, 6);
        g.add_edge(1, 0);
        pth = g.path(2, 6);
        REQUIRE(pth.size() == 0);
        pth = g.path(5, 6);
        REQUIRE(pth.size() == 0);
        pth = g.path(0, 8);
        REQUIRE(pth.size() == 0);
        pth = g.path(6, 1);
        REQUIRE(pth.size() == 4);
        REQUIRE(colored_and_save(g, pth, "red", false));
    }

    SECTION("Component of other vertices") {
        g.add_edge(3, 0);
        g.add_edge(3, 4);
        g.add_edge(3, 6);
        g.add_edge(1, 2);
        g.add_edge(2, 5);
        g.add_edge(8, 5);
        g.add_edge(7, 8);
        std::vector<size_t> res = {0, 0, 2, 3, 0, 3, 0, 0};
        for (size_t i = 1; i < 9; ++i) {
            pth = g.path(0, i);
            REQUIRE(pth.size() == res[i - 1]);
            REQUIRE(is_path(g, pth));
        }
        std::vector<size_t> ress = {0, 4, 3, 0, 0, 2, 0, 2};
        for (size_t i = 0; i < 8; ++i) {
            pth = g.path(8, i);
            REQUIRE(pth.size() == ress[i]);
            REQUIRE(is_path(g, pth));
        }
        pth = g.path(1, 7);
        REQUIRE(colored_and_save(g, pth, "lightgreen", false));
    }
}


TEST_CASE("Graph path - random", "[stage2][path]") {
    const size_t tests = 100;
    std::random_device dev;
    std::minstd_rand rng(time(NULL));

    SECTION("Component of all vertices - graph 3x3") {
        const size_t graph_size = 3;
        size_t max_path = graph_size;
        std::uniform_int_distribution<std::minstd_rand::result_type> dist(0, (graph_size * graph_size) / 2);
        for (size_t i = 0; i < tests; ++i) {
            graph g = generate(graph_size);
            for (size_t j = 0; j < graph_size * graph_size; ++j) {
                std::vector<size_t> pth;
                pth = g.path(dist(rng), 2 * dist(rng));
                REQUIRE(is_path(g, pth));
                if (pth.size() > max_path) {
                    max_path = pth.size();
                    REQUIRE(colored_and_save(g, pth, "red", false));
                }
            }
        }
    }

    SECTION("Component of all vertices - graph 5x5") {
        const size_t graph_size = 5;
        size_t max_path = graph_size;
        std::uniform_int_distribution<std::minstd_rand::result_type> dist(0, (graph_size * graph_size) / 2);
        for (size_t i = 0; i < tests; ++i) {
            graph g = generate(graph_size);
            for (size_t j = 0; j < graph_size * graph_size; ++j) {
                std::vector<size_t> pth;
                pth = g.path(dist(rng), 2 * dist(rng));
                REQUIRE(is_path(g, pth));
                if (pth.size() > max_path) {
                    max_path = pth.size();
                    REQUIRE(colored_and_save(g, pth, "red", false));
                }
            }
        }
    }

    SECTION("Component of all vertices - graph 10x10 and bigger") {
        const size_t graph_size = 10;
        std::random_device dev;
        std::minstd_rand rng(time(NULL));
        std::uniform_int_distribution<std::minstd_rand::result_type> dist(0, 2 * graph_size);
        for (size_t i = 0; i < tests; ++i) {
            size_t my_size = graph_size + (i / 2);
            size_t max_path = my_size;
            std::uniform_int_distribution<std::minstd_rand::result_type> dist(0, (my_size * my_size) / 2);
            graph g = generate(my_size);
            std::vector<size_t> pth;
            pth = g.path(dist(rng), 2 * dist(rng));
            REQUIRE(is_path(g, pth));
            if (pth.size() > max_path && my_size <= 20) {
                max_path = pth.size();
                REQUIRE(colored_and_save(g, pth, "red", false));
            }
            pth.clear();
            pth = g.path(dist(rng), 2 * dist(rng));
            REQUIRE(is_path(g, pth));
            if (pth.size() > max_path && my_size <= 20) {
                max_path = pth.size();
                REQUIRE(colored_and_save(g, pth, "red", false));
            }
            pth.clear();
            pth = g.path(dist(rng), 2 * dist(rng));
            REQUIRE(is_path(g, pth));
            if (pth.size() > max_path && my_size <= 20) {
                max_path = pth.size();
                REQUIRE(colored_and_save(g, pth, "red", false));
            }
        }
    }
}