#include "catch.hpp"

#include "telescope.hpp"
#include "test-helpers.hpp"

#include <string>
#include <sstream>
#include <chrono>

std::string gen_swap_points(const std::pair<size_t, size_t>& m_size, size_t& xxx, size_t& yyy) {
    Point a(0, 0), b(0, 0);
    a.x = random_int(0, static_cast<int>(m_size.second) - 1);
    a.y = random_int(0, static_cast<int>(m_size.first) - 1);
    std::pair<int, int> half = std::make_pair(m_size.first / 2, m_size.second / 2);
    size_t x1, x2, y1, y2;
    if (static_cast<int>(a.x) > half.second) {
        b.x = random_int(0, half.second);
        x2 = m_size.second - a.x;
        x1 = a.x - b.x;
    } else {
        b.x = random_int(half.second + 1, static_cast<int>(m_size.second) - 1);
        x2 = m_size.second - b.x;
        x1 = b.x - a.x;
    }
    if (static_cast<int>(a.y) > half.first) {
        b.y = random_int(0, half.first);
        y2 = m_size.first - a.y;
        y1 = a.y - b.y;
    } else {
        b.y = random_int(half.first + 1, static_cast<int>(m_size.first) - 1);
        y2 = m_size.first - b.y;
        y1 = b.y - a.y;
    }
    std::stringstream ss;
    ss << a.x << " " << a.y << " " << b.x << " " << b.y;
    xxx = 0; yyy = 0;
    if (x1 > x2) x1 = x2;
    if (y1 > y2) y1 = y2;
    if (x1 > 20 && y1 > 20 && random_int(0, 3) != 1) {
        xxx = random_int(10, static_cast<int>(x1));
        yyy = random_int(10, static_cast<int>(y1));
        ss << " " << xxx << " " << yyy;
    }
    return ss.str();
}

void code_generation04(const std::string& file, const std::pair<size_t, size_t>& m_size, int count = 100, bool is_decode = false) {
    std::ofstream f;
    f.open(file);
    std::stringstream ss, sss;
    std::vector<std::string> vec_decode;
    int num;
    for (int i = 0; i < count; ++i) {
        switch (random_int(0, 2)) {
            case 0 :
                if (random_bool()) {
                    num = random_int(-1'000, 1'000);
                    if (num < 0) {
                        ss << "l " << -num;
                        sss << "r " << -num;
                    } else {
                        ss << "r " << num;
                        sss << "l " << num;
                    }
                } else {
                    ss << "r";
                    sss << "l";
                }
                break;
            case 1 :
                if (random_bool()) {
                    num = random_int(-1'000, 1'000);
                    if (num < 0) {
                        ss << "u " << -num;
                        sss << "d " << -num;
                    } else {
                        ss << "d " << num;
                        sss << "u " << num;
                    }
                } else {
                    ss << "d";
                    sss << "u";
                }
                break;
            case 2 : {
                size_t xx, yy;
                ss << "s " << gen_swap_points(m_size, xx, yy);
                sss << ss.str();
                }
                break;
        }
        f << ss.str() << std::endl;
        if (is_decode) {
            sss << std::endl;
            auto it = vec_decode.begin();
            vec_decode.insert(it, sss.str());
        }
        ss.str("");
        sss.str("");
    }
    f.close();
    if (is_decode) {
        f.open("decode.txt");
        for (auto& v : vec_decode)
            f << v;
        f.close();
    }
}

TEST_CASE("Encoding and decoding with many different commands", "[stage4][.long]") {
    const int tests = 5;
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);
    static std::minstd_rand rng{ std::random_device{}() };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);

    SECTION("Encode + decode = original") {
        std::pair<size_t, size_t> dim;
        for (size_t i = 0; i < tests; ++i) {
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation04("code.txt", dim, (i + 1) * 100, true);
            decode_picture("code.txt", dim, temp);
            decode_picture("decode.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }
}
