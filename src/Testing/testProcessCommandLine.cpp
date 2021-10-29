//! Unit tests for MPAGSCipher transformChar interface
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CipherMode.hpp"
#include "ProcessCommandLine.hpp"

TEST_CASE("Help has/ has not been requested", "[bool]") {
    CipherMode cipherMode{CipherMode::Encrypt};
    ProgramSettings settings {false, false, "", "", "", cipherMode};
    std::vector<std::string> cmdLineArgs1{"./mpags-cipher", "--version"};
    std::vector<std::string> cmdLineArgs2{"./mpags-cipher", "--help", "--version"};
    std::vector<std::string> cmdLineArgs3{"./mpags-cipher", "--help"};
    std::vector<std::string> cmdLineArgs4{"./mpags-cipher", "--version", "-h"};
    std::vector<std::string> cmdLineArgs5{"./mpags-cipher", "-h"};
    std::vector<std::string> cmdLineArgs6{"./mpags-cipher", "--help", "-h"};

    //Use [[gnu::unused]] to avoid compiler warnings about unused variables
    bool dummy1 [[gnu::unused]] {processCommandLine(cmdLineArgs1, settings)};
    REQUIRE(settings.helpRequested_ == false);
    bool dummy2 [[gnu::unused]] {processCommandLine(cmdLineArgs2, settings)};
    REQUIRE(settings.helpRequested_ == true);
    bool dummy3 [[gnu::unused]] {processCommandLine(cmdLineArgs3, settings)};
    REQUIRE(settings.helpRequested_ == true);
    bool dummy4 [[gnu::unused]] {processCommandLine(cmdLineArgs4, settings)};
    REQUIRE(settings.helpRequested_ == true);
    bool dummy5 [[gnu::unused]] {processCommandLine(cmdLineArgs5, settings)};
    REQUIRE(settings.helpRequested_ == true);
    bool dummy6 [[gnu::unused]] {processCommandLine(cmdLineArgs6, settings)};
    REQUIRE(settings.helpRequested_ == true);
}

TEST_CASE("Version has/ has not been requested", "[bool]") {
    CipherMode cipherMode{CipherMode::Encrypt};
    ProgramSettings settings {false, false, "", "", "", cipherMode};
    std::vector<std::string> cmdLineArgs1{"./mpags-cipher", "--help"};
    std::vector<std::string> cmdLineArgs2{"./mpags-cipher", "--version", "--help"};
    std::vector<std::string> cmdLineArgs3{"./mpags-cipher", "--version"};
    std::vector<std::string> cmdLineArgs4{"./mpags-cipher", "--help", "-v"};
    std::vector<std::string> cmdLineArgs5{"./mpags-cipher", "-i", "in.txt", "-v"};
    std::vector<std::string> cmdLineArgs6{"./mpags-cipher", "-v"};
    std::vector<std::string> cmdLineArgs7{"./mpags-cipher", "--version", "-v"};

    //Use [[gnu::unused]] to avoid compiler warnings about unused variables
    bool dummy1 [[gnu::unused]] {processCommandLine(cmdLineArgs1, settings)};
    REQUIRE(settings.versionRequested_ == false);
    bool dummy2 [[gnu::unused]] {processCommandLine(cmdLineArgs2, settings)};
    REQUIRE(settings.versionRequested_ == true);
    bool dummy3 [[gnu::unused]] {processCommandLine(cmdLineArgs3, settings)};
    REQUIRE(settings.versionRequested_ == true);
    bool dummy4 [[gnu::unused]] {processCommandLine(cmdLineArgs4, settings)};
    REQUIRE(settings.versionRequested_ == true);
    bool dummy5 [[gnu::unused]] {processCommandLine(cmdLineArgs5, settings)};
    REQUIRE(settings.versionRequested_ == true);
    bool dummy6 [[gnu::unused]] {processCommandLine(cmdLineArgs6, settings)};
    REQUIRE(settings.versionRequested_ == true);
    bool dummy7 [[gnu::unused]] {processCommandLine(cmdLineArgs7, settings)};
    REQUIRE(settings.versionRequested_ == true);
}