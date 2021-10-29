#ifndef MPAGSCIPHER_CAESARCIPHER_HPP
#define MPAGSCIPHER_CAESARCIPHER_HPP

#include "CipherMode.hpp"

#include <cstddef>
#include <string>
#include <vector>

class CaesarCipher {
    public:
        explicit CaesarCipher(const std::size_t key);
        explicit CaesarCipher(const std::string& key);
        std::string applyCipher(const std::string& inputText,
                    const CipherMode cipherMode) const;
    private:
        std::size_t key_{0};
        const std::vector<char> alphabet_{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
};

#endif    // MPAGSCIPHER_CAESARCIPHER_HPP