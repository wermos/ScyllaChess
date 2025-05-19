#include <catch2/catch_all.hpp>

#include "scylla/bitboard.hpp"
#include "scylla/chess_types/file.hpp"
#include "scylla/chess_types/rank.hpp"

using namespace scy;

TEST_CASE("Bitboard from File and Rank", "[bitboard]") {
    Bitboard b1(File('f'), Rank(5));

    REQUIRE(b1 == Bitboard{1uz << 37});

    Bitboard b2(File('h'), Rank(8));

    REQUIRE(b2 == Bitboard{1uz << 63});
}

TEST_CASE("Bitboard set and unset", "[bitboard]") {
    Bitboard b;
    REQUIRE(b == Bitboard{});

    b.set("a1"_sq);
    b.set("e4"_sq);
    b.set(63);
    REQUIRE(b != Bitboard{});

    b.unset("e4"_sq);
    REQUIRE(b != Bitboard{});
    b.unset("a1"_sq);
    b.unset(63);
    REQUIRE(b == Bitboard{});
}

TEST_CASE("Bitboard bitwise operations", "[bitboard]") {
    Bitboard a;
    Bitboard b;
    a.set("e4"_sq);
    b.set("e4"_sq);
    b.set("d5"_sq);

    Bitboard c = a & b;
    REQUIRE(c != Bitboard{});
    REQUIRE(c == Bitboard{1uz << 28});  // e4 only

    Bitboard d = a | b;
    REQUIRE(d != a);
    REQUIRE(d == b);

    Bitboard e = d;
    e ^= a;
    REQUIRE(e != a);
    REQUIRE(e != b);
    REQUIRE(e == Bitboard{1uz << 35});  // d5 only
}

TEST_CASE("Bitboard NOT operator", "[bitboard]") {
    Bitboard b;
    b.set("a1"_sq);
    Bitboard flipped = ~b;

    REQUIRE((flipped != b));
    REQUIRE((flipped & Bitboard{1uz << 0}) == Bitboard{});
}