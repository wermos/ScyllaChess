#pragma once

#include <cstdint>

#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"

namespace scy {

constexpr std::size_t diagonal_index(File file, Rank rank) noexcept {
    // file, rank both 0-based internally, but .file() returns File(char) and
    // .rank() returns Rank(uint8)
    std::size_t file_idx = static_cast<std::size_t>(file);  // 0..7
    std::size_t rank_idx =
        static_cast<std::size_t>(rank);  // 0..7 (since Rank(1)=0)
    // But your Rank(1) is m_rank=0, so is fine.
    return file_idx - rank_idx + 7;  // will be 0..14 if square is valid
}

constexpr std::size_t antidiagonal_index(File file, Rank rank) noexcept {
    std::size_t file_idx = static_cast<std::size_t>(file);  // 0..7
    std::size_t rank_idx = static_cast<std::size_t>(rank);  // 0..7
    return file_idx + rank_idx;                             // 0..14
}

}  // namespace scy
