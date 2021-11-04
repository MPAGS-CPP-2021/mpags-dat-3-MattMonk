//! Unit tests for MPAGSCipher transformChar interface
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CipherMode.hpp"
#include "ProcessCommandLine.hpp"

TEST_CASE("Help has/ has not been requested", "[bool]") {
    CipherMode cipherMode{CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "", cipherMode};
    ProgramSettings settings2 {false, false, "", "", "", cipherMode};
    ProgramSettings settings3 {false, false, "", "", "", cipherMode};
    ProgramSettings settings4 {false, false, "", "", "", cipherMode};
    ProgramSettings settings5 {false, false, "", "", "", cipherMode};
    ProgramSettings settings6 {false, false, "", "", "", cipherMode};
    std::vector<std::string> cmdLineArgs1{"./mpags-cipher", "--version"};
    std::vector<std::string> cmdLineArgs2{"./mpags-cipher", "--help", "--version"};
    std::vector<std::string> cmdLineArgs3{"./mpags-cipher", "--help"};
    std::vector<std::string> cmdLineArgs4{"./mpags-cipher", "--version", "-h"};
    std::vector<std::string> cmdLineArgs5{"./mpags-cipher", "-h"};
    std::vector<std::string> cmdLineArgs6{"./mpags-cipher", "--help", "-h"};

    //Note, can use [[gnu::unused]] to avoid compiler warnings about unused variables
    bool check1 {processCommandLine(cmdLineArgs1, settings1)};
    REQUIRE(settings1.helpRequested_ == false);
    REQUIRE(check1 == true);
    bool check2 {processCommandLine(cmdLineArgs2, settings2)};
    REQUIRE(check2 == true);
    REQUIRE(settings2.helpRequested_ == true);
    bool check3 {processCommandLine(cmdLineArgs3, settings3)};
    REQUIRE(check3 == true);
    REQUIRE(settings3.helpRequested_ == true);
    bool check4 {processCommandLine(cmdLineArgs4, settings4)};
    REQUIRE(check4 == true);
    //False because version requested first
    REQUIRE(settings4.helpRequested_ == false);
    bool check5 {processCommandLine(cmdLineArgs5, settings5)};
    REQUIRE(check5 == true);
    REQUIRE(settings5.helpRequested_ == true);
    bool check6 {processCommandLine(cmdLineArgs6, settings6)};
    REQUIRE(check6 == true);
    REQUIRE(settings6.helpRequested_ == true);
}

TEST_CASE("Version has/ has not been requested", "[bool]") {
    CipherMode cipherMode{CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "", cipherMode};
    ProgramSettings settings2 {false, false, "", "", "", cipherMode};
    ProgramSettings settings3 {false, false, "", "", "", cipherMode};
    ProgramSettings settings4 {false, false, "", "", "", cipherMode};
    std::vector<std::string> cmdLineArgs1{"./mpags-cipher", "--help"};
    std::vector<std::string> cmdLineArgs2{"./mpags-cipher", "--version", "--help"};
    std::vector<std::string> cmdLineArgs3{"./mpags-cipher", "--version"};
    std::vector<std::string> cmdLineArgs4{"./mpags-cipher", "-i", "in.txt", "--version"};

    //Use [[gnu::unused]] to avoid compiler warnings about unused variables
    bool check1 {processCommandLine(cmdLineArgs1, settings1)};
    REQUIRE(settings1.versionRequested_ == false);
    REQUIRE(check1 == true);
    bool check2 {processCommandLine(cmdLineArgs2, settings2)};
    REQUIRE(settings2.versionRequested_ == true);
    REQUIRE(check2 == true);
    bool check3 {processCommandLine(cmdLineArgs3, settings3)};
    REQUIRE(settings3.versionRequested_ == true);
    REQUIRE(check3 == true);
    bool check4 {processCommandLine(cmdLineArgs4, settings4)};
    REQUIRE(settings4.versionRequested_ == true);
    REQUIRE(check4 == true);
}

TEST_CASE("Input file has been provided", "[bool]") {
    CipherMode cipherMode{CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "", cipherMode};
    ProgramSettings settings2 {false, false, "", "", "", cipherMode};
    std::vector<std::string> cmdLineArgs1{"./mpags-cipher", "-i", "in.txt"};
    std::vector<std::string> cmdLineArgs2{"./mpags-cipher", "-i"};

    bool check1 {processCommandLine(cmdLineArgs1, settings1)};
    REQUIRE(settings1.inputFile_ == "in.txt");
    REQUIRE(check1 == true);
    bool check2 {processCommandLine(cmdLineArgs2, settings2)};
    REQUIRE(settings2.inputFile_ == "");
    REQUIRE(check2 == false);
}

TEST_CASE("Output file has been provided", "[bool]") {
    CipherMode cipherMode{CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "", cipherMode};
    ProgramSettings settings2 {false, false, "", "", "", cipherMode};
    std::vector<std::string> cmdLineArgs1{"./mpags-cipher", "-o", "out.txt"};
    std::vector<std::string> cmdLineArgs2{"./mpags-cipher", "-o"};

    bool check1 {processCommandLine(cmdLineArgs1, settings1)};
    REQUIRE(settings1.outputFile_ == "out.txt");
    REQUIRE(check1 == true);
    bool check2 {processCommandLine(cmdLineArgs2, settings2)};
    REQUIRE(settings2.outputFile_ == "");
    REQUIRE(check2 == false);
}

TEST_CASE("Encrypt/decrypt", "[bool]") {
    CipherMode cipherMode{CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "", cipherMode};
    ProgramSettings settings2 {false, false, "", "", "", cipherMode};
    std::vector<std::string> cmdLineArgs1{"./mpags-cipher", "--encrypt"};
    std::vector<std::string> cmdLineArgs2{"./mpags-cipher", "--decrypt"};

    bool check1 {processCommandLine(cmdLineArgs1, settings1)};
    REQUIRE(settings1.cipherMode == CipherMode::Encrypt);
    REQUIRE(check1 == true);
    bool check2 {processCommandLine(cmdLineArgs2, settings2)};
    REQUIRE(settings2.cipherMode == CipherMode::Decrypt);
    REQUIRE(check2 == true);
}

TEST_CASE("Encryption key", "[bool]") {
    //Key input is just a string at this point, test sanity checks later
    CipherMode cipherMode{CipherMode::Encrypt};
    ProgramSettings settings1 {false, false, "", "", "", cipherMode};
    ProgramSettings settings2 {false, false, "", "", "", cipherMode};
    ProgramSettings settings3 {false, false, "", "", "", cipherMode};
    ProgramSettings settings4 {false, false, "", "", "", cipherMode};
    ProgramSettings settings5 {false, false, "", "", "", cipherMode};
    ProgramSettings settings6 {false, false, "", "", "", cipherMode};
    ProgramSettings settings7 {false, false, "", "", "", cipherMode};
    ProgramSettings settings8 {false, false, "", "", "", cipherMode};
    std::vector<std::string> cmdLineArgs1{"./mpags-cipher", "-k", "0"};
    std::vector<std::string> cmdLineArgs2{"./mpags-cipher", "-k", "1"};
    std::vector<std::string> cmdLineArgs3{"./mpags-cipher", "-k", "12"};
    std::vector<std::string> cmdLineArgs4{"./mpags-cipher", "-k", "500"};
    std::vector<std::string> cmdLineArgs5{"./mpags-cipher", "-k", "-2"};
    std::vector<std::string> cmdLineArgs6{"./mpags-cipher", "-k", "-299"};
    std::vector<std::string> cmdLineArgs7{"./mpags-cipher", "-k", "One"};
    std::vector<std::string> cmdLineArgs8{"./mpags-cipher", "-k"};

    bool check1 {processCommandLine(cmdLineArgs1, settings1)};
    REQUIRE(settings1.cipherKey_ == "0");
    REQUIRE(check1 == true);
    bool check2 {processCommandLine(cmdLineArgs2, settings2)};
    REQUIRE(settings2.cipherKey_ == "1");
    REQUIRE(check2 == true);
    bool check3 {processCommandLine(cmdLineArgs3, settings3)};
    REQUIRE(settings3.cipherKey_ == "12");
    REQUIRE(check3 == true);
    bool check4 {processCommandLine(cmdLineArgs4, settings4)};
    REQUIRE(settings4.cipherKey_ == "500");
    REQUIRE(check4 == true);
    bool check5 {processCommandLine(cmdLineArgs5, settings5)};
    REQUIRE(settings5.cipherKey_ == "-2");
    REQUIRE(check5 == true);
    bool check6 {processCommandLine(cmdLineArgs6, settings6)};
    REQUIRE(settings6.cipherKey_ == "-299");
    REQUIRE(check6 == true);
    bool check7 {processCommandLine(cmdLineArgs7, settings7)};
    REQUIRE(settings7.cipherKey_ == "One");
    REQUIRE(check7 == true);
    bool check8 {processCommandLine(cmdLineArgs8, settings8)};
    REQUIRE(check8 == false);
}