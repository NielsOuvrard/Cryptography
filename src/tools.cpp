#include "../include/config.hpp"

std::string stringToHex(const std::string& input) {
    std::ostringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (char c : input) {
        hexStream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
    }
    return hexStream.str();
}

std::string hexToString(const std::string& hex) {
    std::string result;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = static_cast<char>(std::stoi(byteString, nullptr, 16));
        result += byte;
    }
    return result;
}

std::string hexToBinary(std::string hex) {
    std::string binary;
    for (char hexChar : hex) {
        switch (hexChar) {
            case '0': binary.append("0000"); break;
            case '1': binary.append("0001"); break;
            case '2': binary.append("0010"); break;
            case '3': binary.append("0011"); break;
            case '4': binary.append("0100"); break;
            case '5': binary.append("0101"); break;
            case '6': binary.append("0110"); break;
            case '7': binary.append("0111"); break;
            case '8': binary.append("1000"); break;
            case '9': binary.append("1001"); break;
            case 'a': case 'A': binary.append("1010"); break;
            case 'b': case 'B': binary.append("1011"); break;
            case 'c': case 'C': binary.append("1100"); break;
            case 'd': case 'D': binary.append("1101"); break;
            case 'e': case 'E': binary.append("1110"); break;
            case 'f': case 'F': binary.append("1111"); break;
        }
    }
    return binary;
}

std::string binaryToAscii(std::string binary) {
    std::string ascii = "";
    for (size_t i = 0; i < binary.length(); i += 8) {
        std::bitset<8> bits(binary.substr(i, 8));
        ascii += static_cast<char>(bits.to_ulong());
    }
    return ascii;
}

std::string binaryToHex(std::string binary) {
    std::stringstream ss;
    ss << std::hex << std::bitset<8>(binary).to_ulong();
    return ss.str();
}
