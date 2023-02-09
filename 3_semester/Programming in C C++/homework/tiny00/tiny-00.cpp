#include "tiny-00.hpp"
#include <iomanip>
#include <ostream>
#include <numeric>

using namespace std;

void write_stats(vector<double> const& data, ostream& out) {
    double first = *(data.begin());
    double min = first;
    double max = first;

    for (auto &elem : data) {
        if (min > elem) min = elem;
        if (max < elem) max = elem;
    }

    out.precision(2);
    out << fixed;

    out << "min: " << min << "\n";
    out << "max: " << max << "\n";
    out << "mean: " << accumulate(data.begin(), data.end(), 0.00) / double(data.size()) << "\n";
}
