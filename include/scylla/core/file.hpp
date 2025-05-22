#pragma once

#include <cstdint>
#include <stdexcept>

#include "scylla/util.hpp"

namespace scy {

class File {
   public:
    explicit constexpr File(char c)
        : file((c >= 'a' && c <= 'h')
                   ? c - 'a'
                   : throw std::invalid_argument("Invalid file")) {}

    /// TODO: these might not be needed
    explicit constexpr File(const std::string& notation)
        : file(validate(notation)) {}
    explicit constexpr File(const char* notation)
        : File(std::string{notation}) {}

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
    // constexpr operator std::size_t() const noexcept {
    //     return file;
    // }

    constexpr operator std::uint8_t() const noexcept {
        return file;
    }

    // Iterators
    constexpr File next() const noexcept {
        return File((file + 1) % 8);
    }
    constexpr File previous() const noexcept {
        return File((file - 1) % 8);
    }

    // Comparison
    auto operator<=>(const File&) const = default;

   private:
    constexpr static std::size_t validate(const std::string& s) {
        if (s.length() != 1) {
            throw std::invalid_argument("Invalid file");
        }

        char file = util::tolower(s[0]);

        if (file < 'a' || file > 'h') {
            throw std::invalid_argument("Invalid file");
        }

        return file - 'a';
    }

    std::uint8_t file;
    // internally stores 0-7,
    // takes user input between a-h
};

}  // namespace scy
