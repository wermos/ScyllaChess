#include <cstdint>
#include <iostream>

#include "scylla/bitboard.hpp"
#include "scylla/square.hpp"

using namespace scy;

int main() {
    Square e4 = "e4";           // From std::string
    Square d5 = 28;             // From integer index
    std::string notation = d5;  // To std::string
    int index = e4;             // To integral index

    // Literal syntax
    auto a1 = "a1"_sq;

    Bitboard board;
    std::cout << "Initial : " << std::endl;
    std::cout << board << std::endl;

    auto d7 = "d7"_sq;

    board.set(a1);
    board.set(d7);
    board.set(63);
    board.set("e6");
    board.set("c4"_sq);

    std::cout << "After setting some: " << std::endl;
    std::cout << board << std::endl;

    board.unset(d7);
    board.unset(63);
    board.unset("e6");
    board.unset("c4"_sq);
    board.unset("c8");  // Not set, should not change anything

    std::cout << "After unsetting some: " << std::endl;
    std::cout << board << std::endl;
}