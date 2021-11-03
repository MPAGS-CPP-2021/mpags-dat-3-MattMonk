//! Unit tests for MPAGSCipher CaesarCipher interface
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>

#include "CipherMode.hpp"
#include "CaesarCipher.hpp"
#include "ProcessCommandLine.hpp"
#include "TransformChar.hpp"

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
    CaesarCipher caesarCipher2{settings2.cipherKey_};

    const std::string inText1 {"hel& l0o"};
    std::string transText1{""};
    for(const char charcter : inText1) {
        transText1 += transformChar(charcter);
    }
    std::string outText1 {caesarCipher.applyCipher(transText1, settings1.cipherMode)};
    //When an invalid key is provided and applyCipher is used, a message warns the user
    //and the transliterated text is output. However, the transliterated text is NOT
    //the output of applyCipher(), that is done before applyCipher() is called and
    //actually the output of applyCipher is just replace the transliterated string
    //characters with 'x's because that is the place-holder character that is overwritten
    //in the loop, or in this case not over-written because an invalid key was supplied.
    REQUIRE(outText1 == "HELLZEROO");
    std::string outText2 {caesarCipher2.applyCipher(transText1, settings2.cipherMode)};
    REQUIRE(outText2 == "HELLZEROO");
}

TEST_CASE("Apply the cipher with keys > 25") {
    const std::string inText1 {"hel& l0o"};
    std::string transText1{""};
    for(const char charcter : inText1) {
        transText1 += transformChar(charcter);
    }
    CipherMode cipherMode {CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "40", cipherMode};
    CaesarCipher caesarCipher{settings1.cipherKey_};
    std::string outText1 {caesarCipher.applyCipher(transText1, settings1.cipherMode)};
    REQUIRE(outText1 == "VSZZNSFCC");

    CaesarCipher caesarCipher2{"40"};
    std::string inText2 {"VSZZNSFCC"};
    std::string outText2 {caesarCipher2.applyCipher(inText2, CipherMode::Decrypt)};
    REQUIRE(outText2 == "HELLZEROO");

    REQUIRE(outText1 == inText2);
}

TEST_CASE("Apply the cipher") {
    const std::string ascii {"! \" # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \\ ] ^ _ ` a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~"};
    std::string transAscii{""};
    for(const char charcter : ascii) {
        transAscii += transformChar(charcter);
    }
    for(std::size_t i{0}; i<26; i++) {
        CaesarCipher caesarCipher{i};
        std::string out1 {caesarCipher.applyCipher(transAscii, CipherMode::Encrypt)};
        std::string out2 {caesarCipher.applyCipher(transAscii, CipherMode::Decrypt)};

        std::string out3 {caesarCipher.applyCipher(out1, CipherMode::Decrypt)};
        std::string out4 {caesarCipher.applyCipher(out2, CipherMode::Encrypt)};

        REQUIRE(out3==transAscii);
        REQUIRE(out4==transAscii);
    }
    //And a specific key example, already tested forwards-backwards above
    CaesarCipher caesarCipher{5};
    std::string out5 {caesarCipher.applyCipher(transAscii, CipherMode::Encrypt)};
    REQUIRE(out5=="EJWTTSJYBTYMWJJKTZWKNAJXNCXJAJSJNLMYSNSJFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDE");

    CaesarCipher caesarCipher2{5};
    std::string out6 {caesarCipher2.applyCipher(transAscii, CipherMode::Decrypt)};
    REQUIRE(out6=="UZMJJIZORJOCMZZAJPMADQZNDSNZQZIZDBCOIDIZVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU");
}