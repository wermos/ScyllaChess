// src/main.cpp
#include <cstdint>
#include <iostream>

#include "scylla/bitboard.hpp"
#include "scylla/core/square.hpp"

using namespace scy;

int main() {
    Bitboard b;

    std::cout << "Initial state:\n" << b << std::endl;

    b.set("a1"_sq);
    std::cout << "After setting a1:\n" << b << std::endl;
    b.set("e4"_sq);
    std::cout << "After setting a1 and e4:\n" << b << std::endl;
    b.set(63);
    std::cout << "After setting a1, e4, and h8:\n" << b << std::endl;

    b.unset("e4"_sq);
    b.unset("a1"_sq);
    b.unset(63);

    std::cout << "After unsetting a1, e4, h8:\n" << b << std::endl;
}