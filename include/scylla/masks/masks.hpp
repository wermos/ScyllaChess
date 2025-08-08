// include/scylla/masks/masks.hpp
#pragma once

#include <array>

#include "scylla/bitboard.hpp"
#include "scylla/masks/maskgen/antidiagonal.hpp"
#include "scylla/masks/maskgen/diagonal.hpp"
#include "scylla/masks/maskgen/file.hpp"
#include "scylla/masks/maskgen/king.hpp"
#include "scylla/masks/maskgen/knight.hpp"
#include "scylla/masks/maskgen/pawn.hpp"
#include "scylla/masks/maskgen/rank.hpp"

namespace scy {

inline constexpr std::array<Bitboard, 8> rankMasks = maskgen::rankMasks();
inline constexpr std::array<Bitboard, 8> fileMasks = maskgen::fileMasks();

inline constexpr std::array<Bitboard, 15> diagonalMasks =
    maskgen::diagonalMasks();
inline constexpr std::array<Bitboard, 15> antiDiagonalMasks =
    maskgen::antiDiagonalMasks();

inline constexpr std::array<Bitboard, 64> kingMasks = maskgen::kingMasks();

inline constexpr std::array<Bitboard, 64> knightAttackMasks =
    maskgen::knightMasks();

inline constexpr std::array<Bitboard, 64> whitePawnAttackMasks =
    maskgen::pawnAttackMasks(Color::White);
inline constexpr std::array<Bitboard, 64> blackPawnAttackMasks =
    maskgen::pawnAttackMasks(Color::Black);

// inline constexpr std::array<Bitboard, 8> rookMasks =
// generateRookAttackMasks();

}  // namespace scy
