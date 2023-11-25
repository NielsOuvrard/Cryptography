#include "config.hpp"

static std::string rsa_public_key = "010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3";
static std::string rsa_private_key = "81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3";

std::string pgpEncrypt(const std::string &message, const std::string &key)
{

    std::pair<inf_int, inf_int> keyPair;
    keyPair.first = str_hexa_to_int(inverse_two_by_two_rev(rsa_public_key.substr(0, rsa_public_key.find("-"))));
    keyPair.second = str_hexa_to_int(inverse_two_by_two_rev(rsa_public_key.substr(rsa_public_key.find("-") + 1, rsa_public_key.length())));

    std::string encrypted_aes_key = rsaEncrypt(key, keyPair);
    std::string encrypted_message = aesEncrypt(message, key);
    return encrypted_aes_key + encrypted_message;
}

std::string pgpDecrypt(const std::string &encryptedMessage, const std::string &key)
{
    std::pair<inf_int, inf_int> keyPair;
    keyPair.first = str_hexa_to_int(inverse_two_by_two_rev(rsa_private_key.substr(0, rsa_private_key.find("-"))));
    keyPair.second = str_hexa_to_int(inverse_two_by_two_rev(rsa_private_key.substr(rsa_private_key.find("-") + 1, rsa_private_key.length())));

    std::string encrypted_aes_key = encryptedMessage.substr(0, 128);
    std::string encrypted_message = encryptedMessage.substr(128, encryptedMessage.length());

    std::string decrypted_aes_key = rsaDecrypt(encrypted_aes_key, keyPair);
    std::string decrypted_message = aesDecrypt(encrypted_message, decrypted_aes_key);
    return decrypted_message;
}
