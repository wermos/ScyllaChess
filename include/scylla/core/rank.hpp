#pragma once

#include <cstdint>
#include <stdexcept>

#include "scylla/util.hpp"

namespace scy {

class Rank {
   public:
    explicit constexpr Rank(std::uint8_t r)
        : rank((r >= 1 && r <= 8)
                   ? r - 1
                   : throw std::invalid_argument("Invalid rank")) {}

    /// TODO: these might not be needed
    explicit constexpr Rank(const std::string& notation)
        : rank(validate(notation)) {}

    explicit constexpr Rank(const char* notation)
        : Rank(std::string{notation}) {}

    // Predefined ranks
    // clang-format off
    static constexpr Rank First()   noexcept { return Rank(1); }
    static constexpr Rank Second()  noexcept { return Rank(2); }
    static constexpr Rank Third()   noexcept { return Rank(3); }
    static constexpr Rank Fourth()  noexcept { return Rank(4); }
    static constexpr Rank Fifth()   noexcept { return Rank(5); }
    static constexpr Rank Sixth()   noexcept { return Rank(6); }
    static constexpr Rank Seventh() noexcept { return Rank(7); }
    static constexpr Rank Eighth()  noexcept { return Rank(8); }
    // clang-format on

    /// having both std::uint8_t and std::size_t overloads causes ambiguity in
    /// the Bitboard constructor
    // constexpr operator std::uint8_t() const noexcept {
    //     return rank;
    // }

    // `std::size_t` is the "more proper" overload to have because this will
    // allow for indexing into the mask arrays, which is one of the intended
    // usecases.
    constexpr operator std::size_t() const noexcept {
        return rank;
    }

    // "Iterators"
    constexpr Rank& operator++() {
        rank = (rank + 1) % 8;
        return *this;
    }

    constexpr Rank operator++(int) {
        Rank temp = *this;
        ++(*this);
        return temp;
    }

    constexpr Rank& operator--() {
        rank = (rank - 1) % 8;
        return *this;
    }

    constexpr Rank operator--(int) {
        Rank temp = *this;
        --(*this);
        return temp;
    }
    
    // Comparison
    auto operator<=>(const Rank&) const = default;

   private:
    constexpr static std::size_t validate(const std::string& s) {
        if (s.length() != 1) {
            throw std::invalid_argument("Invalid rank");
        }

        char rank = s[0];

        if (rank < '1' || rank > '8') {
            throw std::invalid_argument("Invalid rank");
        }

        return rank - '1';
    }

    std::uint8_t rank;
    // internally stores 0-7,
    // takes user input between 1-8
};

}  // namespace scy
