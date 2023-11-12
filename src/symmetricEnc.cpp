#include "config.hpp"

std::string xorEncrypt(const std::string &message, const std::string &key)
{
    std::string encryptedMessage;
    for (size_t i = 0; i < message.length(); ++i) {
        char encryptedByte = message[i] ^ key[i];
        encryptedMessage += encryptedByte;
    }

    return stringToHex(encryptedMessage);
}

std::string xorDecrypt(const std::string &encryptedMessage, const std::string &key)
{
    std::string hexDecryptedMessage = hexToString(encryptedMessage);
    return hexToString(xorEncrypt(encryptedMessage, key));
}


std::string xorEncryptDecrypt(const std::string &input, const std::string &key)
{
    std::string output(input.size(), '0');

    for (size_t i = 0; i < input.size(); i++) {
        output[i] = ((input[i] - '0') ^ (key[i % key.size()] - '0')) + '0';
    }

    return output;
}
