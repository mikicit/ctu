#include "test-helpers.hpp"

auto& get_rng() {
    static std::minstd_rand rng{ std::random_device{}() };
    return rng;
}

size_t random_size(size_t from, size_t to) {
    auto& rng = get_rng();
    return std::uniform_int_distribution<size_t>(from, to)(rng);
}

int random_int(int from, int to) {
    auto& rng = get_rng();
    return std::uniform_int_distribution<int>(from, to)(rng);
}

bool random_bool() {
    return random_int(0, 1) == 0;
}

std::ofstream open_result(const std::string& file, const std::pair<size_t, size_t>& m_size) {
    std::ofstream f(file, std::fstream::binary);
    f << "P6 " << m_size.second / 3 << " " << m_size.first << " 255 ";
    return f;
}

std::vector<unsigned char> open_file(const std::string& file, std::pair<size_t, size_t>& m_size) {
    std::ifstream f(file, std::fstream::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(f), {});
    buffer.erase(buffer.begin());
    buffer.erase(buffer.begin());
    buffer.erase(buffer.begin());
    size_t w = 0, h = 0;
    unsigned char c = buffer[0];
    while (c != ' ') {
        w = w * 10 + c - '0';
        buffer.erase(buffer.begin());
        c = buffer[0];
    }
    buffer.erase(buffer.begin());
    c = buffer[0];
    while (c != ' ') {
        h = h * 10 + c - '0';
        buffer.erase(buffer.begin());
        c = buffer[0];
    }
    buffer.erase(buffer.begin());
    buffer.erase(buffer.begin());
    buffer.erase(buffer.begin());
    buffer.erase(buffer.begin());
    buffer.erase(buffer.begin());
    m_size = std::make_pair(h, w * 3);
    return buffer;
}

bool valid_vector(const std::string& file, std::vector<unsigned char>& vec, std::pair<size_t, size_t>& dim) {
    auto tmp = open_file(file, dim);
    for (size_t i = 0; i < vec.size(); ++i)
        if (vec[i] != tmp[i])
            return false;
    return true;
}