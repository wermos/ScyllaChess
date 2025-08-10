// include/scylla/zobrist.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include <Xoshiro-cpp/XoshiroCpp.hpp>

#include "scylla/constants.hpp"

namespace scy::zobrist {

namespace generate_impl {

using namespace scy::consts;

using Key = std::uint64_t;

// RNG wrapper to allow for easy PRNG switching
struct RNG {
    XoshiroCpp::Xoshiro256StarStar rng;

    constexpr explicit RNG(std::uint64_t seed) : rng(seed) {}
    constexpr Key next() { return rng(); }
};

struct ZobristTables {
    std::array<std::array<Key, NUM_SQUARES>, NUM_PIECES> piece_square_keys{};
    std::array<Key, NUM_CASTLING_RIGHTS> castling_keys{};
    std::array<Key, NUM_FILES> en_passant_keys{};
    Key side_to_move_key{};
};

consteval ZobristTables generate(std::uint64_t seed = 0xDEADBEEFCAFEBABEull) {
    ZobristTables t{};
    RNG r(seed);

    for (std::size_t p = 0; p < NUM_PIECES; ++p)
        for (std::size_t sq = 0; sq < NUM_SQUARES; ++sq)
            t.piece_square_keys[p][sq] = r.next();

    for (std::size_t i = 0; i < NUM_CASTLING_RIGHTS; ++i)
        t.castling_keys[i] = r.next();

    for (std::size_t f = 0; f < NUM_FILES; ++f)
        t.en_passant_keys[f] = r.next();

    t.side_to_move_key = r.next();

    return t;
}

inline constexpr auto tables = generate_impl::generate();

// Public aliases for clarity
inline constexpr auto& piece_square_keys = tables.piece_square_keys;
inline constexpr auto& castling_keys     = tables.castling_keys;
inline constexpr auto& en_passant_keys   = tables.en_passant_keys;
inline constexpr auto  side_to_move_key  = tables.side_to_move_key;

} // namespace scy::zobrist
