#!/bin/bash

source ./test/function_test_leo.sh

error_encontrado=false
prefix_message="[ ${azul}AES${sin_color} ] "
index=1

# test_universal "c2486f4796f0657481a655c559b38aaa" "6b50fd39f06d33cfefe6936430b6c94f" "-aes -b"
test_universal "193de3bea0f4e22b9ac68d2ae9f84808" "a0fafe1788542cb123a339392a6c7605" "-aes -b"
# test_universal "6b50fd39f06d33cfefe6936430b6c94f" "c2486f4796f0657481a655c559b38aaa" "-aes -b"
# test_universal "3243f6a8885a308d313198a2e0370734" "2b7e151628aed2a6abf7158809cf4f3c" "-aes -b"
# test_universal "2b7e151628aed2a6abf7158809cf4f3c" "3243f6a8885a308d313198a2e0370734" "-aes -b"

if [ "$error_encontrado" = false ]; then
    exit 0  # Success
else
    exit 1  # Failure
fi

# AES
# echo "c2486f4796f0657481a655c559b38aaa" > message

# cat message | ./mypgp -aes -c -b 6b50fd39f06d33cfefe6936430b6c94f > ciphered
# 0fc668acd39462d17272fe863929973a

# cat ciphered | ./mypgp -aes -d -b 6b50fd39f06d33cfefe6936430b6c94f
# c2486f4796f0657481a655c559b38aaa
