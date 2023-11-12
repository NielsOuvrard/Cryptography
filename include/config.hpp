#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


#define EXIT_ERROR 84

/**
 *  Main 
 */

void print_usage();
int main(int ac, char **av);

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

#define CHAR_HEX_TO_INT(c) ((c >= '0' && c <= '9') ? (c - '0') : (c - 'a' + 10))
#define INT_TO_CHAR_HEX(i) ((i >= 0 && i <= 9) ? (i + '0') : (i + 'a' - 10))
