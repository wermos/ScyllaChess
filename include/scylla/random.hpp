// include/scylla/random.hpp
#pragma once

// PRNG Utilities
#include <random>

inline float randomFloat() {
    // Returns a random float in [0, 1].
    static std::uniform_real_distribution<float> distribution(
        0.0, std::nextafter(1.0, std::numeric_limits<float>::infinity()));

    static std::mt19937_64 generator;

    return distribution(generator);
}

inline float randomFloat(float min, float max) {
    // Returns a random float in [min, max].
    static std::uniform_real_distribution<float> distribution(
        min, std::nextafter(max, std::numeric_limits<float>::infinity()));

    static std::mt19937_64 generator;

    return distribution(generator);
}
