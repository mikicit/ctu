#include "catch.hpp"

#include "telescope.hpp"
#include "test-helpers.hpp"

#include <string>
#include <sstream>
#include <iostream>

std::ifstream open_files(const std::string file, std::pair<size_t, size_t>& m_size) {
    std::ifstream f;
    f.open(file);
    unsigned char c;
    f >> std::noskipws >> c;
    f >> std::noskipws >> c;
    f >> std::noskipws >> c;
    f >> std::noskipws >> c;
    size_t w = 0, h = 0;
    while (c != ' ') {
        w = w * 10 + c - '0';
        f >> std::noskipws >> c;
    }
    f >> std::noskipws >> c;
    while (c != ' ') {
        h = h * 10 + c - '0';
        f >> std::noskipws >> c;
    }
    f >> std::noskipws >> c;
    f >> std::noskipws >> c;
    f >> std::noskipws >> c;
    f >> std::noskipws >> c;
    m_size = std::make_pair(h, w * 3);
    return f;
}

TEST_CASE("Parse stream", "[parse_stream]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        REQUIRE(valid_vectors(temp, { 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j'}));
    }

    SECTION("Wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 16);
        std::string s = "Byl pozdni vecerprvni maj       vecerni maj     byl lasky cas   ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        REQUIRE(valid_vectors(temp, { 'B', 'y', 'l', ' ', 'p', 'o', 'z', 'd', 'n', 'i', ' ', 'v', 'e', 'c', 'e', 'r',
                                      'p', 'r', 'v', 'n', 'i', ' ', 'm', 'a', 'j', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 32));
    }

    SECTION("Long wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(15, 31);
        std::string s = "Okolo lesa pole lan            hoj jede, jede z lesa pan      na vranem bujnem jede koni     vesele podkovicky zvoni        jede sam a sam.                A pred chalupou s kone hop!    a na chalupu: klop, klop, klop!'Hola hej! otevrte mi dvere,   zbloudil jsem pri loveni zvere,dejte vody pit!'               Vysla divcina jako kvet,       nevidel take krasy svet;       prinesla vody ze studnice,     stydlive sedla u preslice,     predla, predla len.            ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        REQUIRE(valid_vectors(temp, { 'V', 'y', 's', 'l', 'a', ' ', 'd', 'i', 'v', 'c', 'i', 'n', 'a', ' ', 'j', 'a', 'k',
                                      'o', ' ', 'k', 'v', 'e', 't', ',', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 31, 310));
    }

    SECTION("String with rows that have different width") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 16);
        std::string s = "Byl pozdni vecerprvni maj       vecerni maj     byl lasky cas ";
        str.str(s);
        REQUIRE_THROWS_AS(parse_stream(str, dim), std::invalid_argument);
    }

    SECTION("PPM red file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec.ppm", dim);
        auto temp = parse_stream(f, dim);
        f.close();
        // cerveny ctverecek rozmeru 5x5 pixelu
        REQUIRE(valid_vectors(temp, { 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
                                      255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
                                      255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
                                      255, 0, 0}));
    }

    SECTION("PPM colour file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec1.ppm", dim);
        auto temp = parse_stream(f, dim);
        f.close();
        REQUIRE(valid_vectors(temp, { 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255,
                                      0, 0, 255, 0, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 0, 0, 255, 0, 0, 255, 0, 255, 0, 0,
                                      0, 0, 255, 0, 255, 0, 255, 255, 0, 255, 255, 0, 255, 0, 0, 0, 0, 255, 0, 255, 0, 255, 255, 0,
                                      255, 255, 0}));
    }
}

TEST_CASE("Rotate down", "[rotate_down]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(3, 4);
        std::string s = "aaaabbbbcccc";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp);
        REQUIRE(valid_vectors(temp, {'c', 'c', 'c', 'c', 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b'}));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp);
        REQUIRE(valid_vectors(temp, { 'a', 'H', 'o', 'j', 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp);
        rotate_down(dim, temp);
        REQUIRE(valid_vectors(temp, { 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j', 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        for (size_t i = 0; i < dim.first; ++i)
            rotate_down(dim, temp);
        REQUIRE(valid_vectors(temp, { 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j'}));
    }

    SECTION("Wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 16);
        std::string s = "Byl pozdni vecerprvni maj       vecerni maj     byl lasky cas   ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp);
        REQUIRE(valid_vectors(temp, { 'b', 'y', 'l', ' ', 'l', 'a', 's', 'k', 'y', ' ', 'c', 'a', 's', ' ', ' ', ' ',
                                      'B', 'y', 'l', ' ', 'p', 'o', 'z', 'd', 'n', 'i', ' ', 'v', 'e', 'c', 'e', 'r',
                                      'p', 'r', 'v', 'n', 'i', ' ', 'm', 'a', 'j', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 48, 0));
    }
}

TEST_CASE("Rotate down with step", "[rotate_down]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp, 1);
        REQUIRE(valid_vectors(temp, { 'a', 'H', 'o', 'j', 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp, 2);
        REQUIRE(valid_vectors(temp, { 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j', 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp, 4);
        REQUIRE(valid_vectors(temp, { 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp, -1);
        REQUIRE(valid_vectors(temp, { 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j', 'A', 'h', 'o', 'j' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp, -3);
        REQUIRE(valid_vectors(temp, { 'a', 'H', 'o', 'j', 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp, 15);
        REQUIRE(valid_vectors(temp, { 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j', 'A', 'h', 'o', 'j' }));
    }

    SECTION("Wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 16);
        std::string s = "Byl pozdni vecerprvni maj       vecerni maj     byl lasky cas   ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp, 789);
        REQUIRE(valid_vectors(temp, { 'B', 'y', 'l', ' ', 'p', 'o', 'z', 'd', 'n', 'i', ' ', 'v', 'e', 'c', 'e', 'r',
                                      'p', 'r', 'v', 'n', 'i', ' ', 'm', 'a', 'j', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 32, 16));
    }

    SECTION("Long wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(15, 31);
        std::string s = "Okolo lesa pole lan            hoj jede, jede z lesa pan      na vranem bujnem jede koni     vesele podkovicky zvoni        jede sam a sam.                A pred chalupou s kone hop!    a na chalupu: klop, klop, klop!'Hola hej! otevrte mi dvere,   zbloudil jsem pri loveni zvere,dejte vody pit!'               Vysla divcina jako kvet,       nevidel take krasy svet;       prinesla vody ze studnice,     stydlive sedla u preslice,     predla, predla len.            ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_down(dim, temp, -789);
        REQUIRE(valid_vectors(temp, { 'V', 'y', 's', 'l', 'a', ' ', 'd', 'i', 'v', 'c', 'i', 'n', 'a', ' ', 'j', 'a', 'k',
                                      'o', ' ', 'k', 'v', 'e', 't', ',', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 31, 31));
    }


    SECTION("PPM red file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec1.ppm", dim);
        auto temp = parse_stream(f, dim);
        rotate_down(dim, temp, 1);
        f.close();
        REQUIRE(valid_vectors(temp, { 255, 0, 0, 0, 0, 255, 0, 255, 0, 255, 255, 0, 255, 255, 0, 255, 0, 0, 255, 0, 0,
                                      255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
                                      255, 255, 0, 0, 0, 0, 255, 0, 255, 0, 0, 255, 0, 0, 255, 0, 255, 0, 0, 0, 0, 255,
                                      0, 255, 0, 255, 255, 0, 255, 255, 0 }));
        std::ofstream ff = open_result("result3.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }

    SECTION("PPM red file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec1.ppm", dim);
        auto temp = parse_stream(f, dim);
        rotate_down(dim, temp, -1);
        f.close();
        REQUIRE(valid_vectors(temp, { 255, 0, 0, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 255, 0, 0, 0, 0, 255,
                                      0, 255, 0, 0, 255, 0, 0, 255, 0, 255, 0, 0, 0, 0, 255, 0, 255, 0, 255, 255, 0,
                                      255, 255, 0, 255, 0, 0, 0, 0, 255, 0, 255, 0, 255, 255, 0, 255, 255, 0, 255, 0, 0,
                                      255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0 }));
        std::ofstream ff = open_result("result4.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }
}

TEST_CASE("Rotate right", "[rotate_right]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(3, 4);
        std::string s = "abcdabcdabcd";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp);
        REQUIRE(valid_vectors(temp, {'d', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c'}));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp);
        REQUIRE(valid_vectors(temp, { 'j', 'A', 'h', 'o', 'J', 'A', 'H', 'O', 'j', 'a', 'h', 'o', 'j', 'a', 'H', 'o' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp);
        rotate_right(dim, temp);
        REQUIRE(valid_vectors(temp, { 'o', 'j', 'A', 'h', 'O', 'J', 'A', 'H', 'o', 'j', 'a', 'h', 'o', 'j', 'a', 'H' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        for (size_t i = 0; i < dim.second; ++i)
            rotate_right(dim, temp);
        REQUIRE(valid_vectors(temp, { 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j'}));
    }

    SECTION("Wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 16);
        std::string s = "Byl pozdni vecerprvni maj       vecerni maj     byl lasky cas   ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp);
        REQUIRE(valid_vectors(temp, { ' ', 'p', 'r', 'v', 'n', 'i', ' ', 'm', 'a', 'j', ' ', ' ', ' ', ' ', ' ', ' ',
                                      ' ', 'v', 'e', 'c', 'e', 'r', 'n', 'i', ' ', 'm', 'a', 'j', ' ', ' ', ' ', ' ' }, 32, 16));
    }
}

TEST_CASE("Rotate right with step", "[rotate_right]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, 1);
        REQUIRE(valid_vectors(temp, { 'j', 'A', 'h', 'o', 'J', 'A', 'H', 'O', 'j', 'a', 'h', 'o', 'j', 'a', 'H', 'o' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, 2);
        REQUIRE(valid_vectors(temp, { 'o', 'j', 'A', 'h', 'O', 'J', 'A', 'H', 'o', 'j', 'a', 'h', 'o', 'j', 'a', 'H' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, 4);
        REQUIRE(valid_vectors(temp, { 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j'}));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, 15);
        REQUIRE(valid_vectors(temp, { 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'A', 'h', 'o', 'j', 'a', 'H', 'o', 'j', 'a' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, -1);
        REQUIRE(valid_vectors(temp, { 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'A', 'h', 'o', 'j', 'a', 'H', 'o', 'j', 'a' }));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, -3);
        REQUIRE(valid_vectors(temp, { 'j', 'A', 'h', 'o', 'J', 'A', 'H', 'O', 'j', 'a', 'h', 'o', 'j', 'a', 'H', 'o' }));
    }

    SECTION("Wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 16);
        std::string s = "Byl pozdni vecerprvni maj       vecerni maj     byl lasky cas   ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, 789);
        REQUIRE(valid_vectors(temp, { ' ', ' ', ' ', ' ', ' ', 'v', 'e', 'c', 'e', 'r', 'n', 'i', ' ', 'm', 'a', 'j',
                                      'a', 's', ' ', ' ', ' ', 'b', 'y', 'l', ' ', 'l', 'a', 's', 'k', 'y', ' ', 'c' }, 32, 32));
    }

    SECTION("Wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 16);
        std::string s = "Byl pozdni vecerprvni maj       vecerni maj     byl lasky cas   ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, -789);
        REQUIRE(valid_vectors(temp, { 'n', 'i', ' ', 'm', 'a', 'j', ' ', ' ', ' ', ' ', ' ', 'v', 'e', 'c', 'e', 'r',
                                      'a', 's', 'k', 'y', ' ', 'c', 'a', 's', ' ', ' ', ' ', 'b', 'y', 'l', ' ', 'l' }, 32, 32));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        rotate_right(dim, temp, 7);
        rotate_right(dim, temp, -7);
        REQUIRE(valid_vectors(temp, { 'A', 'h', 'o', 'j', 'A', 'H', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'o', 'j'}));
    }

    SECTION("PPM red file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec.ppm", dim);
        auto temp = parse_stream(f, dim);
        rotate_right(dim, temp, 1);
        f.close();
        // cerveny ctverecek se promeni v zeleny ctverec rozmeru 5x5 bodu
        REQUIRE(valid_vectors(temp, { 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0,
                                      0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0,
                                      0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0,
                                      0, 255, 0}));
        std::ofstream ff = open_result("result0.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }

    SECTION("PPM red file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec.ppm", dim);
        auto temp = parse_stream(f, dim);
        rotate_right(dim, temp, -1);
        f.close();
        // cerveny ctverecek se promeni v modry ctverec rozmeru 5x5 bodu
        REQUIRE(valid_vectors(temp, { 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255,
                                      0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255,
                                      0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255,
                                      0, 0, 255}));
        std::ofstream ff = open_result("result1.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }
    SECTION("PPM red file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec.ppm", dim);
        auto temp = parse_stream(f, dim);
        rotate_right(dim, temp, 54);
        rotate_right(dim, temp, -54);
        f.close();
        // cerveny ctverecek zustane cervenym ctvereckem
        REQUIRE(valid_vectors(temp, { 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
                                      255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
                                      255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
                                      255, 0, 0}));
        std::ofstream ff = open_result("result2.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }
}

TEST_CASE("Swap of points", "[swap_points]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        swap_points(dim, temp, Point(1, 1), Point(2, 3));
        REQUIRE(valid_vectors(temp, { 'A', 'h', 'o', 'j', 'A', 'o', 'O', 'J', 'a', 'h', 'o', 'j', 'a', 'H', 'H', 'j'}));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        REQUIRE_THROWS_AS(swap_points(dim, temp, Point(1, 1), Point(4, 3)), std::invalid_argument);
        REQUIRE_THROWS_AS(swap_points(dim, temp, Point(-10, 1), Point(3, 3)), std::invalid_argument);
        REQUIRE_THROWS_AS(swap_points(dim, temp, Point(1, 1), Point(3, -3)), std::invalid_argument);
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        swap_points(dim, temp, Point(1, 1), Point(2, 3));
        swap_points(dim, temp, Point(1, 0), Point(0, 3));
        swap_points(dim, temp, Point(1, 2), Point(3, 3));
        swap_points(dim, temp, Point(2, 2), Point(3, 0));
        swap_points(dim, temp, Point(3, 0), Point(0, 1));
        swap_points(dim, temp, Point(2, 0), Point(0, 2));
        swap_points(dim, temp, Point(3, 1), Point(0, 2));
        REQUIRE(valid_vectors(temp, { 'A', 'a', 'a', 'A', 'o', 'o', 'O', 'o', 'J', 'j', 'j', 'j', 'h', 'H', 'H', 'h'}));
    }

}

TEST_CASE("Swap points with rectangle", "[swap_points]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(3, 4);
        std::string s = "bbaabbaaaaaa";
        str.str(s);
        auto temp = parse_stream(str, dim);
        swap_points(dim, temp, Point(0, 0), Point(2, 1), Point(2, 2));
        REQUIRE(valid_vectors(temp, {'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b', 'a', 'a', 'b', 'b'}));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        swap_points(dim, temp, Point(1, 0), Point(2, 2), Point(2, 2));
        REQUIRE(valid_vectors(temp, { 'A', 'o', 'j', 'j', 'A', 'o', 'j', 'J', 'a', 'h', 'h', 'o', 'a', 'H', 'H', 'O'}));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        swap_points(dim, temp, Point(2, 0), Point(1, 2), Point(2, 1));
        REQUIRE(valid_vectors(temp, { 'A', 'h', 'h', 'o', 'A', 'H', 'O', 'J', 'a', 'o', 'j', 'j', 'a', 'H', 'o', 'j'}));
    }

    SECTION("Easy to parse rectangular string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s = "AhojAHOJahojaHoj";
        str.str(s);
        auto temp = parse_stream(str, dim);
        REQUIRE_THROWS_AS(swap_points(dim, temp, Point(1, 1), Point(2, 2), Point(2, 2)), std::invalid_argument);
        REQUIRE_THROWS_AS(swap_points(dim, temp, Point(2, 2), Point(1, 1), Point(2, 2)), std::invalid_argument);
        REQUIRE_THROWS_AS(swap_points(dim, temp, Point(2, 0), Point(1, 1), Point(2, 2)), std::invalid_argument);
        REQUIRE_THROWS_AS(swap_points(dim, temp, Point(1, 1), Point(2, 0), Point(2, 2)), std::invalid_argument);
    }

    SECTION("Wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 16);
        std::string s = "Byl pozdni vecerprvni maj       vecerni maj     byl lasky cas   ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        swap_points(dim, temp, Point(4, 0), Point(4, 3), Point(6, 1));
        REQUIRE(valid_vectors(temp, { 'B', 'y', 'l', ' ', 'l', 'a', 's', 'k', 'y', ' ', ' ', 'v', 'e', 'c', 'e', 'r'}, 16, 0));
        REQUIRE(valid_vectors(temp, { 'b', 'y', 'l', ' ', 'p', 'o', 'z', 'd', 'n', 'i', 'c', 'a', 's', ' ', ' ', ' '}, 16, 48));
    }

    SECTION("Long wide string") {
        std::pair<size_t, size_t> dim = std::make_pair(15, 31);
        std::string s = "Okolo lesa pole lan            hoj jede, jede z lesa pan      na vranem bujnem jede koni     vesele podkovicky zvoni        jede sam a sam.                A pred chalupou s kone hop!    a na chalupu: klop, klop, klop!'Hola hej! otevrte mi dvere,   zbloudil jsem pri loveni zvere,dejte vody pit!'               Vysla divcina jako kvet,       nevidel take krasy svet;       prinesla vody ze studnice,     stydlive sedla u preslice,     predla, predla len.            ";
        str.str(s);
        auto temp = parse_stream(str, dim);
        swap_points(dim, temp, Point(0, 10), Point(0, 5), Point(31, 5));
        REQUIRE(valid_vectors(temp, { 'V', 'y', 's', 'l', 'a', ' ', 'd', 'i', 'v', 'c', 'i', 'n', 'a', ' ', 'j', 'a', 'k',
                                      'o', ' ', 'k', 'v', 'e', 't', ',', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 31, 155));
    }

    SECTION("PPM red file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec1.ppm", dim);
        auto temp = parse_stream(f, dim);
        swap_points(dim, temp, Point(3 * 3, 3), Point(0 * 3, 1), Point(2 * 3, 2));
        f.close();
        REQUIRE(valid_vectors(temp, { 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 255, 0, 255, 255, 0, 0, 0, 255,
                                      0, 0, 255, 0, 0, 255, 255, 255, 0, 255, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 255, 0, 0,
                                      0, 0, 255, 0, 255, 0, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 0, 255, 0, 0,
                                      0, 0, 255}));
        std::ofstream ff = open_result("result5.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }

    SECTION("PPM red file") {
        std::pair<size_t, size_t> dim;
        std::ifstream f = open_files("../image/Ctverec1.ppm", dim);
        auto temp = parse_stream(f, dim);
        swap_points(dim, temp, Point(0 * 3, 0), Point(3 * 3, 1), Point(2 * 3, 4));
        f.close();
        REQUIRE(valid_vectors(temp, { 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255,
                                      255, 0, 0, 255, 0, 0, 255, 255, 0, 255, 255, 0, 0, 255, 0, 255, 0, 0, 0, 0, 255, 255, 255, 0,
                                      255, 255, 0, 0, 255, 0, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 0, 255, 0, 255, 0, 0,
                                      0, 0, 255}));
        std::ofstream ff = open_result("result6.ppm", dim);
        for (size_t i = 0; i < temp.size(); ++i)
            ff << temp[i];
        ff.close();
    }
}