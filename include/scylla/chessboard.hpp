#pragma once

#include <cstdint>
#include "scylla/bitboard.hpp"

namespace scy {

// This class should be used to index into the ChessBoard's Bitboard arrays
enum class Piece : std::uint8_t {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
    None, // meaning an empty square
};

enum class Color : std::uint8_t {
    White,
    Black,
};

// Helper: Piece enumeration for [color][piece_type] to improve packing and indexing
inline constexpr std::size_t NUM_COLORS = 2;
inline constexpr std::size_t NUM_TYPES = 6;

class ChessBoard {

    constexpr ChessBoard() {
        /// TODO: should the constructor make a new default-position chess board
        /// or should that be left to a `new()` function?
    }

   private:
    std::array<std::array<Bitboard, NUM_TYPES>, NUM_COLORS> m_pieceOcc;
    std::array<Bitboard, NUM_COLORS> m_colorOcc;

    Bitboard m_occupancy;
};

}  // namespace scy
