#include "tests-helper.hpp"
#include <random>
#include <ctime>

graph generate(size_t n) {
    std::random_device dev;
    std::minstd_rand rng(time(NULL));
    std::uniform_int_distribution<std::minstd_rand::result_type> dist(0,1);
    graph g;
    std::vector<std::pair<size_t, size_t>> edges;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j) {
            g.add_vertex(j * 25 + 10, i * 25 + 10);
            size_t num = g.size() - 1;
            if (j > 0 && dist(rng)) {
                g.add_edge(num, num - 1);
                edges.emplace_back(num, num - 1);
            }
            if (i > 0 && dist(rng)) {
                g.add_edge(num, num - n);
                edges.emplace_back(num, num - n);
            };
        };
    return g;
}

bool is_component(graph& g, const std::vector<size_t>& vec) {
    bool is_OK = true;
    for (auto& i : vec) {
        std::vector<std::pair<size_t, std::string>> tmp = g.get_vertex(i).get_neighbour();
        for (auto& nn : tmp)
            if (std::find(vec.begin(), vec.end(), nn.first) == vec.end())
                is_OK = false;
    }
    return is_OK;
}

bool is_path(graph& g, std::vector<size_t>& path) {
    bool is_OK = true;
    if (path.empty())
        return is_OK;
    auto first = path.begin();
    for (auto i = path.begin() + 1; i < path.end(); ++i) {
        if (!g.is_edge(*first, *i))
            is_OK = false;
        if (std::find(i, path.end(), *first) != path.end())
            is_OK = false;
        first = i;
    }
    return is_OK;
}

bool color_all_component(graph& g, graph::graph_comp& cmp) {
    bool is_OK = true;
    for (size_t j = 0; j < cmp.count(); ++j) {
        std::string m_color = g.get_vertex(cmp.get_component(j)[0]).get_color();
        for (auto i : cmp.get_component(j)) {
            if (g.get_vertex(i).get_color() != m_color)
                is_OK = false;
            for (auto& vv : g.get_vertex(i).get_neighbour())
                if (g.edge_color(vv.first, i) != m_color)
                    is_OK = false;
        }
    }
    return is_OK;
}

void save_graph(graph& g) {
    std::ofstream f("image.svg");
    f << g;
    f.close();
}
bool colored_and_save(graph& g, std::vector<size_t>& vec, const std::string& col, bool is_comp) {
    bool is_res = false;
    if (vec.size() > 0) {
        if (is_comp) {
            g.color_component(vec, col);
             is_res = is_component(g, vec);
        } else {
            g.color_path(vec, col);
            g.set_vertex_color(vec[0], col);
            g.set_vertex_color(vec[vec.size() - 1], col);
            is_res = is_path(g, vec);
        }
    } else is_res = true;
    save_graph(g);
    return is_res;
}
