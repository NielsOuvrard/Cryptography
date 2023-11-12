#!/bin/bash

# Run your tests here

./test/test_xor.sh
./test/test_aes.sh

rojo='\033[0;31m'
verde='\033[0;32m'

sin_color='\033[0m'


# Check if the tests passed and set the exit status accordingly
if [ $? -eq 0 ]; then
    echo -e "${verde}Tests passed successfully!${sin_color}"
    exit 0  # Success
else
    echo -e "${rojo}Tests failed.${sin_color}"
    exit 1  # Failure
fi



# XOR
# echo "68656c6c6f20776f726c64" > message

# cat message | ./mypgp -xor -c -b 7665727920736563726574 > ciphered
# 1e001e154f53120c000910

# cat ciphered | ./mypgp -xor -d -b 7665727920736563726574
# 68656c6c6f20776f726c64


# AES
# echo "c2486f4796f0657481a655c559b38aaa" > message

# cat message | ./mypgp -aes -c -b 6b50fd39f06d33cfefe6936430b6c94f > ciphered
# 3c24744d2bc520ecc7144b55ab5fdc85

# cat ciphered | ./mypgp -aes -d -b 6b50fd39f06d33cfefe6936430b6c94f
# c2486f4796f0657481a655c559b38aaa


# RSA
# echo "2a" > message

# cat message | ./mypgp -rsa -c 010001-19bb > ciphered
# b104

# cat ciphered | ./mypgp -rsa -d 81b3-19bb
# 2a