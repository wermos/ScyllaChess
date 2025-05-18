#pragma once

#include <bits>
#include <cstdint>  // for the std::uint64_t type
#include <ostream>
#include <string>

#include "scylla/square.hpp"

namespace scy {

/// store the chess piece unicode characters so that we can use them when
/// printing the board to the console.
// namespace pieces_literals {
//     constexpr static std::wstring black_king =
// }

class Bitboard {
   public:
    constexpr Bitboard() noexcept = default;
    constexpr explicit Bitboard(std::uint64_t num) noexcept : board{num} {}

    constexpr void set(Square sq) noexcept {
        board |= 1uz << static_cast<std::size_t>(sq);
    }

    constexpr void unset(Square sq) noexcept {
        board &= ~(1uz << static_cast<std::size_t>(sq));
    }

    constexpr std::size_t count() const noexcept {
        // we need to use a braced-init-list here because `std::popcount` actually
        // returns an `int`.
        return {std::popcount(bits)};
    }

    // Bit scanning
    constexpr std::size_t lsb() const noexcept {
        // we need to use a braced-init-list here because `std::countr_zero` actually
        // returns an `int`.
        return {std::countr_zero(bits)};
    }

    constexpr std::size_t msb() const noexcept {
        // we need to use a braced-init-list here because `std::countl_zero` actually
        // returns an `int`.
        return {63 - std::countl_zero(bits)};
    }

    constexpr bool empty() const noexcept {
        return board == 0;
    }

    // is this bitboard and the other bitboard intersecting in any square?
    constexpr bool intersects(const BitBoard& other) const noexcept {
        return (board & other.board) != 0;
    }

    /// Operator overloads
    friend constexpr bool operator==(const Bitboard& b1, const Bitboard& b2) noexcept {
        return b1.board == b2.board;
    }

    friend constexpr bool operator!=(const Bitboard& b1, const Bitboard& b2) noexcept{
        return !(b1 == b2);
    }

    // Bitwise AND
    friend constexpr Bitboard operator&(const Bitboard& b1,
                                        const Bitboard& b2) noexcept {
        return Bitboard{b1.board & b2.board};
    }

    friend constexpr Bitboard& operator&=(Bitboard& self,
                                          const Bitboard& other) noexcept {
        self.board &= other.board;
        return self;
    }

    // Bitwise OR
    friend constexpr Bitboard operator|(const Bitboard& b1,
                                        const Bitboard& b2) noexcept{
        return Bitboard{b1.board | b2.board};
    }

    friend constexpr Bitboard& operator|=(Bitboard& self,
                                          const Bitboard& other) noexcept {
        self.board |= other.board;
        return self;
    }

    // Bitwise XOR
    friend constexpr Bitboard operator^(const Bitboard& b1,
                                        const Bitboard& b2) noexcept {
        return Bitboard{b1.board & b2.board};
    }

    friend constexpr Bitboard& operator^=(Bitboard& self,
                                          const Bitboard& other) noexcept {
        self.board ^= other.board;
        return self;
    }

    // Bitwise NOT
    friend constexpr Bitboard operator~(const Bitboard& b) noexcept {
        return Bitboard{~b.board};
    }

    friend std::ostream& operator<<(std::ostream& os, const Bitboard& b) {
        // 1 = piece, 0 = empty square

        os << "    a b c d e f g h\n";
        os << "  +-----------------+\n";

        for (int rank = 7; rank >= 0; rank--) {
            os << rank + 1 << " | ";
            for (int file = 0; file <= 7; file++) {
                // rank * 8 + file gives the index of the square
                if (b.board & (1uz << (rank * 8 + file))) {
                    os << "1 ";
                } else {
                    os << "0 ";
                }
            }
            os << "| " << rank + 1;

            os << '\n';
        }
        os << "  +-----------------+\n";
        os << "    a b c d e f g h\n";
        return os;
    }

   private:
    std::uint64_t board{0};
};

// TODO: implement like this or use an std::array?
class ChessBoard {
   private:
    // white pieces
    Bitboard m_whiteKing;
    Bitboard m_whiteQueens;
    Bitboard m_whiteRooks;
    Bitboard m_whiteBishops;
    Bitboard m_whiteKnights;
    Bitboard m_whitePawns;

    // black pieces
    Bitboard m_blackKing;
    Bitboard m_blackQueens;
    Bitboard m_blackRooks;
    Bitboard m_blackBishops;
    Bitboard m_blackKnights;
    Bitboard m_blackPawns;

    // all pieces
    Bitboard m_allWhitePieces;
    Bitboard m_allBlackPieces;
    Bitboard m_allPieces;
};

}  // namespace scy
