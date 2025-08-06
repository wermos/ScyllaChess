// include/scylla/game.hpp
#pragma once

#include <cstdint>
#include <optional>

#include "scylla/core/square.hpp"
#include "scylla/chessboard.hpp"

namespace scy {

// which side can castle, etc. encoded as bitflags.
class CastlingInfo {
public:
    // Castling rights bit positions
    enum : std::uint8_t {
        WhiteKingside  = 1 << 0,  // 0001
        WhiteQueenside = 1 << 1,  // 0010
        BlackKingside  = 1 << 2,  // 0100
        BlackQueenside = 1 << 3   // 1000
    };

    constexpr CastlingInfo() noexcept : m_rights{0} {}

    // Initialize with all castling rights enabled
    constexpr static CastlingInfo all_rights() noexcept {
        return CastlingInfo(WhiteKingside | WhiteQueenside | BlackKingside | BlackQueenside);
    }

    constexpr explicit CastlingInfo(std::uint8_t bits) noexcept : m_rights{bits} {}

    // Check if castling right is available for color and side
    constexpr bool can_castle_kingside(bool is_white) const noexcept {
        if (is_white) {
            return (m_rights & WhiteKingside) != 0;
        } else {
            return (m_rights & BlackKingside) != 0;
        }
    }

    constexpr bool can_castle_queenside(bool is_white) const noexcept {
        if (is_white) {
            return (m_rights & WhiteQueenside) != 0;
        } else {
            return (m_rights & BlackQueenside) != 0;
        }
    }

    // Remove kingside castling right for color
    void remove_kingside(bool is_white) noexcept {
        if (is_white) {
            m_rights &= ~WhiteKingside;
        } else {
            m_rights &= ~BlackKingside;
        }
    }

    // Remove queenside castling right for color
    void remove_queenside(bool is_white) noexcept {
        if (is_white) {
            m_rights &= ~WhiteQueenside;
        } else {
            m_rights &= ~BlackQueenside;
        }
    }

    // Remove both castling rights for color
    void remove_all(bool is_white) noexcept {
        if (is_white) {
            m_rights &= ~(WhiteKingside | WhiteQueenside);
        } else {
            m_rights &= ~(BlackKingside | BlackQueenside);
        }
    }

    // Add kingside castling right for color
    void add_kingside(bool is_white) noexcept {
        if (is_white) {
            m_rights |= WhiteKingside;
        } else {
            m_rights |= BlackKingside;
        }
    }

    // Add queenside castling right for color
    void add_queenside(bool is_white) noexcept {
        if (is_white) {
            m_rights |= WhiteQueenside;
        } else {
            m_rights |= BlackQueenside;
        }
    }

    // // Get raw bitfield
    // constexpr std::uint8_t bits() const noexcept { return m_rights; }

    // // Set raw bitfield
    // void set_bits(std::uint8_t bits) noexcept { m_rights = bits; }

    // Utility operator overload to test equality (for testing/game history)
    constexpr bool operator==(const CastlingInfo& other) const noexcept {
        return m_rights == other.m_rights;
    }

    constexpr bool operator!=(const CastlingInfo& other) const noexcept {
        return !(*this == other);
    }

private:
    std::uint8_t m_rights;
};


class GameHistory {};

struct GameState {
    // Which side is to move next
    Color side_to_move;

    // Castling eligibility flags (bitfield: KQkq)
    CastlingInfo castling_rights;

    // If en passant is available, stores the target square; else std::nullopt
    // This is the en passant capture target square, i.e. the square behind the pawn that moved two steps.
    std::optional<Square> en_passant_sq;

    // Number of halfmoves since last capture or pawn advance (for 50-move rule)
    std::size_t halfmove_clock;

    // Fullmove number (starts at 1, increments after Black's move)
    std::size_t fullmove_number;

    // Zobrist hash key representing this exact position and flags (used for transposition and repetition checks)
    /// TODO: Actually implement this
    std::uint64_t zobristKey;

    constexpr GameState() noexcept
        : side_to_move(Color::White),
          castling_rights(CastlingInfo::all_rights()),
          en_passant_sq(std::nullopt),
          halfmove_clock(0),
          fullmove_number(1),
          zobristKey(0)
    {}

    // Equality operators
    constexpr bool operator==(const GameState& other) const noexcept {
        return side_to_move == other.side_to_move
            && castling_rights == other.castling_rights
            && en_passant_sq == other.en_passant_sq
            && halfmove_clock == other.halfmove_clock
            && fullmove_number == other.fullmove_number
            && zobristKey == other.zobristKey;
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

class Game {};

class Zobrist {};

}  // namespace scy
