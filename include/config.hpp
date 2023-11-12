#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

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

#define EXIT_ERROR 84

#define CHAR_HEX_TO_INT(c) ((c >= '0' && c <= '9') ? (c - '0') : (c - 'a' + 10))
#define INT_TO_CHAR_HEX(i) ((i >= 0 && i <= 9) ? (i + '0') : (i + 'a' - 10))

/**
 *  tools main
 */

void print_usage();
int handle_arguments(int argc, char **argv, arguments_t *args);
void print_arguments(arguments_t args);

/**
 *  Tools
 */

std::string stringToHex(const std::string &input);
std::string hexToString(const std::string &hex);
std::string hexToBinary(std::string hex);
std::string binaryToAscii(std::string binary);
std::string binaryToHex(std::string binary);

/**
 *  Xor
 */

std::string xorEncryptDecrypt(const std::string &input, const std::string &key);

/**
 *  AES
 */

std::string aesEncryptDecrypt(const std::string &input, const std::string &key);