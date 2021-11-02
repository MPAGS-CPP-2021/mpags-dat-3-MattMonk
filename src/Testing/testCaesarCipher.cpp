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

TEST_CASE("Apply the cipher with keys > 25") {
    CipherMode cipherMode {CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "40", cipherMode};
    CaesarCipher caesarCipher{settings1.cipherKey_};
    std::string inText1 {"hel& l0o"};
    std::string outText1 {caesarCipher.applyCipher(inText1, settings1.cipherMode)};
    REQUIRE(outText1 == "VSZZNSFCC");

    CipherMode cipherMode2 {CipherMode::Decrypt};
    ProgramSettings settings2 {false, false, "", "", "40", cipherMode2};
    CaesarCipher caesarCipher2{settings1.cipherKey_};
    std::string inText2 {"VSZZNSFCC"};
    std::string outText2 {caesarCipher2.applyCipher(inText2, settings2.cipherMode)};
    REQUIRE(outText2 == "hel& l0o");

    REQUIRE(outText1 == inText2);
    REQUIRE(outText2 == inText1);
}

TEST_CASE("Apply the cipher") {
    std::string ascii {"! \" # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \\ ] ^ _ ` a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~"};
    for(std::size_t i=0; i<26; i++) {
        CaesarCipher caesarCipher{i};
        std::string out1 {caesarCipher.applyCipher(ascii, CipherMode::Encrypt)};
        std::string out2 {caesarCipher.applyCipher(ascii, CipherMode::Decrypt)};

        std::string out3 {caesarCipher.applyCipher(out1, CipherMode::Decrypt)};
        std::string out4 {caesarCipher.applyCipher(out2, CipherMode::Encrypt)};

        REQUIRE(out1==out3);
        REQUIRE(out2==out4);
    }
    //And a specific key example
    CaesarCipher caesarCipher{5};
    std::string out5 {caesarCipher.applyCipher(ascii, CipherMode::Encrypt)};
    REQUIRE(out5=="FGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDE");

    CaesarCipher caesarCipher2{5};
    std::string out6 {caesarCipher2.applyCipher(out5, CipherMode::Decrypt)};
    REQUIRE(out6=="ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ")
}