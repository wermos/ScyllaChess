// include/scylla/chessboard.hpp
#pragma once

#include <cstdint>

#include "scylla/bitboard.hpp"
#include "scylla/constants.hpp"
#include "scylla/core/types.hpp"

namespace scy {

using namespace scy::consts;

class ChessBoard {

    constexpr ChessBoard() {
        /// TODO: should the constructor make a new default-position chess board
        /// or should that be left to a `new()` function?
    }

   private:
    std::array<std::array<Bitboard, NUM_PIECE_TYPES>, NUM_COLORS> m_pieceOcc;
    std::array<Bitboard, NUM_COLORS> m_colorOcc;

    Bitboard m_occupancy;
};

}  // namespace scy
