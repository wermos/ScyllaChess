// include/scylla/game.hpp
#pragma once

#include <cstdint>
#include <optional>

#include "scylla/core/square.hpp"
#include "scylla/chessboard.hpp"

namespace scy {

// which side can castle, etc. encoded as bitflags.
// we only need 2 bits. But most people use 4 bits for some reason.
struct CastlingInfo {};

class GameHistory {};

struct GameState {
    Color side_to_move;
    
    // TODO: See if we can use some other thing for this bitflag
    std::uint8_t castling_rights; // 4 bits: KQkq

    std::optional<Square> en_passant_sq;
    
    std::size_t halfmove_clock;
    std::size_t fullmove_number;
    // std::uint64_t zobristKey;
};

class Game {};

class Zobrist {};

}  // namespace scy
