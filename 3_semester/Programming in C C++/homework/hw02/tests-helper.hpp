#ifndef LIST_TESTS_HELPER_HPP
#define LIST_TESTS_HELPER_HPP

#include "crusoe.hpp"
#include <random>
#include <ctime>

graph generate(size_t n);

bool is_component(graph& g, const std::vector<size_t>& vec);

bool is_path(graph& g, std::vector<size_t>& path);

bool color_all_component(graph& g, graph::graph_comp& cmp);

void save_graph(graph& g);

bool colored_and_save(graph& g, std::vector<size_t>& vec, const std::string& col = "red", bool is_comp = true);

#endif //LIST_TESTS_HELPER_HPP
