
#include "config.hpp"

void print_usage()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "  ./mypgp [-xor | -aes | -rsa | -pgp] [-c | -d] [-b] KEY" << std::endl;
    std::cout << "  the MESSAGE is read from standard input" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "  -xor        computation using XOR algorithm" << std::endl;
    std::cout << "  -aes        computation using AES algorithm" << std::endl;
    std::cout << "  -rsa        computation using RSA algorithm" << std::endl;
    std::cout << "  -pgp        computation using both RSA and AES algorithm" << std::endl;
    std::cout << "  -c          MESSAGE is clear and we want to cipher it" << std::endl;
    std::cout << "  -d          MESSAGE is ciphered and we want to decipher it" << std::endl;
    std::cout << "  -b          block mode: for xor and aes, only works on one block" << std::endl;
    std::cout << "              MESSAGE and KEY must be of the same size" << std::endl;
    std::cout << "  -g P Q      for RSA only: generate a public and private key pair from the prime number P and Q" << std::endl;
}

uint64_t str_hexa_to_int(std::string str)
{
    uint64_t res = 0;
    for (int i = 0; i < str.length(); i++) {
        res = res * 16 + CHAR_HEX_TO_INT(str[i]);
    }
    return res;
}

std::string int_to_str_hexa(uint64_t n)
{
    std::string res = "";
    while (n > 0) {
        res = static_cast<char>(INT_TO_CHAR_HEX(n % 16)) + res;
        n /= 16;
    }
    return res;
}

int handle_arguments(int argc, char **argv, arguments_t *args)
{
    if (argc < 2) {
        std::cerr << "Invalid number of arguments. Use -h for help." << std::endl;
        return EXIT_ERROR;
    }
    args->key = argv[argc - 1];

    for (int x = 1; argv[x] != NULL; x++) {
        if (argv[x][0] != '-') {
            break;
        }
        switch (argv[x][1]) {
            case 'x':
                args->xor_ = true;
                break;
            case 'a':
                args->aes = true;
                break;
            case 'r':
                args->rsa = true;
                break;
            case 'p':
                args->pgp = true;
                break;
            case 'c':
                args->encrypt = true;
                break;
            case 'd':
                args->decrypt = true;
                break;
            case 'b':
                args->block_mode = true;
                break;
            case 'g':
                args->generate_key = true;
                if (argc < x + 3) {
                    std::cerr << "Invalid number of arguments. Use -h for help." << std::endl;
                    return EXIT_ERROR;
                }
                // todo : in hex
                args->p = argv[++x];
                args->q = argv[++x];
                break;
            case 'h':
                args->help = true;
                print_usage();
                return EXIT_SUCCESS;
            default:
                std::cerr << "Invalid option. Use -h for help." << std::endl;
                return EXIT_ERROR;
        }
    }

    if ((!args->xor_ && !args->aes) && args->block_mode) {
        std::cerr << "Block mode (-b) is only valid for -xor and -aes." << std::endl;
        return EXIT_ERROR;
    }

    if (!args->xor_ && !args->aes && !args->rsa && !args->pgp) {
        std::cerr << "Select only one encryption algorithm (-xor, -aes, -rsa, -pgp)." << std::endl;
        return EXIT_ERROR;
    }

    if (!args->generate_key) {
        if (!args->encrypt && !args->decrypt) {
            std::cerr << "Specify whether to encrypt (-c) or decrypt (-d) the message." << std::endl;
            return EXIT_ERROR;
        } else if (args->encrypt && args->decrypt) {
            std::cerr << "Specify either -c (encryption) or -d (decryption), not both." << std::endl;
            return EXIT_ERROR;
        }
        // if() {
        //     std::cerr << "KEY is required. Use -h for help." << std::endl;
        //     return EXIT_ERROR;
        // }
    }
    return EXIT_SUCCESS;
}


void print_arguments(arguments_t args)
{
    std::cout << "Key: " << args.key << std::endl;

    std::cout << "XOR: " << args.xor_ << std::endl;
    std::cout << "AES: " << args.aes << std::endl;
    std::cout << "RSA: " << args.rsa << std::endl;
    std::cout << "PGP: " << args.pgp << std::endl
              << std::endl;

    std::cout << "Encrypt: " << args.encrypt << std::endl;
    std::cout << "Decrypt: " << args.decrypt << std::endl
              << std::endl;

    std::cout << "Block Mode: " << args.block_mode << std::endl;
    std::cout << "Generate Key: " << args.generate_key << std::endl;
    std::cout << "P: " << args.p << std::endl;
    std::cout << "Q: " << args.q << std::endl;
}
