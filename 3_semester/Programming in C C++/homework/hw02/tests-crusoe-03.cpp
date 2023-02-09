#include "catch.hpp"

#include "crusoe.hpp"
#include "tests-helper.hpp"

/*
    Testy pro stage-03.

    Testy testuji definice vnorenych trid:
    - graph_comp
    - graph_fence

    Testy v tomto kroku předpokládají, že metody testované v minulém
    kroku fungují správně, a tudíž se na nich mohou stavět testy pro další
    funkcionalitu.
*/

TEST_CASE("Graph component - nine vertices", "[stage3][components]") {
    SECTION("Two components") {
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
        graph::graph_comp cmp{g};
        REQUIRE(cmp.count() == 2);
        REQUIRE(cmp.count_without_one() == 2);
        REQUIRE(cmp.size_of_comp(0) == 4);
        REQUIRE(cmp.size_of_comp(1) == 5);
        cmp.color_componennts();
        REQUIRE(color_all_component(g, cmp));
        save_graph(g);
    }

    SECTION("Four components") {
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
        graph::graph_comp cmp{g};
        REQUIRE(cmp.count() == 4);
        REQUIRE(cmp.count_without_one() == 2);
        REQUIRE(cmp.size_of_comp(cmp.max_comp()) == 4);
        cmp.color_componennts();
        REQUIRE(color_all_component(g, cmp));
        save_graph(g);
    }
}

TEST_CASE("Graph component", "[stage3][components]") {
    const size_t tests = 100;

    SECTION("Graph 10x10 - 20x20 vertices") {
        for (size_t iii = 0; iii < 3; ++iii) {
            size_t graph_size = 10 + iii * 5;
            for (size_t i = 0; i < tests; ++i) {
                graph g = generate(graph_size);
                graph::graph_comp cmp{g};
                size_t c_without_one = 0, c_vert = 0, c_vert1 = 0;
                for (size_t j = 0; j < cmp.count(); ++j) {
                    c_vert += cmp.get_component(j).size();
                    if (cmp.get_component(j).size() == 1) {
                        REQUIRE(0 == g.get_vertex(cmp.get_component(j)[0]).get_neighbour().size());
                        ++c_without_one;
                    } else {
                        REQUIRE(is_component(g, cmp.get_component(j)));
                        c_vert1 += cmp.get_component(j).size();
                    }
                }
                REQUIRE(c_without_one + cmp.count_without_one() == cmp.count());
                REQUIRE(c_vert == graph_size * graph_size);
                size_t tmp = cmp.count() - cmp.count_without_one();
                REQUIRE(c_vert1 + tmp == graph_size * graph_size);
                if (i == 57) {
                    cmp.color_componennts();
                    REQUIRE(color_all_component(g, cmp));
                    save_graph(g);
                }
            }
        }
    }
}

TEST_CASE("Graph component - there is a path", "[stage3][components]") {
    const size_t tests = 100;
    std::random_device dev;
    std::minstd_rand rng(time(NULL));

    SECTION("Graph 10x10 - 20x20 vertices") {
        for (size_t iii = 0; iii < 3; ++iii) {
            size_t graph_size = 10 + iii * 5;
            graph g = generate(graph_size);
            graph::graph_comp cmp{g};
            cmp.color_componennts();
            REQUIRE(color_all_component(g, cmp));
            size_t idx = cmp.max_comp(), size_comp = cmp.get_component(idx).size();
            std::uniform_int_distribution<std::minstd_rand::result_type> dist(0, size_comp - 1);
            size_t idx1, idx2;
            std::vector<size_t> pth;
            bool is_save = false;
            for (size_t i = 0; i < tests; ++i) {
                idx1 = cmp.get_component(idx)[dist(rng)];
                idx2 = cmp.get_component(idx)[dist(rng)];
                REQUIRE(cmp.same_comp(idx1, idx2));
                pth = g.path(idx1, idx2);
                REQUIRE(is_path(g, pth));
                if (pth.size() > graph_size && !is_save) {
                    g.set_vertex_color(idx1, "#9BFF00");
                    g.set_vertex_color(idx2, "#9BFF00");
                    g.color_path(pth, "#9BFF00");
                    save_graph(g);
                    is_save = true;
                }
            }
            for (size_t i = 0; i < tests; ++i) {
                idx1 = cmp.get_component(idx)[dist(rng)];
                std::vector<size_t> m_comp = cmp.get_component(idx);
                do {
                    idx2 = dist(rng);
                } while (std::find(m_comp.begin(), m_comp.end(), idx2) != m_comp.end());
                REQUIRE_FALSE(cmp.same_comp(idx1, idx2));
                pth = g.path(idx1, idx2);
                REQUIRE(pth.empty());
            }
        }
    }
}

TEST_CASE("Graph fence", "[stage3][fence]") {
    const size_t tests = 100;
    std::random_device dev;
    std::minstd_rand rng(time(NULL));

    SECTION("Graph 10x10 - 20x20 vertices") {
        for (size_t iii = 0; iii < 3; ++iii) {
            size_t graph_size = 10 + iii * 5;
            std::uniform_int_distribution<std::minstd_rand::result_type> f_dist(1, graph_size - 1);
            graph g = generate(graph_size);
            graph::graph_comp cmp{g};
            cmp.color_componennts();
            REQUIRE(color_all_component(g, cmp));
            size_t idx = cmp.max_comp(), size_comp = cmp.get_component(idx).size();
            std::uniform_int_distribution<std::minstd_rand::result_type> dist(0, size_comp - 1);
            size_t idx1;
            std::vector<size_t> pth;
            bool is_save = false;
            for (size_t i = 0; i < tests; ++i) {
                idx1 = cmp.get_component(idx)[dist(rng)];
                size_t ff_dist = f_dist(rng);
                graph::graph_fence fenc{g, idx1, ff_dist};
                if (ff_dist == graph_size / 3 && !is_save) {
                    fenc.color_fence("#9BFF00");
                    g.set_vertex_color(idx1, "#C6C200");
                    save_graph(g);
                    is_save = true;
                }
                for (size_t j = 0; j < fenc.count_stake(); ++j) {
                    pth = g.path(idx1, fenc.get_stake(j));
                    REQUIRE(is_path(g, pth));
                    REQUIRE(pth.size() <= ff_dist + 1);
                }
            }
        }
    }
}


