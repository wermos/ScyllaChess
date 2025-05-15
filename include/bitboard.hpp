#pragma once

#include <cstdint> // for the std::uint64_t type
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
    friend std::ostream& operator<<(std::ostream& os, char8_t const& ch) {

        return os;
    }

   private:
    std::uint64_t board;
};

class ChessBoard {};
}  // namespace scy
