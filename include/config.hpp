#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <bitset>


/**
 *  Main 
 */

void print_usage();
int main(int ac, char **av);

/**
 *  Tools 
 */

std::string stringToHex(const std::string& input);
std::string hexToString(const std::string& hex);
std::string hexToBinary(std::string hex);
std::string binaryToAscii(std::string binary);
std::string binaryToHex(std::string binary);

/**
 *  Xor 
 */

std::string xorEncrypt(const std::string& message, const std::string& key);
std::string xorDecrypt(const std::string& encryptedMessage, const std::string& key);
std::string xorEncryptDecrypt(const std::string& input, const std::string& key);