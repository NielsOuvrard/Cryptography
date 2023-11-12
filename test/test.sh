#!/bin/bash

error_encontrado=false

rojo='\033[0;31m'
verde='\033[0;32m'

sin_color='\033[0m'

# Función para ejecutar pruebas
ejecutar_pruebas() {
    ./test/"$1"

    if [ $? -eq 0 ]; then
        echo -e "${verde}Tests passed successfully!${sin_color}"
    else
        echo -e "${rojo}Tests failed.${sin_color}"
        error_encontrado=true
    fi
}

# Ejecutar pruebas para XOR
ejecutar_pruebas "test_xor.sh"

# Ejecutar pruebas para AES
# ejecutar_pruebas "test_aes.sh"

# Ejecutar pruebas para RSA
# ejecutar_pruebas "test_rsa.sh"

echo -e "\n${verde}Cleaning up...${sin_color}"
for archivo in test/*; do
    if [ "$archivo" ] && [ "${archivo##*.}" != "sh" ]; then
        rm "$archivo"
        echo "Eliminado: $archivo"
    fi
done

if [ "$error_encontrado" = false ]; then
    exit 0  # Success
else
    exit 1  # Failure
fi
