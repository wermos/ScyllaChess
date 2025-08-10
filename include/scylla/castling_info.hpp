#pragma once

#include <cstdint>

namespace scy {

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

}  // namespace scy
