#include "config.hpp"

void print_usage()
{
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

<<<<<<< HEAD:main.cpp
int main (int argc, char* argv[]) {
=======
int main(int argc, char *argv[])
{
    int option;
>>>>>>> 7595112ec086e6540289f60bb640586c77d08e8d:src/main.cpp
    bool xor_flag = false;
    bool aes_flag = false;
    bool rsa_flag = false;
    bool encrypt_flag = false;
    bool decrypt_flag = false;
    bool block_mode_flag = false;
    bool generate_key_flag = false;
    std::string key;
    std::string input = argv[argc - 1];

    for (int x = 1; argv[x][0] == '-'; x++) {
        std::string arg = argv[x];
        if ("-xor" == arg) {
            xor_flag = true;
            break;
        }
        if ("-aes" == arg) {
            aes_flag = true;
            break;
        }
        if ("-rsa" == arg) {
            rsa_flag = true;
            break;
        }
        if ("-c" == arg) {
            encrypt_flag = true;
            break;
        }
        if ("-d" == arg) {
            decrypt_flag = true;
            break;
        }
        if ("-b" == arg) {
            block_mode_flag = true;
            if (!xor_flag && !aes_flag) {
                std::cerr << "Block mode (-b) is only valid for -xor and -aes." << std::endl;
                exit(EXIT_FAILURE);
            }
            break;
        }
        if ("-help" == arg || "-h" == arg) {
            print_usage();
            exit(EXIT_SUCCESS);
        }
        std::cerr << "Invalid option. Use -h for help." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "xor_flag: " << xor_flag << std::endl;
    std::cout << "aes_flag: " << aes_flag << std::endl;
    std::cout << "rsa_flag: " << rsa_flag << std::endl;
    std::cout << "encrypt_flag: " << encrypt_flag << std::endl;
    std::cout << "decrypt_flag: " << decrypt_flag << std::endl;
    std::cout << "block_mode_flag: " << block_mode_flag << std::endl;
    std::cout << "generate_key_flag: " << generate_key_flag << std::endl;
    std::cout << "key: " << key << std::endl;
    std::cout << "input: " << input << std::endl;

    if (!xor_flag && !aes_flag && !rsa_flag) {
        std::cerr << "Select an encryption algorithm (-xor, -aes, -rsa)." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!encrypt_flag && !decrypt_flag) {
        std::cerr << "Specify whether to encrypt (-c) or decrypt (-d) the message." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (encrypt_flag && decrypt_flag) {
        std::cerr << "Specify either -c (encryption) or -d (decryption), not both." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        key = argv[optind];
    }
    else {
        std::cerr << "KEY is required. Use -h for help." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (xor_flag && !block_mode_flag) {
        xorEncryptDecrypt(input, key);
    }

    return 0;
}