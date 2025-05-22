#include <catch2/catch_all.hpp>
#include <cstdint>
#include <string>

#include "scylla/core/file.hpp"
#include "scylla/core/rank.hpp"
#include "scylla/core/square.hpp"

TEST_CASE("Square basic conversions", "[square]") {
    scy::Square s1 = "e4";
    REQUIRE(static_cast<std::size_t>(s1) == 28);
    REQUIRE(static_cast<std::string>(s1) == "e4");

    scy::Square s2 = 35;
    REQUIRE(static_cast<std::string>(s2) == "d5");

    scy::Square s3 = "a1"_sq;
    REQUIRE(static_cast<std::size_t>(s3) == 0);
}

TEST_CASE("Square from File and Rank", "[square]") {
    scy::Square s1(scy::File('e'), scy::Rank(4));

    REQUIRE(static_cast<std::size_t>(s1) == 28);
    REQUIRE(static_cast<std::string>(s1) == "e4");

    scy::Square s2(scy::File('c'), scy::Rank(7));
    REQUIRE(static_cast<std::size_t>(s2) == 50);
    REQUIRE(static_cast<std::string>(s2) == "c7");
}

TEST_CASE("Square invalid input throws", "[square]") {
    REQUIRE_THROWS_AS(scy::Square("z9"), std::invalid_argument);
    REQUIRE_THROWS_AS(scy::Square("a9"), std::invalid_argument);
    REQUIRE_THROWS_AS(scy::Square("h0"), std::invalid_argument);
    REQUIRE_THROWS_AS(scy::Square(""), std::invalid_argument);
    REQUIRE_THROWS_AS(scy::Square(64), std::invalid_argument);
}
