// include/scylla/masks/masks.hpp
#pragma once

#include <array>

#include "scylla/bitboard.hpp"
#include "scylla/masks/maskgen/file.hpp"
#include "scylla/masks/maskgen/rank.hpp"
#include "scylla/masks/maskgen/diagonal.hpp"
#include "scylla/masks/maskgen/antidiagonal.hpp"

namespace scy {
    
inline constexpr std::array<Bitboard, 8> rankMasks = maskgen::rankMasks();
inline constexpr std::array<Bitboard, 8> fileMasks = maskgen::fileMasks();

inline constexpr std::array<Bitboard, 15>  diagonalMasks = maskgen::diagonalMasks();
inline constexpr std::array<Bitboard, 15>  antiDiagonalMasks = maskgen::antiDiagonalMasks();

// inline constexpr std::array<Bitboard, 8> rookMasks =
// generateRookAttackMasks();

}  // namespace scy


// namespace scy::masks {
//     inline constexpr auto rankMasks = maskgen::rankMasks();
//     inline constexpr auto fileMasks = maskgen::fileMasks();
//     inline constexpr auto diagonalMasks = maskgen::diagonalMasks();
//     inline constexpr auto antiDiagonalMasks = maskgen::antiDiagonalMasks();

//     inline constexpr auto knightAttackMasks = maskgen::knightMasks();
//     inline constexpr auto kingAttackMasks = maskgen::kingMasks();

//     inline constexpr auto whitePawnAttackMasks = maskgen::pawnAttackMasks<Color::White>();
//     inline constexpr auto blackPawnAttackMasks = maskgen::pawnAttackMasks<Color::Black>();
// }

