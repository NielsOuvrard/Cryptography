#!/bin/bash

source ./test/function_test.sh

error_encontrado=false
prefix_message="[ ${viola}RSA${sin_color} ] "
index=1

test_universal "2a" "010001-19bb" "-rsa"

if [ "$error_encontrado" = false ]; then
    exit 0  # Success
else
    exit 1  # Failure
fi

# RSA
# echo "2a" > message

# cat message | ./mypgp -rsa -c 010001-19bb > ciphered
# b104

# cat ciphered | ./mypgp -rsa -d 81b3-19bb
# 2a