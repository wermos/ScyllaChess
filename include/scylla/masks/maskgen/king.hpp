// include/scylla/masks/maskgen/king.hpp
#pragma once

#include <array>
#include <cstdint>

#include "scylla/bitboard.hpp"
#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/core/square.hpp"

namespace scy::maskgen {

// Helper arrays for file/rank deltas
constexpr std::array<std::int64_t, 3> offsets = {-1, 0, 1};

[[nodiscard]] consteval std::array<Bitboard, 64> kingMasks() {
    std::array<Bitboard, 64> masks{};
    for (Rank rank{1}; rank <= Rank{8}; ++rank) {
        for (File file{'a'}; file <= File{'h'}; ++file) {
            Square sq{file, rank};
            Bitboard bb;

            for (std::int64_t dr = -1; dr <= 1; ++dr) {
                for (std::int64_t df = -1; df <= 1; ++df) {
                    if (df == 0 && dr == 0) {
                        continue;
                    }

                    if (auto maybe_dest = sq.offset(df, dr)) {
                        bb.set(*maybe_dest);
                    }
                }
            }

            masks[static_cast<std::size_t>(sq)] = bb;
        }
    }
    return masks;
}

}  // namespace scy::maskgen
