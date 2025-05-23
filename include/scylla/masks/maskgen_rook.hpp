#pragma once

#include <array>
#include <cstdint>

namespace scy::maskgen {

/// TODO: should the parameters be const T& or const T? Does it matter?
[[nodiscard]] consteval std::array<Bitboard, 64> rookATKMasks(
    const std::array<Bitboard, 8> rankMasks,
    const std::array<Bitboard, 8> fileMasks) {
    // having the rank and file masks available makes the code much simpler

    std::array<Bitboard, 64> masks;

    for (File f = File{'a'}; f <= File{'h'}; ++f) {
        for (Rank r{1}; r <= Rank{8}; ++r) {
            // the square the rook is already on gets a 0. For example, if you
            // had a rook on a1, the relevant occupancy bits will be from a2-a7
            // and b1-g1.

            // this functionally works out to taking the XOR between the rank and the file the rook is on.
            const Square sq{f, r};
            const Bitboard file{fileMasks[f]}, rank{rankMasks[r]};

            masks[sq] = file ^ rank;
        }
    }
}

[[nodiscard]] consteval std::array<Bitboard, 64> rookATKMasks() {
    return rookATKMasks(rankMasks(), fileMasks());
}

}
