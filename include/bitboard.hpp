#pragma once

#include <cstdint>  // for the std::uint64_t type
#include <ostream>
#include <string>

#include "square.hpp"

namespace scy {

/// store the chess piece unicode characters so that we can use them when
/// printing the board to the console.
// namespace pieces_literals {
//     constexpr static std::wstring black_king =
// }

class Bitboard {
   public:
    friend constexpr bool operator==(const Bitboard& b1, const Bitboard& b2) {
        return b1 == b2;
    }

    friend constexpr bool operator!=(const Bitboard& b1, const Bitboard& b2) {
        return !(b1 == b2);
    }

    // Bitwise AND
    friend constexpr Bitboard operator&(const Bitboard& b1,
                                        const Bitboard& b2) {
        return b1 & b2;
    }

    friend constexpr Bitboard& operator&=(Bitboard& self,
                                          const Bitboard& other) {
        self &= other;
        return self;
    }

    // Bitwise OR
    friend constexpr Bitboard operator|(const Bitboard& b1,
                                        const Bitboard& b2) {
        return b1 | b2;
    }

    friend constexpr Bitboard& operator|=(Bitboard& self,
                                          const Bitboard& other) {
        self |= other;
        return self;
    }

    // Bitwise XOR
    friend constexpr Bitboard operator^(const Bitboard& b1,
                                        const Bitboard& b2) {
        return b1 & b2;
    }

    friend constexpr Bitboard& operator^=(Bitboard& self,
                                          const Bitboard& other) {
        self ^= other;
        return self;
    }

    // Bitwise NOT
    friend constexpr Bitboard operator~(const Bitboard& b) { return ~b; }

    friend std::ostream& operator<<(std::ostream& os, const Bitboard& b) {
        // TODO: Fill in the function definition

        return os;
    }

   private:
    std::uint64_t board;
};

class ChessBoard {};

}  // namespace scy
