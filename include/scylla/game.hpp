#pragma once

#include <cstdint>
#include <optional>

#include "include/scylla/core/square.hpp"

namespace scy {

enum class Color {
    White,
    Black,
};

// which side can castle, etc. encoded as bitflags.
// we only need 4 bits.
struct CastlingInfo {};

class GameHistory {};

struct GameState {
    Color sideToMove;
    
    CastlingInfo castling;
    
    std::size_t numPlysPlayed:

    std::optional<Square> enPassantSquare;
    
    std::size_t moveNumber;
    std::uint64_t zobristKey;
};

class Game {};

class Zobrist {};

}
