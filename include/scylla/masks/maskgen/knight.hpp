// include/scylla/masks/maskgen/knight.hpp
#pragma once

#include <array>
#include <cstdint>

#include "scylla/bitboard.hpp"
#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/core/square.hpp"

namespace scy::maskgen {

// Generates knight attack masks for all squares on the board
[[nodiscard]] consteval std::array<Bitboard, 64> knightMasks() {
    std::array<Bitboard, 64> masks{};

    // Knight moves are eight possible jumps:
    // (±1 file, ±2 rank) and (±2 file, ±1 rank)
    constexpr std::int64_t knightOffsets[8][2] = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    for (Rank rank{1}; rank <= Rank{8}; ++rank) {
        for (File file{'a'}; file <= File{'h'}; ++file) {
            Square sq{file, rank};
            Bitboard bb;

            for (auto [df, dr] : knightOffsets) {
                if (auto maybe_dest = sq.offset(df, dr)) {
                    bb.set(*maybe_dest);
                }
            }

            masks[static_cast<std::size_t>(sq)] = bb;
        }
    }

    return masks;
}

}  // namespace scy::maskgen
