// include/scylla/game.hpp
#pragma once

#include <cstdint>
#include <optional>

#include "scylla/chessboard.hpp"
#include "scylla/core/square.hpp"

namespace scy {

enum class MoveType : uint8_t {
    Normal,
    Capture,
    EnPassant,
    CastleKingside,
    CastleQueenside,
    Promotion,
    PromotionCapture
};

struct Move {
    Square m_from;
    Square m_to;
    MoveType m_type;
    std::optional<Piece> m_promotion_piece;
    std::optional<Piece> m_captured_piece;

    constexpr Move(Square from, Square to, MoveType type) noexcept
        : m_from{from},
          m_to{to},
          m_type{type},
          m_promotion_piece{std::nullopt},
          m_captured_piece{std::nullopt} {}

    constexpr Move(Square from, Square to, MoveType type,
                   std::optional<Piece> promotion_piece,
                   std::optional<Piece> captured_piece) noexcept
        : m_from{from},
          m_to{to},
          m_type{type},
          m_promotion_piece{promotion_piece},
          m_captured_piece{captured_piece} {}

    // Equality operators
    constexpr bool operator==(const Move& other) const noexcept {
        return m_from == other.m_from && m_to == other.m_to &&
               m_type == other.m_type &&
               m_promotion_piece == other.m_promotion_piece &&
               m_captured_piece == other.m_captured_piece;
    }

    constexpr bool operator!=(const Move& other) const noexcept {
        return !(*this == other);
    }

    // Utility functions
    constexpr bool is_capture() const noexcept {
        return m_type == MoveType::Capture ||
               m_type == MoveType::PromotionCapture ||
               m_type == MoveType::EnPassant;
    }

    constexpr bool is_promotion() const noexcept {
        return m_type == MoveType::Promotion ||
               m_type == MoveType::PromotionCapture;
    }

    constexpr bool is_castling() const noexcept {
        return m_type == MoveType::CastleKingside ||
               m_type == MoveType::CastleQueenside;
    }
};

// which side can castle, etc. encoded as bitflags.
class CastlingInfo {
   public:
    // Castling rights bit positions
    enum : std::uint8_t {
        WhiteKingside = 1 << 0,   // 0001
        WhiteQueenside = 1 << 1,  // 0010
        BlackKingside = 1 << 2,   // 0100
        BlackQueenside = 1 << 3   // 1000
    };

    constexpr CastlingInfo() noexcept : m_rights{0} {}

    // Initialize with all castling rights enabled
    constexpr static CastlingInfo all_rights() noexcept {
        return CastlingInfo(WhiteKingside | WhiteQueenside | BlackKingside |
                            BlackQueenside);
    }

    constexpr explicit CastlingInfo(std::uint8_t bits) noexcept
        : m_rights{bits} {}

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

    class GameHistory {
       public:
        constexpr GameHistory() = default;

        // Push new state and corresponding move
        constexpr void push(const GameState& state, const Move& move) {
            m_states.push_back(state);
            m_moves.push_back(move);
        }

        // Pop last state and move (ensure you check empty before calling)
        constexpr void pop() {
            if (!m_states.empty()) {
                m_states.pop_back();
            }

            if (!m_moves.empty()) {
                m_moves.pop_back();
            }
        }

        constexpr bool empty() const noexcept {
            return m_states.empty();
        }

        const GameState& last_state() const {
            return m_states.back();
        }

        const Move& last_move() const {
            return m_moves.back();
        }

        constexpr std::size_t size() const noexcept {
            return m_states.size();
        }

        // No default parameter here — caller must specify how many repetitions
        // to check for
        constexpr bool has_repeated(const GameState& state,
                                    std::size_t times) const {
            int count = 0;
            for (const auto& s : m_states) {
                if (s == state) {
                    ++count;
                    if (count >= times) {
                        return true;
                    }
                }
            }
            return false;
        }

        constexpr void clear() noexcept {
            m_states.clear();
            m_moves.clear();
        }

       private:
        std::vector<GameState> m_states;
        std::vector<Move> m_moves;
    };

    class Game {};

    class Zobrist {};

}  // namespace scy
