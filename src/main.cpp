#include "config.hpp"

inf_int read_from_little_endian(std::string str)
{
    inf_int res = 0;
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
            if (args->encrypt)
                std::cout << aesEncrypt(input, args->key) << std::endl;
            else if (args->decrypt)
                std::cout << aesDecrypt(input, args->key) << std::endl;
            else
                std::cerr << "Error: no mode selected" << std::endl;
        }
    } else if (args->rsa) {
        std::pair<inf_int, inf_int> keyPair;
        keyPair.first = str_hexa_to_int(inverse_two_by_two_rev(args->key.substr(0, args->key.find("-"))));
        keyPair.second = str_hexa_to_int(inverse_two_by_two_rev(args->key.substr(args->key.find("-") + 1, args->key.length())));
        if (args->encrypt) {
            std::cout << rsaEncrypt(input, keyPair) << std::endl;
        } else if (args->decrypt) {
            std::cout << rsaDecrypt(input, keyPair) << std::endl;
        } else {
            std::cerr << "Error: no mode selected" << std::endl;
        }
    } else if (args->pgp) {
        if (args->encrypt)
            std::cout << pgpEncrypt(input, args->key) << std::endl;
        else if (args->decrypt)
            std::cout << pgpDecrypt(input, args->key) << std::endl;
        else
            std::cerr << "Error: no mode selected" << std::endl;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    arguments_t args = {"", false, false, false, false, false, false, false, false, "", "", false};

    if (handle_arguments(argc, argv, &args) == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (args.help) {
        return EXIT_SUCCESS;
    }

    return handle_input(&args);
}
