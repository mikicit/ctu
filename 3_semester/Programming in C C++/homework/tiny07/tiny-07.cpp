#include "tiny-07.hpp"

#include <cstdint>

mersenne_twister_generator::mersenne_twister_generator(size_t seed):
    rng(seed)
{}

double mersenne_twister_generator::random_double() {
    return double_dist(rng);
}

int mersenne_twister_generator::random_int(int lower, int upper) {
    return uniform_int_distribution(lower, upper)(rng);
}

bool mersenne_twister_generator::random_bool() {
    return bool_dist(rng);
}

minstd_generator::minstd_generator(size_t seed):
    rng(static_cast<uint32_t>(seed))
{}

double minstd_generator::random_double() {
    return double_dist(rng);
}

int minstd_generator::random_int(int lower, int upper) {
    return uniform_int_distribution(lower, upper)(rng);
}

bool minstd_generator::random_bool() {
    return bool_dist(rng);
}

// numbers_generator
std::unique_ptr<numbers_generator> numbers_generator::clone() const {
    return std::unique_ptr<numbers_generator>(this->clone_impl());
}

// fixed_generator
std::unique_ptr<fixed_generator> fixed_generator::clone() const {
    return std::unique_ptr<fixed_generator>(this->clone_impl());
}

fixed_generator* fixed_generator::clone_impl() const {
    return new fixed_generator(*this);
}

// mersenne_twister_generator
std::unique_ptr<mersenne_twister_generator> mersenne_twister_generator::clone() const {
    return std::unique_ptr<mersenne_twister_generator>(this->clone_impl());
}

mersenne_twister_generator* mersenne_twister_generator::clone_impl() const {
    return new mersenne_twister_generator(*this);
}

// minstd_generator
std::unique_ptr<minstd_generator> minstd_generator::clone() const {
    return std::unique_ptr<minstd_generator>(this->clone_impl());
}

minstd_generator* minstd_generator::clone_impl() const {
    return new minstd_generator(*this);
}
