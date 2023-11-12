#!/bin/bash

source ./test/function_test.sh

error_encontrado=false

prefix_message="[ ${amarillo}XOR${sin_color} ] "
index=1

test_universal "68656c6c6f20776f726c64" "7665727920736563726574" "-xor -b"
test_universal "832" "7665727dzeez920736563726574" "-xor"
test_universal "34" "2" "-xor"
test_universal "844232" "a" "-xor"
test_universal "838278372" "feer" "-xor"

if [ "$error_encontrado" = false ]; then
    exit 0  # Success
else
    exit 1  # Failure
fi

# XOR
# echo "68656c6c6f20776f726c64" > message

# cat message | ./mypgp -xor -c -b 7665727920736563726574 > ciphered
# 1e001e154f53120c000910

# cat ciphered | ./mypgp -xor -d -b 7665727920736563726574
# 68656c6c6f20776f726c64