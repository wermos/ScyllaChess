#pragma once

#include <cstdint>
#include <optional>

#include "scylla/constants.hpp"
#include "scylla/core/square.hpp"

namespace scy {
    
enum class MoveType : std::uint8_t {
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

}
