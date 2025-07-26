#pragma once

#include <libassert/assert.hpp>
#include <string_view>
#include <type_traits>

#include "scylla/util.hpp"

namespace scy {

class File {
   public:
    constexpr explicit File(char c) : m_file{validate_char(c)} {}

    /// TODO: these might not be needed
    constexpr explicit File(std::string_view sv) : m_file{validate(sv)} {}
    constexpr explicit File(const char* s) : File(std::string_view{s}) {}

    // Predefined files
    // clang-format off
    static constexpr File A() noexcept { return File('a'); }
    static constexpr File B() noexcept { return File('b'); }
    static constexpr File C() noexcept { return File('c'); }
    static constexpr File D() noexcept { return File('d'); }
    static constexpr File E() noexcept { return File('e'); }
    static constexpr File F() noexcept { return File('f'); }
    static constexpr File G() noexcept { return File('g'); }
    static constexpr File H() noexcept { return File('h'); }
    // clang-format on

    /// having both std::uint8_t and std::size_t overloads causes ambiguity in
    /// the Bitboard constructor
    // constexpr operator std::uint8_t() const noexcept {
    //     return file;
    // }

    // `std::size_t` is the "more proper" overload to have because this will
    // allow for indexing into the mask arrays, which is one of the intended
    // usecases.
    constexpr operator std::size_t() const noexcept {
        return m_file;
    }

    // "Iterators"
    constexpr File& operator++() {
        m_file = (m_file + 1) % 8;
        return *this;
    }

    constexpr File operator++(int) {
        File temp = *this;
        ++(*this);
        return temp;
    }

    constexpr File& operator--() {
        m_file = (m_file - 1) % 8;
        return *this;
    }

    constexpr File operator--(int) {
        File temp = *this;
        --(*this);
        return temp;
    }

    // Comparison
    auto operator<=>(const File&) const = default;

   private:
    // static constexpr std::uint8_t validate_char(const char c) {
    //     if (std::is_constant_evaluated()) {
    //         // Compile-time validation with static_assert
    //         char file = util::tolower(c);
    //         static_assert('a' <= c && c <= 'h',
    //                      "File must be in range 'a'-'h'");
    //         return file - 'a';
    //     } else {
    //         // Runtime validation with libassert
    //         char file = util::tolower(c);
    //         ASSERT(file >= 'a' && file <= 'h',
    //                "Invalid file character:", c, "Expected: 'a'-'h', got:",
    //                file);
    //         return file - 'a';
    //     }
    // }
    // static constexpr std::uint8_t validate(std::string_view sv) {
    //     if (std::is_constant_evaluated()) {
    //         // Compile-time validation
    //         static_assert(sv.size() == 1,
    //                      "File notation must contain exactly one character");
    //         return validate_char(sv[0]);
    //     } else {
    //         // Runtime validation with libassert rich diagnostics
    //         ASSERT(sv.size() == 1,
    //                "File notation length error. Expected: 1 character, got:",
    //                sv.size(), "characters in string:", sv);
    //         return validate_char(sv[0]);
    //     }
    // }

    static constexpr std::uint8_t validate_char(const char c) {
        char file = util::tolower(c);
        ASSERT(file >= 'a' && file <= 'h', "Invalid file character:", c,
               "Expected: 'a'-'h', got:", file);
        return file - 'a';
    }

    static constexpr std::uint8_t validate(std::string_view sv) {
        // Runtime validation with libassert rich diagnostics
        ASSERT(sv.size() == 1,
               "File notation length error. Expected: 1 character, got:",
               sv.size(), "characters in string:", sv);
        return validate_char(sv[0]);
    }

    std::uint8_t m_file;
    // internally stores 0-7,
    // takes user input between a-h
};

}  // namespace scy
