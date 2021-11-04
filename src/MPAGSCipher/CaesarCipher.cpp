#include "CaesarCipher.hpp"
#include "CipherMode.hpp"

#include <string>
#include <iostream>


CaesarCipher::CaesarCipher(const std::size_t key)
    : key_{key}
{

}

CaesarCipher::CaesarCipher(const std::string& key)
    : key_{0}
{
    if (!key.empty()) {
        // Before doing the conversion we should check that the string contains a
        // valid positive integer.
        // Here we do that by looping through each character and checking that it
        // is a digit. What is rather hard to check is whether the number is too
        // large to be represented by an unsigned long, so we've omitted that for
        // the time being.
        // (Since the conversion function std::stoul will throw an exception if the
        // string does not represent a valid unsigned long, we could check for and
        // handled that instead but we only cover exceptions very briefly on the
        // final day of this course - they are a very complex area of C++ that
        // could take an entire course on their own!)
        for (const auto& elem : key) {
            if (!std::isdigit(elem)) {
                std::cerr
                    << "[error] cipher key must be an unsigned long integer for Caesar cipher,\n"
                    << "        the supplied key (" << key
                    << ") could not be successfully converted" << std::endl;
                return;
            }
        }
        key_ = std::stoul(key);
    }
}

std::string CaesarCipher::applyCipher(const std::string& inputText,
                    const CipherMode cipherMode) const
{
    // Create the output string
    std::string outputText;

    const std::size_t alphabetSize{alphabet_.size()};

    const std::size_t truncatedKey{key_ % alphabetSize};

    // Loop over the input text
    char processedChar{'x'};
    for (const auto& origChar : inputText) {
        // For each character in the input text, find the corresponding position in
        // the alphabet by using an indexed loop over the alphabet container
        for (size_t i{0}; i < alphabetSize; ++i) {
            if (origChar == alphabet_[i]) {
                // Apply the appropriate shift (depending on whether we're encrypting
                // or decrypting) and determine the new character
                // Can then break out of the loop over the alphabet
                switch(cipherMode) {
                    case CipherMode::Encrypt:
                        processedChar = alphabet_[(i + truncatedKey) % alphabetSize];
                        break;
                    case CipherMode::Decrypt:
                        processedChar = alphabet_[(i + alphabetSize - truncatedKey) %
                                             alphabetSize];
                        break;
                }
                break;
            }
        }

        // Add the new character to the output text
        outputText += processedChar;
    }

    return outputText;
}