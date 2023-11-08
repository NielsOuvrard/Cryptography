
#include "config.hpp"

std::string xorEncryptDecrypt(const std::string& input, const std::string& key) {
    std::string output = input;
    for (size_t i = 0; i < input.length(); ++i) {
        output[i] = input[i] ^ key[i % key.length()];
    }
    return output;
}

// std::string aesEncryptDecrypt(const std::string& input, const std::string& key, bool encrypt) {
//     std::string output;
//     CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption e;
//     CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption d;
//     if (encrypt) {
//         e.SetKey((const CryptoPP::byte*)key.data(), key.size());
//         CryptoPP::StringSource(input, true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(output)));
//     } else {
//         d.SetKey((const CryptoPP::byte*)key.data(), key.size());
//         CryptoPP::StringSource(input, true, new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(output)));
//     }
//     return output;
// }
//