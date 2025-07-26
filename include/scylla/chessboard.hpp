#pragma once

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
};

class ChessBoard {

    constexpr ChessBoard() {
        /// TODO: should the constructor make a new default-position chess board
        /// or should that be left to a `new()` function?
    }

   private:
    // white pieces
    std::array<Bitboard, 6> m_whitePieces;

    // black pieces
    std::array<Bitboard, 6> m_blackPieces;

    // all pieces
    Bitboard m_allWhitePieces;
    Bitboard m_allBlackPieces;
    Bitboard m_allPieces;
};

}  // namespace scy
