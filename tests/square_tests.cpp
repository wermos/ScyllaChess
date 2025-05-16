#include <catch2/catch_all.hpp>

#include <cstdint>
#include <string>

#include "scylla/square.hpp"

TEST_CASE("Square basic conversions", "[square]") {
    scy::Square s1 = "e4";
    REQUIRE(static_cast<std::size_t>(s1) == 36);
    REQUIRE(static_cast<std::string>(s1) == "e4");

    scy::Square s2 = 28;
    REQUIRE(static_cast<std::string>(s2) == "d5");

    scy::Square s3 = "a1"_sq;
    REQUIRE(static_cast<std::size_t>(s3) == 0);
}

TEST_CASE("Square invalid input throws", "[square]") {
    REQUIRE_THROWS_AS(scy::Square("z9"), std::invalid_argument);
    REQUIRE_THROWS_AS(scy::Square("a9"), std::invalid_argument);
    REQUIRE_THROWS_AS(scy::Square("h0"), std::invalid_argument);
    REQUIRE_THROWS_AS(scy::Square(""), std::invalid_argument);
    REQUIRE_THROWS_AS(scy::Square(64), std::invalid_argument);
}
