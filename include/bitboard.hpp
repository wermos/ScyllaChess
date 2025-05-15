#pragma once

#include <cctype> // std::tolower
// TODO: see if this is needed and if tolower exists anywhere else.
#include <cstddef> // for the std::size_t type
#include <cstdint> // for the std::uint64_t type
#include <ostream>
#include <stdexcept>
#include <string>

namespace scy {

/// store the chess piece unicode characters so that we can use them when
/// printing the board to the console.
// namespace pieces_literals {
//     constexpr static std::wstring black_king =
// }

class Square {
    static std::size_t validate(const std::string& notation) {
        if (notation.length() != 2) {
            throw std::invalid_argument("Invalid notation");
        }

            char file = std::tolower(notation[0]);
            char rank = notation[1];
            if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
                throw std::invalid_argument("Invalid square");
            }

        return (rank - '1') * 8 + (file - 'a');
    }

   public:
    // Implicit conversions
    Square(const std::string& notation) : index(validate(notation)) {}
    Square(const char* notation) : Square(std::string{notation}) {}

    // std::size_t is already unsigned, so we don't need to check if it's
    // greater than 0 or not.
    Square(std::size_t idx)
        : index(idx < 64
                    ? idx
                    : throw std::invalid_argument("Invalid index")) {}

    operator std::size_t() const noexcept {
        return index;
    }

    operator std::string() const {
        return {static_cast<char>('a' + (index % 8)), static_cast<char>('1' + (index / 8))};
    }

    private:
    std::size_t index;
};

// User-defined literal operator
Square operator""_sq(const char* str, std::size_t) {
    return Square(std::string{str});
}

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
