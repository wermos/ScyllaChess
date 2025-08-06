// include/scylla/masks/maskgen/antidiagonal.hpp
#pragma once

#include <array>
#include <cstdint>

#include "scylla/bitboard.hpp"
#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/core/square.hpp"

namespace scy::maskgen {

// 15 anti-diagonals: index 0 = (file + rank) = 2, ..., index 14 = 16
[[nodiscard]] consteval std::array<Bitboard, 15> antiDiagonalMasks() {
    std::array<Bitboard, 15> masks{};

    for (File file = File{'a'}; file <= File{'h'}; ++file) {
        for (Rank rank{1}; rank <= Rank{8}; ++rank) {
            // Map (2..16) to (0..14)
            std::size_t adiag_id = static_cast<std::size_t>(file) + static_cast<std::size_t>(rank) - 2;

            masks[adiag_id].set(Square{file, rank});
        }
    }

    return masks;
}

}  // namespace scy::maskgen
