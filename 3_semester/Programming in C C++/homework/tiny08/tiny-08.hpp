#pragma once

template <class T> T const& clamp(T const& value, T const& low, T const& high) {
    if (value < low) {
        return low;
    } else if (high < value) {
        return high;
    } else {
        return value;
    }
}

template <class T, class Compare> T const& clamp(T const& value, T const& low, T const& high, Compare cmp) {
    if (cmp(value, low)) {
        return low;
    } else if (cmp(high, value)) {
        return high;
    } else {
        return value;
    }
}