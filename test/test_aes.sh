#!/bin/bash


rojo='\033[0;31m'
verde='\033[0;32m'
azul='\033[0;34m'

sin_color='\033[0m'

prefix_message="[ ${azul}AES${sin_color} ] "

error_encontrado=false

function test_aes_1() {
    mensaje="c2486f4796f0657481a655c559b38aaa"
    clave="6b50fd39f06d33cfefe6936430b6c94f"

    echo "$mensaje" > test/message
    cat test/message | ./mypgp -aes -c -b "$clave" > ciphered

    if [ "$(cat ciphered)" != "0fc668acd39462d17272fe863929973a" ]; then
        error_encontrado=true
        echo -e "${prefix_message}test 1.0 ${rojo}failed${sin_color}."
    else
        echo -e "${prefix_message}test 1.0 ${verde}passed${sin_color}."

        cat ciphered | ./mypgp -aes -d -b "$clave" > deciphered
        if [ "$(cat deciphered)" == "$mensaje" ]; then
            echo -e "${prefix_message}test 1.1 ${verde}passed${sin_color}."
        else
            echo -e "${prefix_message}test 1.1 ${rojo}failed${sin_color}."
            error_encontrado=true
        fi
    fi
}

test_aes_1



if [ "$error_encontrado" = false ]; then
    echo -e "${prefix_message}${verde}passed${sin_color}."
    exit 0  # Success
else
    echo -e "${prefix_message}${rojo}failed${sin_color}."
    exit 1  # Failure
fi
