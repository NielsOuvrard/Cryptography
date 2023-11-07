#include <cstdlib>
#include <getopt.h>
#include <iostream>

/**
 *  Main 
 */

void print_usage();
int main(int ac, char **av);

/**
 *  Tools 
 */


/**
 *  Xor 
 */

std::string xorEncryptDecrypt(const std::string &input, const std::string &key);