#include "catch.hpp"

#include "telescope.hpp"
#include "test-helpers.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <chrono>

std::string gen_swap_points(const std::pair<size_t, size_t>& m_size) {
    Point a(0, 0), b(0, 0), c(0, 0);
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
    c.x = 0; c.y = 0;
    if (x1 > x2) x1 = x2;
    if (y1 > y2) y1 = y2;
    if (x1 > 20 && y1 > 20 && random_int(0, 3) != 1) {
        c.x = random_int(10, static_cast<int>(x1));
        c.y = random_int(10, static_cast<int>(y1));
        ss << " " << c.x << " " << c.y;
    }
    return ss.str();
}

void code_generation(const std::string& file, const std::pair<size_t, size_t>& m_size, int count = 100, bool is_decode = false) {
    std::ofstream f;
    f.open(file);
    std::stringstream ss, sss;
    std::vector<std::string> vec_decode;
    int num = 0;
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
            case 2 :
                ss << "s " << gen_swap_points(m_size);
                sss << ss.str();
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

void code_generation_simple(const std::string& file, const std::pair<size_t, size_t>& m_size, char operand, size_t count = 2, bool l_u = false) {
    std::ofstream f;
    f.open(file);
    if (operand == 'r' || operand == 'd') {
        std::vector<int> vec_num;
        int sum = 0;
        for (size_t i = 0; i < count - 1; ++i) {
            if (random_bool())
                vec_num.push_back(random_int(-1'000, 1'000));
            else
                vec_num.push_back(1);
            sum += vec_num[vec_num.size() - 1];
        }
        vec_num.push_back(-sum);
        for (size_t i = 0; i < count; ++i)
            if (vec_num[i] == 1)
                f << operand << std::endl;
            else
                if (l_u && vec_num[i] < 0) {
                        switch (operand) {
                            case 'r': f << "l" << " " << -vec_num[i] << std::endl; break;
                            case 'd': f << "u" << " " << -vec_num[i] << std::endl; break;
                        }
                } else
                    f << operand << " " << vec_num[i] << std::endl;
    } else if (operand == 's') {
        std::vector<std::string> vec_decode;
        for (size_t i = 0; i < count / 2; ++i) {
            std::string s = gen_swap_points(m_size);
            std::stringstream ss;
            ss << operand << " " << s << std::endl;
            f << ss.str();
            vec_decode.push_back(ss.str());
        }
        for (size_t i = vec_decode.size(); i > 0; --i)
            f << vec_decode[i - 1];
    }
    f.close();
}

void code_generation_simplest(const std::string& file, char operand) {
    std::ofstream f;
    f.open(file);
    switch (operand) {
        case 'r' :
            f << operand << std::endl;
            f << "l" << std::endl;
            break;
        case 'd' :
            f << operand << std::endl;
            f << "u" << std::endl;
            break;
        default : break;
    }
    f.close();
}

TEST_CASE("Decoding with one command", "[one_command]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);
    static std::minstd_rand rng{ std::random_device{}() };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
    const int tests = 10;

    SECTION("Easy rotate right") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'r');
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate down") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'd');
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate right and left") {
        // radek "r -1" je nahrazen radkem "l" - vlevo
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simplest("code.txt", 'r');
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate down and up") {
        // radek "d -1" je nahrazen radkem "u" - nahoru
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simplest("code.txt", 'd');
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy swap points") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 's');
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }
}

TEST_CASE("Decoding with one type command - 3", "[one_type_command]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);
    static std::minstd_rand rng{ std::random_device{}() };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
    const int tests = 10;

    SECTION("Easy rotate right - 3") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'r', 3);
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate right and left - 3") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'r', 3, true);
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate down - 3") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'd', 3);
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate down and up - 3") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'd', 3, true);
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy swap points - 2") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 's');
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }
}

TEST_CASE("Decoding with one type command - a lot of...", "[one_type_command][.long]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);
    static std::minstd_rand rng{ std::random_device{}() };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
    const int tests = 10;

    SECTION("Easy rotate right - a lof of...") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'r', random_int(4, 100));
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate right and left - a lof of...") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'r', random_int(4, 100), true);
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate down - a lof of...") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'd', random_int(4, 100));
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy rotate down and up - a lof of...") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 'd', random_int(4, 100), true);
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }

    SECTION("Easy swap points - a lof of...") {
        for (size_t i = 0; i < tests; ++i) {
            std::pair<size_t, size_t> dim;
            auto temp = open_file("../image/carina.ppm", dim);
            code_generation_simple("code.txt", dim, 's', random_int(4, 100));
            decode_picture("code.txt", dim, temp);
            REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
        }
    }
}

TEST_CASE("Decoding with many different commands", "[many_commands][.long]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("10 corrections") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/carina1.ppm", dim);
        decode_picture("../image/decode1.txt", dim, temp);
        std::ofstream ff = open_result("carina1.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
        REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
    }

    SECTION("50 corrections") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/carina2.ppm", dim);
        decode_picture("../image/decode2.txt", dim, temp);
        std::ofstream ff = open_result("carina2.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
        REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
    }

    SECTION("100 corrections") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/carina3.ppm", dim);
        decode_picture("../image/decode3.txt", dim, temp);
        std::ofstream ff = open_result("carina3.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
        REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
    }
    SECTION("1000 corrections") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/carina4.ppm", dim);
        decode_picture("../image/decode4.txt", dim, temp);
        std::ofstream ff = open_result("carina4.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
        REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
    }

    SECTION("2000 corrections") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/carina5.ppm", dim);
        decode_picture("../image/decode5.txt", dim, temp);
        std::ofstream ff = open_result("carina5.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
        REQUIRE(valid_vector("../image/carina.ppm", temp, dim));
    }

    SECTION("Quintet") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/quintet.ppm", dim);
        decode_picture("../image/decode_quintet.txt", dim, temp);
        std::ofstream ff = open_result("quintet.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }

    SECTION("smacs") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/smacs.ppm", dim);
        decode_picture("../image/decode_smacs.txt", dim, temp);
        std::ofstream ff = open_result("smacs0723.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }

    SECTION("Deaths Ring") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/dring.ppm", dim);
        decode_picture("../image/decode_ring.txt", dim, temp);
        std::ofstream ff = open_result("deathsring.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }

    SECTION("Carina small") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/carina_small.ppm", dim);
        decode_picture("../image/decode_carinas.txt", dim, temp);
        std::ofstream ff = open_result("carina_S.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }
}
/*
 * Generovani kodu a dekodovacich souboru.
 *
TEST_CASE("Decoding with many different ahoj commands", "[many_commands][.different]") {
//    const int tests = 100;
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);
    static std::minstd_rand rng{ std::random_device{}() };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);

    SECTION("10 corrections") {
        std::pair<size_t, size_t> dim;
        auto temp = open_file("../image/carina_s.ppm", dim);
        code_generation("code.txt", dim, 3000, true);
        decode_picture("code.txt", dim, temp);
        std::ofstream ff = open_result("carina_small.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
        decode_picture("decode.txt", dim, temp);
        ff = open_result("carina.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }
}
*/