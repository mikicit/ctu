#pragma once

#include <random>
#include <fstream>

auto& get_rng();

size_t random_size(size_t from, size_t to);

int random_int(int from, int to);

bool random_bool();

char random_ws();

template<typename T>
bool valid_vectors(std::vector<T> vec1, std::vector<T> vec2, size_t count = 0, size_t first = 0) {
    if (count == 0 && vec1.size() != vec2.size())
        return false;
    if (count == 0)
        count = vec1.size();
    for (size_t i = 0; i < count; ++i)
        if (vec1[i + first] != vec2[i])
            return false;
    return true;
}

std::ofstream open_result(const std::string& file, const std::pair<size_t, size_t>& m_size);

std::vector<unsigned char> open_file(const std::string& file, std::pair<size_t, size_t>& m_size);

bool valid_vector(const std::string& file, std::vector<unsigned char>& vec, std::pair<size_t, size_t>& dim);