#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>

#include "scylla/castling_info.hpp"
#include "scylla/core/square.hpp"
#include "scylla/core/types.hpp"

namespace scy {

struct GameState {
    // Which side is to move next
    Color side_to_move;

    // Castling eligibility flags (bitfield: KQkq)
    CastlingInfo castling_rights;

    // If en passant is available, stores the target square; else std::nullopt
    // This is the en passant capture target square, i.e. the square behind the
    // pawn that moved two steps.
    std::optional<Square> en_passant_sq;

    // Number of halfmoves since last capture or pawn advance (for 50-move rule)
    std::size_t halfmove_clock;

    // Fullmove number (starts at 1, increments after Black's move)
    std::size_t fullmove_number;

    // Zobrist hash key representing this exact position and flags (used for
    // transposition and repetition checks)
    /// TODO: Actually implement this
    std::uint64_t zobristKey;

    constexpr GameState() noexcept
        : side_to_move(Color::White),
          castling_rights(CastlingInfo::all_rights()),
          en_passant_sq(std::nullopt),
          halfmove_clock(0),
          fullmove_number(1),
          zobristKey(0) {}

    // Equality operators
    constexpr bool operator==(const GameState& other) const noexcept {
        return side_to_move == other.side_to_move &&
               castling_rights == other.castling_rights &&
               en_passant_sq == other.en_passant_sq &&
               halfmove_clock == other.halfmove_clock &&
               fullmove_number == other.fullmove_number &&
               zobristKey == other.zobristKey;
    }

    constexpr bool operator!=(const GameState& other) const noexcept {
        return !(*this == other);
    }

    // Method to reset en passant square after a move that doesn't create one
    void clear_en_passant() noexcept {
        en_passant_sq = std::nullopt;
    }

    // Utility functions that might be helpful, for example:

    // Is castling allowed for a given color and side?
    constexpr bool can_castle_kingside(Color c) const noexcept {
        return castling_rights.can_castle_kingside(c == Color::White);
    }

    constexpr bool can_castle_queenside(Color c) const noexcept {
        return castling_rights.can_castle_queenside(c == Color::White);
    }

    // Increment fullmove number after Black moves
    constexpr void increment_fullmove() noexcept {
        if (side_to_move == Color::Black) {
            ++fullmove_number;
        }
    }

    // Switch side to move (White <-> Black)
    constexpr void toggle_side() noexcept {
        if (side_to_move == Color::White) {
            side_to_move = Color::Black;
        } else {
            side_to_move = Color::White;
        }
    };
}
