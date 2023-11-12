#!/bin/bash

source test/color.sh

error_encontrado=false

# Función para ejecutar pruebas
ejecutar_pruebas() {
    ./test/"$1"

    if [ $? -eq 0 ]; then
        echo -e "${verde}Tests passed successfully!${sin_color}\n"
    else
        echo -e "${rojo}Tests failed.${sin_color}\n"
        error_encontrado=true
    fi
}

ejecutar_pruebas "test_xor.sh"
# ejecutar_pruebas "test_aes.sh"
# ejecutar_pruebas "test_rsa.sh"

echo -e "${verde}Cleaning up...${sin_color}"
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
