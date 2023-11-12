#!/bin/bash

rojo='\033[0;31m'
verde='\033[0;32m'
amarillo='\033[0;33m'

sin_color='\033[0m'

prefix_message="[ ${amarillo}XOR${sin_color} ] "

error_encontrado=false

function test_xor_1() {
    mensaje="68656c6c6f20776f726c64"
    clave="7665727920736563726574"

    echo "$mensaje" > test/message
    cat test/message | ./mypgp -xor -c -b "$clave" > ciphered

    if [ "$(cat ciphered)" == "1e001e154f53120c000910" ]; then
        echo -e "${prefix_message}test 1.0 ${verde}passed${sin_color}."
    else
        echo -e "${prefix_message}test 1.0 ${rojo}failed${sin_color}."
        error_encontrado=true
    fi
}

test_xor_1

rojo='\033[0;31m'
verde='\033[0;32m'

sin_color='\033[0m'


if [ "$error_encontrado" = false ]; then
    echo -e "${prefix_message}${verde}passed${sin_color}."
    exit 0  # Success
else
    echo -e "${prefix_message}${rojo}failed${sin_color}."
    exit 1  # Failure
fi
