#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <boost/multiprecision/cpp_int.hpp>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

namespace bm = boost::multiprecision;

using inf_int = bm::cpp_int;

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
    std::string p;
    std::string q;
    bool help;
} arguments_t;

#define EXIT_ERROR 84

#define CHAR_HEX_TO_INT(c) ((c >= '0' && c <= '9') ? (c - '0') : (c - 'a' + 10))
#define INT_TO_CHAR_HEX(i) ((i >= 0 && i <= 9) ? (i + '0') : (i + 'a' - 10))

/**
 *  tools main
 */

int handle_arguments(int argc, char **argv, arguments_t *args);
void print_arguments(arguments_t args);

inf_int str_hexa_to_int(std::string str);
std::string int_to_str_hexa(inf_int n);

/**
 *  Xor
 */

std::string xorEncryptDecrypt(const std::string &input, const std::string &key);

/**
 *  AES
 */

std::string aesEncrypt(const std::string &input, const std::string &key);
std::string aesDecrypt(const std::string &input, const std::string &key);

/**
 *  RSA
 */

std::string inverse_two_by_two(std::string value);
std::string inverse_two_by_two_rev(std::string value);

void generateKeyPair(std::string p, std::string q);

std::string rsaEncrypt(std::string input, std::pair<inf_int, inf_int> keyPair);
std::string rsaDecrypt(std::string input, std::pair<inf_int, inf_int> keyPair);

/**
 *  PGP
 */

std::string pgpEncrypt(const std::string &message, const std::string &key);
std::string pgpDecrypt(const std::string &encryptedMessage, const std::string &key);