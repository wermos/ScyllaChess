#pragma once

#include <cstddef>
#include <cstdint>

/// TODO: Should this be in the `scy::consts` namespace or just naked `scy`?
namespace scy::consts {

// Helper: Piece enumeration for [color][piece_type] to improve packing and
// indexing
inline constexpr std::size_t NUM_COLORS = 2;
inline constexpr std::size_t NUM_PIECE_TYPES = 6;

// Everything below is stuff we needed for Zobrist.
inline constexpr std::size_t NUM_PIECES =
    NUM_COLORS * NUM_PIECE_TYPES;  // 6 types * 2 colors

inline constexpr std::size_t NUM_FILES = 8;
inline constexpr std::size_t NUM_RANKS = 8;
inline constexpr std::size_t NUM_SQUARES = NUM_RANKS * NUM_FILES;

inline constexpr std::size_t NUM_CASTLING_RIGHTS = 4;  // WK, WQ, BK, BQ

}  // namespace scy::consts