// include/scylla/core/square.hpp
#pragma once

#include <array>
#include <cstdint>
#include <libassert/assert.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>

#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/util.hpp"

namespace scy {

class Square {
   public:
    constexpr Square(File f, Rank r) noexcept : m_index(8 * r + f) {}

    // String-based constructors
    constexpr Square(std::string_view notation) : m_index(validate(notation)) {}
    constexpr Square(const char* notation)
        : Square(std::string_view{notation}) {}

    // Index-based constructor
    constexpr Square(std::size_t idx) : m_index(validate_index(idx)) {}

    constexpr operator std::size_t() const noexcept {
        return m_index;
    }

    /// TODO: This is tested for and everything, but is this actually needed?
    constexpr operator std::string() const {
        return {static_cast<char>('a' + (m_index % 8)),
                static_cast<char>('1' + (m_index / 8))};
    }

    // Decomposition
    constexpr File file() const noexcept {
        return File(static_cast<char>('a' + (m_index % 8)));
    }

    constexpr Rank rank() const noexcept {
        return Rank(static_cast<std::uint8_t>((m_index / 8) + 1));
    }

    // Arithmetic
    constexpr std::optional<Square> offset(std::int64_t df,
                                           std::int64_t dr) const noexcept {
        auto maybe_file = file().offset(df);
        auto maybe_rank = rank().offset(dr);
        if (maybe_file && maybe_rank) {
            return Square(*maybe_file, *maybe_rank);
        }
        return std::nullopt;
    }

    // Comparison
    auto operator<=>(const Square&) const = default;

   private:
    static constexpr std::size_t validate_index(std::size_t idx) {
        // Runtime validation with libassert
        ASSERT(idx < 64, "Invalid square index:", idx, "Expected: 0-63");
        return idx;
    }

    static constexpr std::size_t validate(std::string_view notation) {
        // Runtime validation with libassert rich diagnostics
        ASSERT(notation.size() == 2,
               "Square notation length error. Expected: 2 characters, got:",
               notation.size(), "characters in string:", notation);
        return validate_notation_chars(notation[0], notation[1]);
    }

    static constexpr std::size_t validate_notation_chars(char file_char,
                                                         char rank_char) {
        // Runtime validation with libassert
        char file = util::tolower(file_char);
        ASSERT(file >= 'a' && file <= 'h', "Invalid file character:", file_char,
               "Lowercased:", file, "Expected: 'a'-'h'");
        ASSERT(rank_char >= '1' && rank_char <= '8',
               "Invalid rank character:", rank_char, "Expected: '1'-'8'");
        return (rank_char - '1') * 8 + (file - 'a');
    }

    std::size_t m_index;
};

}  // namespace scy

// User-defined literal operator
constexpr scy::Square operator""_sq(const char* str, std::size_t) {
    // this operator overload needs to be in the global namespace
    // because otherwise, it never gets included into the list of
    // user-defined literal operator overloads that the compiler
    // looks at.
    return scy::Square(std::string_view{str});
}
