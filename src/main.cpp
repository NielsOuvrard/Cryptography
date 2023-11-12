#include "config.hpp"

typedef struct arguments_t {
    std::string key;
    // * algorithm
    bool xor_;
    bool aes;
    bool rsa;
    bool pgp;
    // * mode
    bool encrypt;
    bool decrypt;
    // * options
    bool block_mode;
    bool generate_key;
    int p;
    int q;
    bool help;
} arguments_t;

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
                args->p = std::stoi(argv[++x]);
                args->q = std::stoi(argv[++x]);
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

int handle_input(arguments_t *args)
{
    std::string input;
    std::getline(std::cin, input);
    // std::cout << "input: " << input << std::endl;

    if (args->xor_) {
        if (args->block_mode) {
            if (input.length() != args->key.length()) {
                std::cerr << "In block mode, MESSAGE and KEY must be of the same size."
                          << "input" << input.length() << "key" << args->key.length() << std::endl;
                return 84;
            }
            std::cout << xorEncryptDecrypt(input, args->key) << std::endl;
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

int main(int argc, char *argv[])
{
    arguments_t args = {"", false, false, false, false, false, false, false, false, false};

    if (handle_arguments(argc, argv, &args) == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (args.help) {
        return EXIT_SUCCESS;
    }

    // print_arguments(args);

    handle_input(&args);
    return 0;
}
