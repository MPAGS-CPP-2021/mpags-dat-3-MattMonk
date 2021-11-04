//! Unit tests for MPAGSCipher transformChar interface
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>

#include "TransformChar.hpp"

TEST_CASE("Characters are uppercased", "[alphanumeric]") {
    const std::vector<std::string> upper{"A", "B", "C", "D", "E" ,"F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    const std::vector<char> lower{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                  'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                  's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for(size_t i=0;i<upper.size();i++) {
        REQUIRE(transformChar(lower[i]) == upper[i]);
    }
}

TEST_CASE("Digits are transliterated", "[alphanumeric]") {
    REQUIRE(transformChar('0') == "ZERO");
    REQUIRE(transformChar('1') == "ONE");
    REQUIRE(transformChar('2') == "TWO");
    REQUIRE(transformChar('3') == "THREE");
    REQUIRE(transformChar('4') == "FOUR");
    REQUIRE(transformChar('5') == "FIVE");
    REQUIRE(transformChar('6') == "SIX");
    REQUIRE(transformChar('7') == "SEVEN");
    REQUIRE(transformChar('8') == "EIGHT");
    REQUIRE(transformChar('9') == "NINE");
}

TEST_CASE("Characters are removed", "[alphanumeric]") {
    const std::string chars{"!\"#$%&\\\'()*+,-./:;<=>?@[\\]^_`{|}~ "};
    for(const auto character : chars) {
        REQUIRE(transformChar(character) == "");
    }
}