#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


#define EXIT_FAILURE 84

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
