
#include "config.hpp"

std::string xorEncryptDecrypt(const std::string& input, const std::string& key) {
    std::string output = input;
    for (size_t i = 0; i < input.length(); ++i) {
        output[i] = input[i] ^ key[i % key.length()];
    }
    return output;
}