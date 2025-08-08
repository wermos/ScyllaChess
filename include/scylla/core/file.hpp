// include/scylla/core/file.hpp
#pragma once

#include <cstdint>
#include <libassert/assert.hpp>
#include <optional>
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

    // `std::size_t` is the "more proper" overload to have (as opposed to a
    // `std::uint8_t` overload because this will allow for indexing into the
    // mask arrays, which is one of the intended usecases.
    constexpr operator std::size_t() const noexcept {
        return m_file;
    }

    // "Iterators"
    constexpr File& operator++() {
        m_file++;
        ASSERT(m_file >= 0 && m_file <= 7,
               "File is invalid after increment:", m_file,
               "Expected a value between: 0-7");
        return *this;
    }

    constexpr File operator++(int) {
        File temp = *this;
        ++(*this);
        ASSERT(m_file >= 0 && m_file <= 7,
               "File is invalid after increment:", m_file,
               "Expected a value between: 0-7");
        return temp;
    }

    constexpr File& operator--() {
        m_file--;
        ASSERT(m_file >= 0 && m_file <= 7,
               "File is invalid after decrement:", m_file,
               "Expected a value between: 0-7");
        return *this;
    }

    constexpr File operator--(int) {
        File temp = *this;
        --(*this);
        ASSERT(m_file >= 0 && m_file <= 7,
               "File is invalid after decrement:", m_file,
               "Expected a value between: 0-7");
        return temp;
    }

    constexpr std::optional<File> offset(std::int64_t delta) const noexcept {
        std::int64_t new_file_idx = static_cast<std::int64_t>(m_file) + delta;
        // m_file is 0..7 internally, so valid range is 0..7
        if (new_file_idx < 0 || new_file_idx > 7) {
            return std::nullopt;
        }
        // Converts back to char for File constructor: 'a' is 0
        return File(static_cast<char>('a' + new_file_idx));
    }

    // Comparison
    auto operator<=>(const File&) const = default;

   private:
    static constexpr std::uint8_t validate_char(const char c) {
        char file = util::tolower(c);
        ASSERT(file >= 'a' && file <= 'h', "Invalid file character:", c,
               "Expected: 'a'-'h', got:", file);
        return file - 'a';
    }

    static constexpr std::uint8_t validate(std::string_view sv) {
        // Runtime validation with libassert
        ASSERT(sv.size() == 1,
               "File notation length error. Expected: 1 character, got:",
               sv.size(), "characters in string:", sv);
        return validate_char(sv[0]);
    }

    std::uint8_t m_file;
    // internally stores 0-7,
    // takes user input between 'a'-'h'
};

}  // namespace scy
