#include "telescope.hpp"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>

using namespace std;

pair<size_t, size_t> parse_matrix(istream& in) {
    pair<size_t, size_t> matrixSize = {0, 0};
    string line;

    while (!in.eof()) {
        getline(in, line);
        if (line.empty()) break; // throw invalid_argument("Empty line.") :)
        matrixSize.first++;

        size_t columnsCount = 0;
        bool isPrevDigit = false;

        for (auto const &ch : line) {
            if (isPrevDigit && !isdigit(ch)) {
                isPrevDigit = false;
                continue;
            } else if (!isPrevDigit && isdigit(ch)) {
                columnsCount++;
                isPrevDigit = true;
            }
        }

        if (matrixSize.second != 0 && matrixSize.second != columnsCount) {
            throw invalid_argument("Inconsistent columns count.");
        }

        matrixSize.second = columnsCount;
    }

    return matrixSize;
}

vector<int> parse_matrix(istream& in, const pair<size_t, size_t>& m_size) {
    vector<int> result = {};
    string line;

    size_t rowCount = 0;

    while (!in.eof()) {
        getline(in, line);
        if (line.empty()) break; // throw invalid_argument("Empty line.") :)
        rowCount++;

        size_t columnsCount = 0;
        string accString = "";
        bool isPrevDigit = false;

        for (auto const &ch : line) {
            if (isdigit(ch) || ch == '-') {
                if (isPrevDigit) {
                    accString += ch;
                } else {
                    accString = ch;
                    isPrevDigit = true;
                    columnsCount++;
                }
            } else {
                if (isPrevDigit) {
                    result.push_back(stoi(accString));
                    accString = "";
                    isPrevDigit = false;
                    continue;
                }
            }
        }

        result.push_back(stoi(accString)); // adding last elem of column

        if (columnsCount != m_size.second) {
            throw invalid_argument("Inconsistent columns count.");
        }
    }

    if (rowCount != m_size.first) {
        throw invalid_argument("Inconsistent columns count.");
    }

    return result;
}

void print_matrix(std::ostream& out, const std::pair<size_t, size_t>& m_size, const std::vector<int>& vec) {
    // first and last line ((maxElemLength + 2) * colCount) + colCount++
    if (int(vec.size()) == 0) {
        cout << "" << endl;
        return;
    }

    int sepLineSize = 0;
    int maxElemSize = 0;
    int colCount = int(m_size.second);

    for (int const &i : vec) {
        int length = int(to_string(i).length());
        if (length > maxElemSize) {
            maxElemSize = length;
        }
    }

    sepLineSize = ((maxElemSize + 2) * colCount) + colCount + 1;

    out.width(sepLineSize);
    out.fill('-');
    out << "" << endl;

    int index = 0;
    for (int const &i : vec) {
        char buffer[100];
        sprintf(buffer, " %*i ", maxElemSize, i);

        if ((index + 1) % colCount == 0) { // end of line
            out << "|" << buffer << "|" << endl;
        } else {
            out << "|" << buffer;
        }
        index++;
    }

    out.width(sepLineSize);
    out.fill('-');
    out << "" << endl;
}

vector<unsigned char> parse_stream(istream& in, const pair<size_t, size_t>& m_size) {
    vector<unsigned char> result = {};

    char ch;
    while (in.get(ch)) {
        result.push_back(ch);
    }

    if (result.size() != m_size.first * m_size.second) {
        throw invalid_argument("Inconsistent count.");
    }

    return result;
}

void rotate_down(const pair<size_t, size_t>& m_size, vector<unsigned char>& vec) {
    size_t elemStep = m_size.second;
    size_t size = vec.size();
    vector<unsigned char> copyVec = vec;

    size_t copyVecIndex = 0;
    for (const auto &i : copyVec) {
        size_t newIndex = (copyVecIndex + elemStep) % size;
        vec[newIndex] = i;
        copyVecIndex++;
    }
}

void rotate_down(const pair<size_t, size_t>& m_size, vector<unsigned char>& vec, int step) {
    if (m_size.first == 1) return;
    if (step < 0) {
        step = -step;
        step = int(m_size.first - (step % m_size.first));
    } else {
        step = int(step % m_size.first);
    }
    if (step == 0) return;

    size_t size = vec.size();
    size_t columnsCount = m_size.second;
    vector<unsigned char> copyVec = vec;

    size_t copyVecIndex = 0;
    for (const auto &i : copyVec) {
        vec[(copyVecIndex + (step * columnsCount)) % size] = i;
        copyVecIndex++;
    }
}

void rotate_right(const pair<size_t, size_t>& m_size, vector<unsigned char>& vec) {
    if (m_size.second == 1) return;

    size_t size = vec.size();
    vector<unsigned char> copyVec = vec;

    size_t copyVecIndex = 0;
    size_t currentColumn = 1;
    for (const auto &i : copyVec) {
        bool isLasColumn = currentColumn % m_size.second == 0;

        if (isLasColumn) {
            vec[copyVecIndex - (m_size.second - 1)] = i;
        } else {
            size_t newIndex = (copyVecIndex + 1) % size;
            vec[newIndex] = i;
        }

        copyVecIndex++;
        currentColumn = isLasColumn ? 1 : ++currentColumn;
    }
}

void rotate_right(const pair<size_t, size_t>& m_size, vector<unsigned char>& vec, int step) {
    if (m_size.second == 1) return;

    if (step < 0) {
        step = -step;
        step = int(m_size.second - (step % m_size.second));
    } else {
        step = int(step % m_size.second);
    }

    if (step == 0) return;

    vector<unsigned char> copyVec = vec;

    size_t currentColumn = 1;
    size_t currentLine = 1;
    for (const auto &i : copyVec) {
        bool isLasColumn = currentColumn % m_size.second == 0;

        size_t newCol = (currentColumn + step) % m_size.second;
        newCol = newCol == 0 ? m_size.second : newCol;
        size_t newIndex = (currentLine * m_size.second) - (m_size.second - newCol) - 1;

        vec[newIndex] = i;

        if (isLasColumn) {
            currentColumn = 1;
            currentLine++;
        } else {
            currentColumn++;
        }
    }
}

void swap_points(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, const Point& p1, const Point& p2) {
    if ((p1.x + 1) < 1 || (p1.x + 1) > m_size.second) throw invalid_argument("Out of matrix.");
    if ((p1.y + 1) < 1 || (p1.y + 1) > m_size.first) throw invalid_argument("Out of matrix.");
    if ((p2.x + 1) < 1 || (p2.x + 1) > m_size.second) throw invalid_argument("Out of matrix.");
    if ((p2.y + 1) < 1 || (p2.y + 1) > m_size.first) throw invalid_argument("Out of matrix.");

    size_t firstElemIndex = ((p1.y + 1) * m_size.second) - (m_size.second - p1.x);
    size_t secondElemIndex = ((p2.y + 1) * m_size.second) - (m_size.second - p2.x);

    unsigned char prev = vec[firstElemIndex];
    vec[firstElemIndex] = vec[secondElemIndex];
    vec[secondElemIndex] = prev;
}

void swap_points(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, const Point& p1, const Point& p2, const Point& delta) {
    // Out of matrix
    if (m_size.first < p1.y + delta.y || m_size.second < p1.x + delta.x) {
        throw invalid_argument("Out of matrix.");
    }
    if (m_size.first < p2.y + delta.y || m_size.second < p2.x + delta.x) {
        throw invalid_argument("Out of matrix.");
    }

    // Intersections
    // First Matrix Vertex
    pair<size_t, size_t> firstMatrixLeftTopVertexCoord = make_pair(p1.y + 1, p1.x + 1);
    pair<size_t, size_t> firstMatrixRightBottomVertexCoord = make_pair(p1.y + delta.y, p1.x + delta.x);

    vector<pair<size_t, size_t>> vertexes;
    vertexes.reserve(4);
    vertexes.emplace_back(p2.y + 1, p2.x + 1);
    vertexes.emplace_back(p2.y + 1, p2.x + delta.x);
    vertexes.emplace_back(p2.y + delta.y, p2.x + delta.x);
    vertexes.emplace_back(p2.y + delta.y, p2.x + 1);

    for (const auto &vertex : vertexes) {
        if (vertex.first >= firstMatrixLeftTopVertexCoord.first
            && vertex.first <= firstMatrixRightBottomVertexCoord.first
            && vertex.second >= firstMatrixLeftTopVertexCoord.second
            && vertex.second <= firstMatrixRightBottomVertexCoord.second) {
            throw invalid_argument("Intersection of two matrices.");
        }
    }

    size_t firstMatrixFirstElemIndex = ((p1.y + 1) * m_size.second) - (m_size.second - p1.x);
    size_t secondMatrixFirstElemIndex = ((p2.y + 1) * m_size.second) - (m_size.second - p2.x);
    size_t firstMatrixLastElemIndex = firstMatrixFirstElemIndex + (delta.x - 1) + m_size.second * (delta.y - 1);

    size_t currentInnerMatrixColumn = 1;
    size_t currentInnerMatrixLine = 1;
    size_t currentFirstMatrixElemIndex = firstMatrixFirstElemIndex;
    size_t currentSecondMatrixElemIndex = secondMatrixFirstElemIndex;
    while (true) {
        unsigned char prev = vec[currentFirstMatrixElemIndex];
        vec[currentFirstMatrixElemIndex] = vec[currentSecondMatrixElemIndex];
        vec[currentSecondMatrixElemIndex] = prev;

        if (currentFirstMatrixElemIndex == firstMatrixLastElemIndex) break;

        if (currentInnerMatrixColumn == delta.x) {
            currentFirstMatrixElemIndex = firstMatrixFirstElemIndex + m_size.second * currentInnerMatrixLine;
            currentSecondMatrixElemIndex = secondMatrixFirstElemIndex + m_size.second * currentInnerMatrixLine;
            currentInnerMatrixColumn = 1;
            currentInnerMatrixLine++;
            continue;
        }

        currentFirstMatrixElemIndex++;
        currentSecondMatrixElemIndex++;
        currentInnerMatrixColumn++;
    }
}

void decode_picture(const std::string& file, const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec) {
    string line;
    ifstream in(file);

    if (in.is_open())
    {
        while (getline(in, line))
        {
            char currentCommand = '_';
            vector<string> args = {};
            string acc = "";

            for (const auto &ch : line) {
                if (isalpha(ch)) {
                    currentCommand = ch;
                    continue;
                }

                if (currentCommand == '_') break;

                if (isdigit(ch) || ch == '-') {
                    acc += ch;
                } else if (!acc.empty()) {
                    args.push_back(acc);
                    acc = "";
                }
            }

            if (!acc.empty()) {
                args.push_back(acc);
            }

            if (currentCommand == 'l') {
                if (!args.empty()) {
                    rotate_right(m_size, vec, -stoi(args[0]));
                } else {
                    rotate_right(m_size, vec, -1);
                }
            } else if (currentCommand == 'r') {
                if (!args.empty()) {
                    rotate_right(m_size, vec, stoi(args[0]));
                } else {
                    rotate_right(m_size, vec);
                }
            } else if (currentCommand == 'd') {
                if (!args.empty()) {
                    rotate_down(m_size, vec, stoi(args[0]));
                } else {
                    rotate_down(m_size, vec);
                }
            } else if (currentCommand == 'u') {
                if (!args.empty()) {
                    rotate_down(m_size, vec, -stoi(args[0]));
                } else {
                    rotate_down(m_size, vec, -1);
                }
            } else if (currentCommand == 's') {
                if (args.size() == 4) {
                    swap_points(m_size, vec,
                                Point(stoull(args[0]), stoull(args[1])),
                                Point(stoull(args[2]), stoull(args[3])));
                } else {
                    swap_points(m_size, vec,
                                Point(stoull(args[0]), stoull(args[1])),
                                Point(stoull(args[2]), stoull(args[3])),
                                Point(stoull(args[4]), stoull(args[5])));
                }
            }
        }
    }
    in.close();
}