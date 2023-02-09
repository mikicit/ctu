#pragma once

#include <memory>
#include <cfloat>

enum class generator_kind {
    random,
    mersenne,
    minstd
};

class numbers_generator {
private:
    double stats_min_generated_double{};
    double stats_max_generated_double{};
    size_t stats_doubles_generated = 0;
    int stats_min_generated_int{};
    int stats_max_generated_int{};
    size_t stats_ints_generated = 0;
    size_t stats_trues_generated = 0;
    size_t stats_falses_generated= 0;
    size_t stats_bools_generated = 0;

    virtual double random_double_impl() = 0;
    virtual int random_int_impl(int lower, int upper) = 0;
    virtual bool random_bool_impl() = 0;
public:
    static std::unique_ptr<numbers_generator> create_by_kind(generator_kind kind, size_t seed);

    double random_double() {
        stats_doubles_generated++;
        double result = random_double_impl();

        if (stats_min_generated_double == 0) {
            stats_min_generated_double = result;
        }

        if (stats_max_generated_double == 0) {
            stats_max_generated_double = result;
        }

        if (result < stats_min_generated_double) {
            stats_min_generated_double = result;
        }

        if (result > stats_max_generated_double) {
            stats_max_generated_double = result;
        }

        return result;
    };

    int random_int(int lower, int upper) {
        stats_ints_generated++;
        int result = random_int_impl(lower, upper);

        if (stats_min_generated_int == 0) {
            stats_min_generated_int = result;
        }

        if (stats_max_generated_int == 0) {
            stats_max_generated_int = result;
        }

        if (result < stats_min_generated_int) {
            stats_min_generated_int = result;
        }

        if (result > stats_max_generated_int) {
            stats_max_generated_int = result;
        }

        return result;
    };

    bool random_bool() {
        stats_bools_generated++;

        bool result = random_bool_impl();

        if (result) {
            stats_trues_generated++;
        } else {
            stats_falses_generated++;
        }

        return result;
    };

    double min_generated_double() const {
        return stats_min_generated_double;
    }
    double max_generated_double() const {
        return stats_max_generated_double;
    }
    size_t doubles_generated() const {
        return stats_doubles_generated;
    }
    int min_generated_int() const {
        return stats_min_generated_int;
    }
    int max_generated_int() const {
        return stats_max_generated_int;
    }
    size_t ints_generated() const {
        return stats_ints_generated;
    }
    size_t trues_generated() const {
        return stats_trues_generated;
    }
    size_t falses_generated() const {
        return stats_falses_generated;
    }
    size_t bools_generated() const {
        return stats_bools_generated;
    }

    virtual ~numbers_generator() = default;
};
