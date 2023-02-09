#include "catch.hpp"

#include "telescope.hpp"
#include "test-helpers.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <limits>

struct generated_matrix {
    generated_matrix():width(random_size(5, 100)), height(random_size(5, 100)) {}


    std::stringstream create_stream(bool valid_stream = true) {
        size_t breaking_height = height;
        size_t breaking_width = width;
        if (!valid_stream) {
            // Select a row to cut short
            // -- the selection range is [from, to], but our range is [from, to)
            breaking_height = random_size(0, height - 1);
            // Make sure there is something in the row, and it isn't left full
            breaking_width = random_size(1, width - 2);
        }

        std::stringstream res;
        for (size_t h = 0; h < height; ++h) {
            for (size_t w = 0; w < width; ++w) {
                if (h == breaking_height &&
                    w == breaking_width) {
                    break;
                }
                if (w > 0) {
                    auto amount = random_size(1, 250);
                    for (size_t i = 0; i < amount; ++i) {
                        if (random_bool())
                            res << " ";
                        else
                            res << "\t";
                    }
                }
                int num = random_int(-1'000, 1'000);
                res << num;
                vec.push_back(num);
            }
            res << '\n';
        }
        return res;
    }
    size_t width;
    size_t height;
    std::vector<int> vec;
};

bool valid_vect(std::vector<int> vec1, std::vector<int> vec2) {
    if (vec1.size() != vec2.size())
        return false;
    for (size_t i = 0; i < vec1.size(); ++i)
        if (vec1[i] != vec2[i])
            return false;
    return true;
}

TEST_CASE("Parse matrix", "[parse_matrix]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular matrix") {
        std::string s =
R"f(1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
)f";
        str.str(s);
        auto temp = parse_matrix(str);
        REQUIRE(temp.first == 4);
        REQUIRE(temp.second == 4);
    }

    SECTION("Singular column matrix") {
        std::string s = "1\n2\n3\n4\n5\n6\n7\n";
        str.str(s);
        auto temp = parse_matrix(str);
        REQUIRE(temp.first == 7);
        REQUIRE(temp.second == 1);
    }

    SECTION("Singular row matrix") {
        std::string s = "-1 -2 -3 4 5 6 7\n";
        str.str(s);
        auto temp = parse_matrix(str);
        REQUIRE(temp.first == 1);
        REQUIRE(temp.second == 7);
    }

    SECTION("Wide matrix") {
        std::string s = R"f(1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8
)f";
        str.str(s);
        auto temp = parse_matrix(str);
        REQUIRE(temp.first == 3);
        REQUIRE(temp.second == 8);
    }

    SECTION("Empty string (no matrix)") {
        std::string s = "";
        str.str(s);
        auto temp = parse_matrix(str);
        REQUIRE(temp.first == 0);
        REQUIRE(temp.second == 0);
    }

    SECTION("String with single number") {
        std::string s = "11\n";
        str.str(s);
        auto temp = parse_matrix(str);
        REQUIRE(temp.first == 1);
        REQUIRE(temp.second == 1);
    }

    SECTION("Tall matrix") {
        std::string s = R"f(1 2 3
4 5 6
7 8 9
10 11 12
13 14 15
)f";
        str.str(s);
        auto temp = parse_matrix(str);
        REQUIRE(temp.first == 5);
        REQUIRE(temp.second == 3);
    }

    SECTION("Matrix with weird whitespace") {
        std::string s = R"f(1 2		3 4
5		6		7 8
9	10 12 13
13 14		15 33
16 17	22	11
)f";
        str.str(s);
        auto temp = parse_matrix(str);
        REQUIRE(temp.first == 5);
        REQUIRE(temp.second == 4);
    }

    SECTION("Matrix with rows that have different width") {
        std::string s = R"f(1 2 3 4
5 6 7
)f";
        str.str(s);
        REQUIRE_THROWS_AS(parse_matrix(str), std::invalid_argument);
    }

    SECTION("Matrix with middle row different") {
        std::string s = R"f(1 2 3 4
4 56 7 8
5 6 7
77 889 97 10
8 9 10 11
)f";
        str.str(s);
        REQUIRE_THROWS_AS(parse_matrix(str), std::invalid_argument);
    }
}

TEST_CASE("Parse matrix dimension", "[parse_matrix]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("Easy to parse rectangular matrix") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::string s =
                R"f(1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
)f";

        str.str(s);
        auto temp = parse_matrix(str, dim);
        REQUIRE(temp.size() == dim.first * dim.second);
        REQUIRE(valid_vect(temp, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }));
    }

    SECTION("Singular column matrix") {
        std::pair<size_t, size_t> dim = std::make_pair(7, 1);
        std::string s = "1\n2\n3\n4\n5\n6\n7\n";
        str.str(s);
        auto temp = parse_matrix(str, dim);
        REQUIRE(temp.size() == 7);
        REQUIRE(valid_vect(temp, { 1, 2, 3, 4, 5, 6, 7 }));
    }

    SECTION("Singular row matrix") {
        std::pair<size_t, size_t> dim = std::make_pair(1, 7);
        std::string s = "-1 -2 -3 4 5 6 -7\n";
        str.str(s);
        auto temp = parse_matrix(str, dim);
        REQUIRE(temp.size() == 7);
        REQUIRE(valid_vect(temp, { -1, -2, -3, 4, 5, 6, -7 }));
    }


    SECTION("Wide matrix") {
        std::pair<size_t, size_t> dim = std::make_pair(3, 8);
        std::string s = R"f(1 2 3 4 5 6 7 8
11 22 33 44 55 66 77 88
111 222 333 444 555 666 777 888
)f";

        str.str(s);
        auto temp = parse_matrix(str, dim);
        REQUIRE(temp.size() == dim.first * dim.second);
        REQUIRE(valid_vect(temp, { 1, 2, 3, 4, 5, 6, 7, 8, 11, 22, 33, 44, 55, 66, 77, 88, 111, 222, 333, 444, 555, 666, 777, 888 }));
    }

    SECTION("Empty string (no matrix)") {
        std::pair<size_t, size_t> dim = std::make_pair(0, 0);
        std::string s = "";
        str.str(s);
        auto temp = parse_matrix(str, dim);
        REQUIRE(temp.empty());
        REQUIRE(valid_vect(temp, { }));
    }

    SECTION("String with single number") {
        std::pair<size_t, size_t> dim = std::make_pair(1, 1);
        std::string s = "11\n";
        str.str(s);
        auto temp = parse_matrix(str, dim);
        REQUIRE(temp.size() == 1);
        REQUIRE(valid_vect(temp, { 11 }));
    }

    SECTION("Tall matrix") {
        std::pair<size_t, size_t> dim = std::make_pair(5, 3);
        std::string s = R"f(1 2 3
4 5 6
7 8 9
10 11 12
13 14 15
)f";
        str.str(s);
        auto temp = parse_matrix(str, dim);
        REQUIRE(temp.size() == dim.first * dim.second);
        REQUIRE(valid_vect(temp, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }));
    }

    SECTION("Matrix with weird whitespace") {
        std::pair<size_t, size_t> dim = std::make_pair(5, 4);
        std::string s = R"f(1 2		3 4
5		6		7 8
9	10 12 13
13 14		15 33
16 17	22	11
)f";
        str.str(s);
        auto temp = parse_matrix(str, dim);
        REQUIRE(temp.size() == dim.first * dim.second);
        REQUIRE(valid_vect(temp, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 13, 14, 15, 33, 16, 17, 22, 11 }));
    }

    SECTION("Matrix with rows that have different width") {
        std::pair<size_t, size_t> dim = std::make_pair(2, 3);
        std::string s = R"f(1 2 3 4
5 6 7
)f";
        str.str(s);
        REQUIRE_THROWS_AS(parse_matrix(str, dim), std::invalid_argument);
    }

    SECTION("Matrix with rows that have different width 2") {
        std::pair<size_t, size_t> dim = std::make_pair(2, 3);
        std::string s = R"f(1 2 3
5 6 7 8
)f";
        str.str(s);
        REQUIRE_THROWS_AS(parse_matrix(str, dim), std::invalid_argument);
    }

    SECTION("Matrix with middle row different") {
        std::pair<size_t, size_t> dim = std::make_pair(5, 4);
        std::string s = R"f(1 2 3 4
4 56 7 8
5 6 7
77 889 97 10
8 9 10 11
)f";
        str.str(s);
        REQUIRE_THROWS_AS(parse_matrix(str, dim), std::invalid_argument);
    }

    SECTION("Randomly generated matrices") {
        const int tests = 10;
        SECTION("Valid") {
            for (int i = 0; i < tests; ++i) {
                generated_matrix m;
                auto str = m.create_stream();
                std::pair<size_t, size_t> dim = std::make_pair(m.height, m.width);
                auto temp = parse_matrix(str, dim);
                REQUIRE(temp.size() == dim.first * dim.second);
                REQUIRE(valid_vect(temp, m.vec));
            }
        }
        SECTION("Invalid") {
            for (int i = 0; i < tests; ++i) {
                generated_matrix m;
                auto str = m.create_stream(false);
                std::pair<size_t, size_t> dim = std::make_pair(m.height, m.width);
                REQUIRE_THROWS_AS(parse_matrix(str, dim), std::invalid_argument);
            }
        }
    }

    SECTION("Autogenerated") {
        const int tests = 10;
        SECTION("Valid") {
            for (int i = 0; i < tests; ++i) {
                generated_matrix m;
                auto str = m.create_stream();
                auto temp = parse_matrix(str);
                REQUIRE(temp.first == m.height);
                REQUIRE(temp.second == m.width);
            }
        }
        SECTION("Invalid") {
            for (int i = 0; i < tests; ++i) {
                generated_matrix m;
                auto str = m.create_stream(false);
                REQUIRE_THROWS_AS(parse_matrix(str), std::invalid_argument);
            }
        }
    }
}

TEST_CASE("Print matrix", "[print_matrix]") {
    std::stringstream str;
    str.exceptions(std::ios_base::badbit);

    SECTION("input 1") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        std::string exp =
                R"f(---------------------
|  1 |  2 |  3 |  4 |
|  5 |  6 |  7 |  8 |
|  9 | 10 | 11 | 12 |
| 13 | 14 | 15 | 16 |
---------------------
)f";

        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("input 1") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::vector<int> vec = {-1, -2, -3, -4, -5, -6, -7, -8, -9, 10, 11, 12, 13, 14, 15, 16};
        std::string exp =
                R"f(---------------------
| -1 | -2 | -3 | -4 |
| -5 | -6 | -7 | -8 |
| -9 | 10 | 11 | 12 |
| 13 | 14 | 15 | 16 |
---------------------
)f";

        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("input 1") {
        std::pair<size_t, size_t> dim = std::make_pair(4, 4);
        std::vector<int> vec = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, 12, 13, 14, 15, 16};
        std::string exp =
                R"f(-------------------------
|  -1 |  -2 |  -3 |  -4 |
|  -5 |  -6 |  -7 |  -8 |
|  -9 | -10 | -11 |  12 |
|  13 |  14 |  15 |  16 |
-------------------------
)f";

        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("Wide matrix") {
        std::pair<size_t, size_t> dim = std::make_pair(3, 8);
        std::vector<int> vec = {1, -2, 3, -4, 5, -6, 7, -8, 11, -22, 33, -44, 55, -66, 77, -88, -111, 222, -333, 444,
                                -555, 666, -777, 888};
        std::string exp =
                R"f(---------------------------------------------------------
|    1 |   -2 |    3 |   -4 |    5 |   -6 |    7 |   -8 |
|   11 |  -22 |   33 |  -44 |   55 |  -66 |   77 |  -88 |
| -111 |  222 | -333 |  444 | -555 |  666 | -777 |  888 |
---------------------------------------------------------
)f";

        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("Empty string (no matrix)") {
        std::pair<size_t, size_t> dim = std::make_pair(0, 0);
        std::vector<int> vec = {};
        std::string exp = R"f()f";
        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("String with single number") {
        std::pair<size_t, size_t> dim = std::make_pair(1, 1);
        std::vector<int> vec = { 17 };
        std::string exp =
                R"f(------
| 17 |
------
)f";
        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("String with single negative number") {
        std::pair<size_t, size_t> dim = std::make_pair(1, 1);
        std::vector<int> vec = { -17 };
        std::string exp =
                R"f(-------
| -17 |
-------
)f";
        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("Tall matrix") {
        std::pair<size_t, size_t> dim = std::make_pair(6, 3);
        std::vector<int> vec = { 1'456, 2'789, -389, 4, 5, 6, 7, 8, 9, 10, 11, 125, -1'123, 1'400, 15, 20, 15'123, -456 };
        std::string exp =
                R"f(-------------------------
|  1456 |  2789 |  -389 |
|     4 |     5 |     6 |
|     7 |     8 |     9 |
|    10 |    11 |   125 |
| -1123 |  1400 |    15 |
|    20 | 15123 |  -456 |
-------------------------
)f";
        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("Big number") {
        std::pair<size_t, size_t> dim = std::make_pair(2, 3);
        std::vector<int> vec = { 12, 56, 1'123'456'789, 45, 18, 1'000 };
        std::string exp =
                R"f(----------------------------------------
|         12 |         56 | 1123456789 |
|         45 |         18 |       1000 |
----------------------------------------
)f";
        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

    SECTION("Big negative number") {
        std::pair<size_t, size_t> dim = std::make_pair(2, 3);
        std::vector<int> vec = { 12, -2'123'456'789, 1'987'654'321, 1'555'666'777, -1'159'753, -1'121 };
        std::string exp =
                R"f(-------------------------------------------
|          12 | -2123456789 |  1987654321 |
|  1555666777 |    -1159753 |       -1121 |
-------------------------------------------
)f";
        print_matrix(str, dim, vec);
        REQUIRE(str.str() == exp);
    }

}