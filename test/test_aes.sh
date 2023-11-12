#!/bin/bash

source ./test/function_test.sh

prefix_message="[ ${azul}AES${sin_color} ] "
index=1

test_universal "c2486f4796f0657481a655c559b38aaa" "6b50fd39f06d33cfefe6936430b6c94f" "-aes -b"

if [ "$error_encontrado" = false ]; then
    exit 0  # Success
else
    exit 1  # Failure
fi

# AES
# echo "c2486f4796f0657481a655c559b38aaa" > message

# cat message | ./mypgp -aes -c -b 6b50fd39f06d33cfefe6936430b6c94f > ciphered
# 3c24744d2bc520ecc7144b55ab5fdc85

# cat ciphered | ./mypgp -aes -d -b 6b50fd39f06d33cfefe6936430b6c94f
# c2486f4796f0657481a655c559b38aaa
