#pragma once

#include <cstdint>

#include "scylla/bitboard.hpp"
#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/core/square.hpp"

namespace scy::maskgen {

[[nodiscard]] consteval std::array<Bitboard, 8> antiDiagonalMasks() {
    std::array<Bitboard, 8> masks;
    
    /// TODO: Fill this shit in
    
    return masks;
}

}  // namespace scy::maskgen
