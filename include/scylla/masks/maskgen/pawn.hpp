// include/scylla/masks/maskgen/pawn.hpp
#pragma once

#include <array>
#include <cstdint>

#include "scylla/bitboard.hpp"
#include "scylla/chessboard.hpp"  // for Color
#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/core/square.hpp"

namespace scy::maskgen {

// Generates attack masks for all pawns of the given color.
[[nodiscard]] consteval std::array<Bitboard, 64> pawnAttackMasks(Color color) {
    std::array<Bitboard, 64> masks{};

    // White pawns move "up" (higher ranks), Black pawns move "down" (lower
    // ranks)
    const std::int64_t dr = (color == Color::White) ? 1 : -1;

    for (Rank rank{1}; rank <= Rank{8}; ++rank) {
        for (File file{'a'}; file <= File{'h'}; ++file) {
            Square sq{file, rank};
            Bitboard bb;

            // Pawns attack (file - 1, rank + dr) and (file + 1, rank + dr)
            for (std::int64_t df : {-1, 1}) {
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
