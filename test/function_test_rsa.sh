#!/bin/bash

source test/color.sh

function test_rsa() {
    mensaje="$1"
    clave_public="$2"
    argumentos="$3"
    clave_private="$4"

    echo "$mensaje" > test/message
    cat test/message | ./mypgp $argumentos -c "$clave_public" > test/ciphered

    if [ $? -eq 0 ]; then
        printf "${prefix_message}test ${index}.0 ${verde}passed${sin_color}, ciphered:"
        printf "%s\n" "$(cat test/ciphered)\n"

        cat test/ciphered | ./mypgp $argumentos -d "$clave_private" > test/deciphered

        if [ "$(cat test/deciphered)" == "$mensaje" ]; then
            echo -e "${prefix_message}test ${index}.5 ${verde}passed${sin_color}."
        else
            echo -e "${prefix_message}test ${index}.5 ${rojo}failed${sin_color}."
            echo -e "$(cat test/deciphered) != $mensaje"
            error_encontrado=true
        fi
    else
        echo -e "${prefix_message}test ${index}.0 ${rojo}failed${sin_color}."
        error_encontrado=true
    fi
    index=$((index+1))
}
