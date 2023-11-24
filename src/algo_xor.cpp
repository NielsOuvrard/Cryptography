#include "config.hpp"

std::string stringToHex(const std::string &input)
{
    std::ostringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (char c: input) {
        hexStream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
    }
    return hexStream.str();
}

std::string hexToString(const std::string &hex)
{
    std::string result;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = static_cast<char>(std::stoi(byteString, nullptr, 16));
        result += byte;
    }
    return result;
}

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
        char a = CHAR_HEX_TO_INT(input[i]) ^ CHAR_HEX_TO_INT(key[i % key.size()]);
        output[i] = INT_TO_CHAR_HEX(a);
    }

    return output;
}
