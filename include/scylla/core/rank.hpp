// include/scylla/core/rank.hpp
#pragma once

#include <cstdint>
#include <libassert/assert.hpp>
#include <string_view>
#include <type_traits>

#include "scylla/util.hpp"

namespace scy {

class Rank {
   public:
    constexpr explicit Rank(std::uint8_t r) : m_rank{validate_uint8(r)} {}

    /// TODO: these might not be needed
    constexpr explicit Rank(std::string_view sv) : m_rank{validate(sv)} {}
    constexpr explicit Rank(const char* s) : Rank(std::string_view{s}) {}

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

    // `std::size_t` is the "more proper" overload to have (as opposed to a
    // `std::uint8_t` overload because this will allow for indexing into the
    // mask arrays, which is one of the intended usecases.
    constexpr operator std::size_t() const noexcept {
        return m_rank;
    }

    // "Iterators"
    constexpr Rank& operator++() {
        m_rank = (m_rank + 1) % 8;
        return *this;
    }

    constexpr Rank operator++(int) {
        Rank temp = *this;
        ++(*this);
        return temp;
    }

    constexpr Rank& operator--() {
        m_rank = (m_rank - 1) % 8;
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
    static constexpr std::uint8_t validate_uint8(std::uint8_t r) {
        // Runtime validation with libassert
        ASSERT(r >= 1 && r <= 8, "Invalid rank number:", r, "Expected: 1-8");
        return r - 1;
    }

    static constexpr std::uint8_t validate(std::string_view sv) {
        // Runtime validation with libassert rich diagnostics
        ASSERT(sv.size() == 1,
               "Rank notation length error. Expected: 1 character, got:",
               sv.size(), "characters in string:", sv);
        return validate_char(sv[0]);
    }

    static constexpr std::uint8_t validate_char(char c) {
        // Runtime validation with libassert
        ASSERT(c >= '1' && c <= '8', "Invalid rank character:", c,
               "Expected: '1'-'8'");
        return c - '1';
    }

    std::uint8_t m_rank;
    // internally stores 0-7,
    // takes user input between 1-8
};

}  // namespace scy
