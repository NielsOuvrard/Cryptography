#!/bin/bash


rojo='\033[0;31m'
verde='\033[0;32m'
azul='\033[0;34m'

sin_color='\033[0m'

prefix_message="[ ${azul}AES${sin_color} ] "

error_encontrado=false

function test_aes_1() {
    mensaje="$1"
    clave="$2"

    echo "$mensaje" > test/message
    cat test/message | ./mypgp -aes -c -b "$clave" > test/ciphered

    if [ "$(cat test/ciphered)" != "0fc668acd39462d17272fe863929973a" ]; then
        error_encontrado=true
        echo -e "${prefix_message}test 1.0 ${rojo}failed${sin_color}."
    else
        echo -e "${prefix_message}test 1.0 ${verde}passed${sin_color}."

        cat test/ciphered | ./mypgp -aes -d -b "$clave" > test/deciphered
        if [ "$(cat test/deciphered)" == "$mensaje" ]; then
            echo -e "${prefix_message}test 1.1 ${verde}passed${sin_color}."
        else
            echo -e "${prefix_message}test 1.1 ${rojo}failed${sin_color}."
            error_encontrado=true
        fi
    fi
}

test_aes_1 "c2486f4796f0657481a655c559b38aaa" "6b50fd39f06d33cfefe6936430b6c94f"

if [ "$error_encontrado" = false ]; then
    echo -e "${prefix_message}${verde}passed${sin_color}."
    exit 0  # Success
else
    echo -e "${prefix_message}${rojo}failed${sin_color}."
    exit 1  # Failure
fi

# AES
# echo "c2486f4796f0657481a655c559b38aaa" > message

# cat message | ./mypgp -aes -c -b 6b50fd39f06d33cfefe6936430b6c94f > ciphered
# 3c24744d2bc520ecc7144b55ab5fdc85

# cat ciphered | ./mypgp -aes -d -b 6b50fd39f06d33cfefe6936430b6c94f
# c2486f4796f0657481a655c559b38aaa
