#pragma once

#include <array>
#include <bit>
#include <cstdint>  // for the std::uint64_t type
#include <ostream>
#include <string>

#include "scylla/chess_types/square.hpp"
#include "scylla/chess_types/file.hpp"
#include "scylla/chess_types/rank.hpp"

namespace scy {

/// store the chess piece unicode characters so that we can use them when
/// printing the board to the console.
// namespace pieces_literals {
//     constexpr static std::wstring black_king =
// }

// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
// | A8 | B8 | C8 | D8 | E8 | F8 | G8 | H8 |  | 56 | 57 | 58 | 59 | 60 | 61 | 62 | 63 |
// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
// | A7 | B7 | C7 | D7 | E7 | F7 | G7 | H7 |  | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 |
// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
// | A6 | B6 | C6 | D6 | E6 | F6 | G6 | H6 |  | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 |
// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
// | A5 | B5 | C5 | D5 | E5 | F5 | G5 | H5 |  | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
// | A4 | B4 | C4 | D4 | E4 | F4 | G4 | H4 |  | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 |
// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
// | A3 | B3 | C3 | D3 | E3 | F3 | G3 | H3 |  | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |
// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
// | A2 | B2 | C2 | D2 | E2 | F2 | G2 | H2 |  |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15 |
// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
// | A1 | B1 | C1 | D1 | E1 | F1 | G1 | H1 |  |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |
// +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
//
//
// https://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/rep.html
// a1 is the LSB, h8 is the MSB.
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

    constexpr void setFile() noexcept {

    }

    constexpr void unsetFile() noexcept {

    }

    constexpr void setRank() noexcept {

    }

    constexpr void unsetRank() noexcept {

    }

    // // Rank/File interaction
    // static constexpr std::array<Bitboard, 8> RANK_MASKS = []{
    //     std::array<Bitboard, 8> masks{};
    //     for(uint8_t r = 0; r < 8; ++r)
    //         masks[r] = Bitboard(0xFFULL << (8 * r));
    //     return masks;
    // }();
    
    // static constexpr std::array<Bitboard, 8> FILE_MASKS = []{
    //     std::array<Bitboard, 8> masks{};
    //     for(uint8_t f = 0; f < 8; ++f)
    //         masks[f] = Bitboard(0x0101010101010101ULL << f);
    //     return masks;
    // }();
    
    // constexpr Bitboard(Rank r) noexcept : 
    //     value(RANK_MASKS[r.index()].value) {}
    
    // constexpr Bitboard(File f) noexcept : 
    //     value(FILE_MASKS[f.index()].value) {}

    /// the above doesn't work, but it's a good idea nonetheless

    // // Shifts with file wrapping protection
    // constexpr Bitboard north() const noexcept { return Bitboard(value << 8); }
    // constexpr Bitboard south() const noexcept { return Bitboard(value >> 8); }
    // constexpr Bitboard east() const noexcept { 
    //     return Bitboard((value & ~FILE_MASKS[7].value) << 1); 
    // }
    // constexpr Bitboard west() const noexcept { 
    //     return Bitboard((value & ~FILE_MASKS[0].value) >> 1); 
    // }

    /// also good idea, should have all 8 directions

    constexpr std::size_t count() const noexcept {
        // we need to use a braced-init-list here because `std::popcount` actually
        // returns an `int`.
        return static_cast<std::size_t>(std::popcount(board));
    }

    // Bit scanning
    constexpr std::size_t lsb() const noexcept {
        // least significant bit
        // what is the index of the first non-zero bit (starting from the LSB, i.e. bit number 0.)

        // we need to use a braced-init-list here because `std::countr_zero` actually
        // returns an `int`.
        return static_cast<std::size_t>(std::countr_zero(board));
    }

    constexpr std::size_t msb() const noexcept {
        // most significant bit
        // what is the index of the last non-zero bit (starting from the MSB, i.e. bit number 63.)
        
        // we need to use a braced-init-list here because `std::countl_zero` actually
        // returns an `int`.
        return static_cast<std::size_t>(63 - std::countl_zero(board));
    }

    constexpr bool empty() const noexcept {
        return board == 0;
    }

    // is this bitboard and the other bitboard intersecting in any square?
    constexpr bool intersects(const Bitboard& other) const noexcept {
        return (board & other.board) != 0;
    }

    /// Operator overloads
    friend constexpr bool operator==(const Bitboard& b1, const Bitboard& b2) noexcept {
        return b1.board == b2.board;
    }

    friend constexpr bool operator!=(const Bitboard& b1, const Bitboard& b2) noexcept {
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
                                        const Bitboard& b2) noexcept {
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

}  // namespace scy
