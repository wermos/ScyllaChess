// include/scylla/masks/masks.hpp
#pragma once

#include <array>

#include "scylla/bitboard.hpp"
#include "scylla/maskgen.hpp"

namespace scy {
inline constexpr std::array<Bitboard, 8> rankMasks = maskgen::rankMasks();
inline constexpr std::array<Bitboard, 8> fileMasks = maskgen::fileMasks();

// inline constexpr std::array<Bitboard, 8> rookMasks =
// generateRookAttackMasks();

}  // namespace scy
