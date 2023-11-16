#include "config.hpp"

boost::multiprecision::cpp_int read_from_little_endian(std::string str)
{
    boost::multiprecision::cpp_int res = 0;
    for (int i = str.length() - 1; i >= 0; i -= 2) {
        res = res * 16 + CHAR_HEX_TO_INT(str[i - 1]);
        res = res * 16 + CHAR_HEX_TO_INT(str[i]);
    }
    return res;
}

int handle_input(arguments_t *args)
{
    if (args->generate_key) {
        generateKeyPair(args->p, args->q);
        return EXIT_SUCCESS;
    }
    std::string input;
    std::getline(std::cin, input);
    // std::cout << "input: " << input << std::endl;

    if (args->xor_) {
        if (args->block_mode) {
            if (input.length() != args->key.length()) {
                std::cerr << "In block mode, MESSAGE and KEY must be of the same size."
                          << "input: " << input.length() << " key: " << args->key.length() << std::endl;
                return EXIT_ERROR;
            }
        }
        std::cout << xorEncryptDecrypt(input, args->key) << std::endl;
    } else if (args->aes) {
        if (args->block_mode) {
            if (input.length() != args->key.length()) {
                std::cerr << "In block mode, MESSAGE and KEY must be of the same size."
                          << "input" << input.length() << "key" << args->key.length() << std::endl;
                return EXIT_ERROR;
            }
            std::cout << aesEncryptDecrypt(input, args->key) << std::endl;
        }
    } else if (args->rsa) {
        std::pair<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int> keyPair;
        keyPair.first = read_from_little_endian(args->key.substr(0, args->key.find("-")));
        keyPair.second = read_from_little_endian(args->key.substr(args->key.find("-") + 1, args->key.length()));
        if (args->encrypt) {
            rsaEncrypt(input, keyPair);
        } else if (args->decrypt) {
            rsaDecrypt(input, keyPair);
        }
    } else if (args->pgp) {
        if (args->block_mode) {
            if (input.length() != args->key.length()) {
                std::cerr << "In block mode, MESSAGE and KEY must be of the same size."
                          << "input" << input.length() << "key" << args->key.length() << std::endl;
                return EXIT_ERROR;
            }
            // std::cout << pgpEncryptDecrypt(input, args->key) << std::endl;
        }
    }
    return EXIT_SUCCESS;
}

/*
std::string key1 = "68656c6c6f20776f726c64";  // "hello world" in ASCII
std::string message = "74657374206d657373616765";  // "test message" in ASCII

* Convert key1 and message to binary
std::string binaryKey = hexToBinary(key1);
std::string binaryMessage = hexToBinary(message);

* Encrypt
std::string encrypted = xorEncryptDecrypt(binaryMessage, binaryKey);

* Decrypt
std::string decrypted = xorEncryptDecrypt(encrypted, binaryKey);

* Print results
std::cout << "Encrypted: " << encrypted << std::endl;
std::cout << "Decrypted: " << binaryToAscii(decrypted) << std::endl;
*/

int main(int argc, char *argv[])
{
    // for (int i = 256; i < 512; i++)
    //     std::cout << int_to_str_hexa(i) << std::endl;
    // return EXIT_SUCCESS;
    arguments_t args = {"", false, false, false, false, false, false, false, false, "", "", false};

    if (handle_arguments(argc, argv, &args) == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (args.help) {
        return EXIT_SUCCESS;
    }

    // print_arguments(args);

    return handle_input(&args);
}
