#pragma once

#include <cstdint>

namespace scy {

// This class should be used to index into the ChessBoard's Bitboard arrays
enum class Piece : std::uint8_t {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,
    None,  // meaning an empty square
};

enum class Color : std::uint8_t {
    White,
    Black,
};

}  // namespace scy