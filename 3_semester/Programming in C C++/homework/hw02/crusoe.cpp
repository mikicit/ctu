#include "crusoe.hpp"

#include <utility>
#include <queue>

using namespace std;

// Stage 1

// vertex

// default constructor
vertex::vertex() = default;

// constructor with args
vertex::vertex(string str, int x, int y, string col) {
    xy.first = x;
    xy.second = y;
    name = std::move(str);
    c_forward = std::move(col);
}

bool vertex::add_neighbour(size_t vv, const std::string& col) {
    for (auto &neighbour : neighbours) {
        if (neighbour.first == vv) return false;
    }
    neighbours.emplace_back(vv, col);
    return true;
}

vector<pair<size_t, string>> vertex::get_neighbour() const {
    return neighbours;
}

pair<int, int> vertex::get_xy() const {
    return xy;
}

void vertex::set_color(const string &col) {
    c_forward = col;
}

string vertex::get_color() const {
    return c_forward;
}

void vertex::set_edge_color(size_t vv, const string &col) {
    for (auto &neighbour : neighbours) {
        if (neighbour.first == vv) {
            neighbour.second = col;
        }
    }
}

string vertex::get_edge_color(size_t vv) {
    for (const auto &neighbour : neighbours) {
        if (neighbour.first == vv) {
            return neighbour.second;
        }
    }
    return "#FFFFFF";
}

// graph

void graph::add_vertex(int x, int y, const string &col) {
    vertices.emplace_back(to_string(++num_elem), x, y, col);
}

void graph::add_edge(size_t v1, size_t v2, const string &col) {
    if (num_elem == 0 || v1 > num_elem - 1 || v2 > num_elem - 1) return;

    vertices[v1].add_neighbour(v2, col);
    vertices[v2].add_neighbour(v1, col);
}

bool graph::is_edge(size_t v1, size_t v2) const {
    if (num_elem == 0 || v1 > num_elem - 1 || v2 > num_elem - 1) return false;

    for (const auto &neighbour : vertices[v1].get_neighbour()) {
        if (neighbour.first == v2) return true;
    }

    return false;
}

string graph::edge_color(size_t v1, size_t v2) const {
    if (num_elem == 0 || v1 > num_elem - 1 || v2 > num_elem - 1) return "#FFFFFF";

    for (const auto &neighbour : vertices[v1].get_neighbour()) {
        if (neighbour.first == v2) {
            return neighbour.second;
        }
    }

    return "#FFFFFF";
}

std::string graph::vertex_color(size_t v1) const {
    if (num_elem == 0 || v1 > num_elem - 1) return "#FFFFFF";

    return vertices[v1].get_color();
}

void graph::set_vertex_color(size_t v1, const string &col) {
    if (num_elem == 0 || v1 > num_elem - 1) return;
    vertices[v1].set_color(col);
}

void graph::set_edge_color(size_t v1, size_t v2, const string &col) {
    if (num_elem == 0 || v1 > num_elem - 1 || v2 > num_elem - 1) return;
    vertices[v1].set_edge_color(v2, col);
    vertices[v2].set_edge_color(v1, col);
}

bool graph::empty() const {
    return vertices.empty();
}

size_t graph::size() const {
    return num_elem;
}

size_t graph::num_edge() const {
    size_t num_edge = 0;

    for (const auto &vertex : vertices) {
        num_edge += vertex.get_neighbour().size();
    }

    return num_edge / 2;
}

// Stage 2

vertex graph::get_vertex(size_t num) const {
    return vertices[num];
}

void graph::is_achievable(size_t from, vector<size_t> &achieved) {
    vector<bool> visited(num_elem, false);

    auto dfs = [&visited, &achieved, this](auto &&self, size_t start) -> void {
        visited[start] = true;
        achieved.push_back(start);
        for (const auto &v : vertices[start].get_neighbour()) {
            if (!visited[v.first]) {
                self(self, v.first);
            }
        }
    };

    dfs(dfs, from);
}

void graph::color_component(vector<size_t> cmp, const string &col) {
    for (const auto &i : cmp) {
        vertices[i].set_color(col);
        for (const auto &n : vertices[i].get_neighbour()) {
            vertices[i].set_edge_color(n.first, col);
        }
    }
}

vector<size_t> graph::path(size_t v1, size_t v2) {
    vector<bool> visited(num_elem, false);
    vector<long long int> prev(num_elem, -1);
    queue<size_t> queue;
    vector<size_t> path = {};

    if (num_elem == 0 || v1 > num_elem - 1 || v2 > num_elem - 1) return path;

    queue.push(v1);
    visited[v1] = true;
    prev[v1] = -1;

    while (!queue.empty()) {
        size_t v = queue.front();
        queue.pop();

        for (const auto &vv : vertices[v].get_neighbour()) {
            if (!visited[vv.first]) {
                queue.push(vv.first);
                prev[vv.first] = v;
                visited[vv.first] = true;
            }
        }
    }

    size_t current = v2;
    if (prev[current] == -1) return path;
    path.push_back(v2);

    while (prev[current] != -1) {
        current = prev[current];
        path.push_back(current);
    }

    reverse(path.begin(), path.end());

    return path;
}

void graph::color_path(vector<size_t> pth, const string &col) {
    for (size_t i = 1; i < pth.size(); i++) {
        set_edge_color(pth[i - 1], pth[i], col);
    }
}

// Stage 3

// graph_comp

graph::graph_comp::graph_comp(graph &gg) : gg(gg) {
    vector<size_t> found; // vertices for which the components have already been found
    found.reserve(gg.vertices.size());

    size_t current = 0; // The vertex for which we will find the component, if it is not already found
    while (found.size() != gg.vertices.size()) {
        while (find(found.begin(), found.end(), current) != found.end()) {
            current++;
        }

        vector<size_t> component;
        gg.is_achievable(current, component);
        components.push_back(component);

        for (const auto &v : component) {
            found.push_back(v);
        }

        component.clear();
    }
}

void graph::graph_comp::color_componennts() {
    vector<string> colors{"red", "olive", "orange", "lightblue", "yellow", "pink", "cyan", "purple", "brown", "magenta"};
    int colorsQuantity = int(colors.size());

    int current_color = 0;
    for (const auto &cmp : components) {
        if (cmp.size() > 1) {
            gg.color_component(cmp, colors[current_color]);
            current_color = (current_color + 1) % colorsQuantity;
        }
    }
}

size_t graph::graph_comp::count() const {
    return components.size();
}

size_t graph::graph_comp::count_without_one() const {
    size_t count = 0;

    for (const auto &c : components) {
        if (c.size() > 1) count++;
    }

    return count;
}

size_t graph::graph_comp::max_comp() const {
    size_t max = 0;
    size_t maxIndex = 0;

    size_t index = 0;
    for (const auto &c : components) {
        if (c.size() > max) {
            max = c.size();
            maxIndex = index;
        };
        index++;
    }

    return maxIndex;
}

size_t graph::graph_comp::size_of_comp(size_t i) const {
    if (components.empty() || i > components.size() - 1) return 0;

    return components[i].size();
}

std::vector<size_t> graph::graph_comp::get_component(size_t i) const {
    return components[i];
}

bool graph::graph_comp::same_comp(size_t v1, size_t v2) const {
    vector<size_t> cmp;
    gg.is_achievable(v1, cmp);

    for (const auto &v : cmp) {
        if (v == v2) {
            return true;
        }
    }

    return false;
}

// graph_fence

graph::graph_fence::graph_fence(graph &gg, size_t vv, size_t distance) : gg(gg) {
    vector<bool> visited(gg.num_elem, false);
    vector<long long int> d(gg.num_elem, -1); // Distance for each vector
    queue<size_t> queue;

    queue.push(vv);
    visited[vv] = true;
    d[vv]= 0;
    while (!queue.empty()) {
        size_t current = queue.front();
        queue.pop();

        if (d[current] > distance) break;

        for (const auto &n : gg.vertices[current].get_neighbour()) {
            if (!visited[n.first]) {
                queue.push(n.first);
                d[n.first] = d[current] + 1;
                visited[n.first] = true;
            }
        }
    }

    for (size_t i = 0; i < d.size(); i++) {
        if (d[i] <= distance) {
            fence.push_back(i);
        }
    }
}

void graph::graph_fence::color_fence(const string &col) {
    for (const auto &v : fence) {
        gg.vertices[v].set_color(col);
    }
}

size_t graph::graph_fence::count_stake() const {
    return fence.size();
}

size_t graph::graph_fence::get_stake(size_t i) const {
    if (i > fence.size() - 1) return -1;
    return fence[i];
}
