#pragma once

#include <cstdint>
#include <stdexcept>

#include "scylla/chess_types/util.hpp"

namespace scy {

class File {
public:
    // explicit constexpr File(std::uint8_t f) : file(f) {
    //     if (f > 7) throw std::invalid_argument("Invalid file");
    // }

    explicit constexpr File(char c) :
        file((c >= 'a' && c <= 'h') ? c - 'a' : throw std::invalid_argument("Invalid file")) {}

    /// TODO: these might not be needed
    explicit constexpr File(const std::string& notation) : file(validate(notation)) {}
    explicit constexpr File(const char* notation) : File(std::string{notation}) {}

    // Predefined files
    static constexpr File A() noexcept { return File('a'); }
    static constexpr File B() noexcept { return File('b'); }
    static constexpr File C() noexcept { return File('c'); }
    static constexpr File D() noexcept { return File('d'); }
    static constexpr File E() noexcept { return File('e'); }
    static constexpr File F() noexcept { return File('f'); }
    static constexpr File G() noexcept { return File('g'); }
    static constexpr File H() noexcept { return File('h'); }

    /// we prefer to overload the std::string operator and the operator<<
    /// (stream) operator instead of this nonsense.
    // // Conversion
    // static constexpr File from_char(char c) {
    //     if(c < 'a' || c > 'h') throw std::invalid_argument("Invalid file");
    //     return File(c - 'a');
    // }
    
    // constexpr char to_char() const noexcept { return 'a' + file; }
    
    constexpr std::uint8_t index() const noexcept {
        /// TODO: is this function really needed?
        return file;
    }
    
    // Arithmetic
    constexpr File next() const noexcept { return File((file + 1) % 8); }
    constexpr File previous() const noexcept { return File((file - 1) % 8); }
    
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

    std::uint8_t file; // 0-7 (a-h)
};

}
