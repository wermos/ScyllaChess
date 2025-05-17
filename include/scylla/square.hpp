#pragma once

#include <cctype>  // std::tolower
// TODO: see if this is needed and if tolower exists anywhere else.
#include <cstddef>    // for the std::size_t type
#include <stdexcept>  // required for std::invalid_argument
#include <string>

namespace scy {

// TODO: Figure out if using stdexcept errors is the best way to handle it.
class Square {
    constexpr static std::size_t validate(const std::string& notation) {
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

    constexpr operator std::string() const {
        return {static_cast<char>('a' + (index % 8)),
                static_cast<char>('1' + (index / 8))};
    }

   private:
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
