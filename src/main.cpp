#include "config.hpp"

int handle_input(arguments_t *args)
{
    std::string input;
    std::getline(std::cin, input);
    // std::cout << "input: " << input << std::endl;

    if (args->xor_) {
        if (args->block_mode) {
            if (input.length() != args->key.length()) {
                std::cerr << "In block mode, MESSAGE and KEY must be of the same size."
                          << "input: " << input.length() << " key: " << args->key.length() << std::endl;
                return 84;
            }
        }
        std::cout << xorEncryptDecrypt(input, args->key) << std::endl;
    } else if (args->aes) {
        if (args->block_mode) {
            if (input.length() != args->key.length()) {
                std::cerr << "In block mode, MESSAGE and KEY must be of the same size."
                          << "input" << input.length() << "key" << args->key.length() << std::endl;
                return 84;
            }
            std::cout << aesEncryptDecrypt(input, args->key) << std::endl;
        }
    } else if (args->rsa) {
        if (args->generate_key) {
            std::cout << "Generating key pair from P=" << args->p << " and Q=" << args->q << std::endl;
            // std::pair<int, int> keyPair = generateKeyPair(args->p, args->q);
            // std::cout << "Public key: " << keyPair.first << std::endl;
            // std::cout << "Private key: " << keyPair.second << std::endl;
        }
    } else if (args->pgp) {
        if (args->block_mode) {
            if (input.length() != args->key.length()) {
                std::cerr << "In block mode, MESSAGE and KEY must be of the same size."
                          << "input" << input.length() << "key" << args->key.length() << std::endl;
                return 84;
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
    arguments_t args = {"", false, false, false, false, false, false, false, false, false};

    if (handle_arguments(argc, argv, &args) == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (args.help) {
        return EXIT_SUCCESS;
    }

    // print_arguments(args);

    return handle_input(&args);
}
