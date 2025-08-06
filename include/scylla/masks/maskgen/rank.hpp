#pragma once

#include <cstdint>

#include "scylla/bitboard.hpp"
#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/core/square.hpp"

namespace scy::maskgen {

[[nodiscard]] consteval std::array<Bitboard, 8> rankMasks() {
    std::array<Bitboard, 8> masks;

    std::size_t idx = 0;
    for (Rank r{1}; r <= Rank{8}; ++r) {
        Bitboard b;
        for (File f = File{'a'}; f <= File{'h'}; ++f) {
            b.set(Square{f, r});
        }

        masks[idx] = b;
        idx++;
    }

    return masks;
}

// what masks should we generate?

}  // namespace scy::maskgen
