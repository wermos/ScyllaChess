#pragma once

namespace scy::util {

constexpr char tolower(char c) {
    // `std::tolower` (in the `cctype` header) isn't `constexpr`, so we
    // roll our own `constexpr`-friendly version.
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

}  // namespace scy::util