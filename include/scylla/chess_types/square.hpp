#pragma once

#include <array>
#include <cstddef>    // for the std::size_t type
#include <stdexcept>  // required for std::invalid_argument
#include <string>

#include "scylla/chess_types/file.hpp"
#include "scylla/chess_types/rank.hpp"
#include "scylla/chess_types/util.hpp"

namespace scy {

/// TODO: Figure out if using stdexcept errors is the best way to handle it.
class Square {   
   public:
    constexpr Square(File f, Rank r) noexcept : index(r.index() * 8 + f.index()) {}
    // Implicit conversions
    constexpr Square(const std::string& notation) : index(validate(notation)) {}
    constexpr Square(const char* notation) : Square(std::string{notation}) {}

    // std::size_t is already unsigned, so we don't need to check if it's
    // greater than 0 or not.
    constexpr Square(std::size_t idx)
        : index(idx < 64 ? idx : throw std::invalid_argument("Invalid index")) {
    }

    constexpr operator std::size_t() const noexcept {
        return index;
    }

    /// TODO: is this one needed?
    constexpr operator std::string() const {
        return {static_cast<char>('a' + (index % 8)),
                static_cast<char>('1' + (index / 8))};
    }

    // Decomposition
    constexpr File file() const noexcept {
        return File(index % 8);
    }

    constexpr Rank rank() const noexcept {
        return Rank(index / 8);
    }

    // Conversion
    /// TODO: keep this or not?
    // static constexpr Square from_algebraic(const char* str) {
    //     return Square(File::from_char(str[0]), Rank::from_char(str[1]));
    // }
    
    // constexpr std::array<char, 2> to_algebraic() const noexcept {
    //     return {file().to_char(), rank().to_char()};
    // }
    
    // constexpr std::uint8_t index() const noexcept { return index; }
    
    // Arithmetic
    constexpr Square offset(std::uint8_t files, std::uint8_t ranks) const {
        /// TODO: is this function really needed?
        return Square(
            static_cast<std::size_t>(index + files + 8 * ranks)
        );
    }
    
    // Comparison
    auto operator<=>(const Square&) const = default;

   private:
    constexpr static std::size_t validate(const std::string& notation) {
        if (notation.length() != 2) {
            throw std::invalid_argument("Invalid notation");
        }

        char file = util::tolower(notation[0]);
        char rank = notation[1];

        if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
            throw std::invalid_argument("Invalid square");
        }

        return (rank - '1') * 8 + (file - 'a');
    }

    std::size_t index;
};

}  // namespace scy

// User-defined literal operator
constexpr scy::Square operator""_sq(const char* str, std::size_t) {
    // this operator overload needs to be in the global namespace
    // because otherwise, it never gets included into the list of
    // user-defined literal operator overloads that the compiler
    // looks at.
    return scy::Square(std::string{str});
}
