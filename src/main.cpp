#include "../include/config.hpp"

void print_usage () {
    std::cout << "USAGE" << std::endl;
    std::cout << "  ./mypgp [-xor | -aes | -rsa] [-c | -d] [-b] KEY" << std::endl;
    std::cout << "  the MESSAGE is read from standard input" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "  -xor        computation using XOR algorithm" << std::endl;
    std::cout << "  -aes        computation using AES algorithm" << std::endl;
    std::cout << "  -rsa        computation using RSA algorithm" << std::endl;
    std::cout << "  -c          MESSAGE is clear and we want to cipher it" << std::endl;
    std::cout << "  -d          MESSAGE is ciphered and we want to decipher it" << std::endl;
    std::cout << "  -b          block mode: for xor and aes, only works on one block" << std::endl;
    std::cout << "              MESSAGE and KEY must be of the same size" << std::endl;
    std::cout << "  -g P Q      for RSA only: generate a public and private key pair from the prime number P and Q" << std::endl;
}

int main (int argc, char* argv[]) {
    bool xor_flag = false;
    bool aes_flag = false;
    bool rsa_flag = false;
    bool encrypt_flag = false;
    bool decrypt_flag = false;
    bool block_mode_flag = false;
    bool generate_key_flag = false;
    std::string key = argv[argc - 1];

    for (int x = 1; argv[x][0] == '-'; x++) {
        // std::cout << "argv[" << x << "]: " << argv[x] << std::endl;
        std::string arg = argv[x];
        if ("-xor" == arg) 
            xor_flag = true;
        if ("-aes" == arg) 
            aes_flag = true;
        if ("-rsa" == arg) 
            rsa_flag = true;
        if ("-c" == arg) 
            encrypt_flag = true;
        if ("-d" == arg) 
            decrypt_flag = true;
        if ("-b" == arg) {
            block_mode_flag = true;
            if (!xor_flag && !aes_flag) {
                std::cerr << "Block mode (-b) is only valid for -xor and -aes." << std::endl;
                exit(84);
            }
        }
        if ("-help" == arg || "-h" == arg) {
            print_usage();
            exit(EXIT_SUCCESS);
        }
        // std::cerr << "Invalid option. Use -h for help." << std::endl;
        // exit(84);
    }
    
    // std::cout << "xor_flag: " << xor_flag << std::endl;
    // std::cout << "aes_flag: " << aes_flag << std::endl;
    // std::cout << "rsa_flag: " << rsa_flag << std::endl;
    // std::cout << "encrypt_flag: " << encrypt_flag << std::endl;
    // std::cout << "decrypt_flag: " << decrypt_flag << std::endl;
    // std::cout << "block_mode_flag: " << block_mode_flag << std::endl;
    // std::cout << "generate_key_flag: " << generate_key_flag << std::endl;
    std::cout << "key:   " << key << std::endl;

    if (!xor_flag && !aes_flag && !rsa_flag) {
        std::cerr << "Select an encryption algorithm (-xor, -aes, -rsa)." << std::endl;
        exit(84);
    }

    // pas de block mode pour rsa

    if (!encrypt_flag && !decrypt_flag) {
        std::cerr << "Specify whether to encrypt (-c) or decrypt (-d) the message." << std::endl;
        exit(84);
    }

    if (encrypt_flag && decrypt_flag) {
        std::cerr << "Specify either -c (encryption) or -d (decryption), not both." << std::endl;
        exit(84);
    }

    if (optind < argc) {
        key = argv[optind];
    } else {
        std::cerr << "KEY is required. Use -h for help." << std::endl;
        exit(84);
    }

    std::string input;
    std::getline(std::cin, input);
    std::cout << "input: " << input << std::endl;

    if (xor_flag) {
        if (block_mode_flag) {
            if (input.length() != key.length()) {
                std::cerr << "In block mode, MESSAGE and KEY must be of the same size." << "input" << input.length() << "key" << key.length() << std::endl;
                return 84;
            }
        }
    // std::string key1 = "68656c6c6f20776f726c64";  // "hello world" in ASCII
    // std::string message = "74657374206d657373616765";  // "test message" in ASCII

    // // Convert key1 and message to binary
    // std::string binaryKey = hexToBinary(key1);
    // std::string binaryMessage = hexToBinary(message);

    // // Encrypt
    // std::string encrypted = xorEncryptDecrypt(binaryMessage, binaryKey);

    // // Decrypt
    // std::string decrypted = xorEncryptDecrypt(encrypted, binaryKey);

    // // Print results
    // std::cout << "Encrypted: " << encrypted << std::endl;
    // std::cout << "Decrypted: " << binaryToAscii(decrypted) << std::endl;

    }

    return 0;
}
