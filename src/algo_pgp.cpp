#include "config.hpp"

std::string generateRandomAESKey()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 15);

    std::ostringstream oss;
    oss << std::hex;

    for (int i = 0; i < 32; ++i) {
        oss << dis(gen);
    }

    return oss.str();
}

std::string pgpEncrypt(const std::string &message, const std::string &key)
{

    std::pair<inf_int, inf_int> keyPair;
    keyPair.first = str_hexa_to_int(inverse_two_by_two_rev(key.substr(0, key.find("-"))));
    keyPair.second = str_hexa_to_int(inverse_two_by_two_rev(key.substr(key.find("-") + 1, key.length())));

    std::string aes_key = generateRandomAESKey();

    std::string encrypted_aes_key = rsaEncrypt(aes_key, keyPair);
    std::string encrypted_message = aesEncrypt(message, aes_key);
    return encrypted_aes_key + encrypted_message;
}

std::string pgpDecrypt(const std::string &encryptedMessage, const std::string &key)
{
    std::pair<inf_int, inf_int> keyPair;
    keyPair.first = str_hexa_to_int(inverse_two_by_two_rev(key.substr(0, key.find("-"))));
    keyPair.second = str_hexa_to_int(inverse_two_by_two_rev(key.substr(key.find("-") + 1, key.length())));

    std::string encrypted_aes_key = encryptedMessage.substr(0, 128);
    std::string encrypted_message = encryptedMessage.substr(128, encryptedMessage.length());

    std::string decrypted_aes_key = rsaDecrypt(encrypted_aes_key, keyPair);
    std::string decrypted_message = aesDecrypt(encrypted_message, decrypted_aes_key);
    return decrypted_message;
}
