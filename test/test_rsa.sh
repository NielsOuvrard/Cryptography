#!/bin/bash

rojo='\033[0;31m'
verde='\033[0;32m'
amarillo='\033[0;33m'

sin_color='\033[0m'

prefix_message="[ ${amarillo}RSA${sin_color} ] "

error_encontrado=false

function test_rsa_1() {
    mensaje="$1"
    clave="$2"

    echo "$mensaje" > test/message
    cat test/message | ./mypgp -rsa -c "$clave" > test/ciphered

    if [ "$(cat test/ciphered)" == "b104" ]; then
        echo -e "${prefix_message}test 1.0 ${verde}passed${sin_color}."

        cat test/ciphered | ./mypgp -rsa -d "$clave" > test/deciphered

        if [ "$(cat test/deciphered)" == "$mensaje" ]; then
            echo -e "${prefix_message}test 1.5 ${verde}passed${sin_color}."
        else
            echo -e "${prefix_message}test 1.5 ${rojo}failed${sin_color}."
            error_encontrado=true
        fi
    else
        echo -e "${prefix_message}test 1.0 ${rojo}failed${sin_color}."
        error_encontrado=true
    fi
}

test_rsa_1 "2a" "010001-19bb"

if [ "$error_encontrado" = false ]; then
    echo -e "${prefix_message}${verde}passed${sin_color}."
    exit 0  # Success
else
    echo -e "${prefix_message}${rojo}failed${sin_color}."
    exit 1  # Failure
fi

# RSA
# echo "2a" > message

# cat message | ./mypgp -rsa -c 010001-19bb > ciphered
# b104

# cat ciphered | ./mypgp -rsa -d 81b3-19bb
# 2a