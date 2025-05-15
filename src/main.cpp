#include <cstdint>
#include <iostream>

#include "bitboard.hpp"
#include "square.hpp"

using namespace scy;

int main() {
    Square e4 = "e4";           // From std::string
    Square d5 = 28;             // From integer index
    std::string notation = d5;  // To std::string
    int index = e4;             // To integral index

    // Literal syntax
    auto a1 = "a1"_sq;
    uint64_t board = 1ULL << static_cast<int>(a1);

    Bitboard myboard;
    std::cout << myboard << std::endl;

    auto d7 = "d7"_sq;
    uint64_t board2 = 1ULL << static_cast<int>(d7);
    Bitboard myboard2(board | board2);

    std::cout << myboard2 << std::endl;
}