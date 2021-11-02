//! Unit tests for MPAGSCipher CaesarCipher interface
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>

#include "CipherMode.hpp"
#include "CaesarCipher.hpp"
#include "ProcessCommandLine.hpp"

//A bit tricky to test. Really, I'd like to test separately
//the constructor that converts string->size_t but because
//key is a private member of CaesarCipher I can't test it
//without testing the whole applyCipher algorithm at the same
//time. Could also add a public getter I guess but I'm not sure
//if I should be adding something just for testing that would then
//be removed afterwards.

TEST_CASE("Apply the cipher with invalid keys") {
    //output should just be the transliterated input i.e.
    //a default key of 0 is used (so no shift)
    CipherMode cipherMode {CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "one", cipherMode};
    CaesarCipher caesarCipher{settings1.cipherKey_};
    ProgramSettings settings2 {false, false, "", "", "-1", cipherMode};
    CaesarCipher caesarCipher{settings2.cipherKey_};

    std::string outText1 {caesarCipher.applyCipher("hel& l0o", settings1.cipherMode)};
    REQUIRE(outText1 == "HELLZEROO");
    std::string outText2 {caesarCipher.applyCipher("hel& l0o", settings2.cipherMode)};
    REQUIRE(outText2 == "HELLZEROO");
}