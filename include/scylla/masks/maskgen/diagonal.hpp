// include/scylla/masks/maskgen/diagonal.hpp
#pragma once

#include <array>
#include <cstdint>

#include "scylla/bitboard.hpp"
#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/core/square.hpp"

namespace scy::maskgen {

// 15 diagonals: index 0 = (file - rank) = -7, ..., index 7 = (file - rank) = 0 (main), ..., 14 = +7
[[nodiscard]] consteval std::array<Bitboard, 15> diagonalMasks() {
    std::array<Bitboard, 15> masks{};

    for (File file = File{'a'}; file <= File{'h'}; ++file) {
        for (Rank rank{1}; rank <= Rank{8}; ++rank) {
            // Map (-7..+7) to (0..14)
            std::size_t diag_id = 7 + static_cast<std::size_t>(file) - static_cast<std::size_t>(rank);
            // Do the addition before the subtraction to ensure we never go negative
            
            masks[diag_id].set(Square{file, rank});
        }
    }

    return masks;
}

}  // namespace scy::maskgen
