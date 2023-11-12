#!/bin/bash

# Run your tests here
./test/test_xor.sh
./test/test_aes.sh

rojo='\033[0;31m'
verde='\033[0;32m'

sin_color='\033[0m'


# TODO: Check if the tests passed and set the exit status accordingly
if [ $? -eq 0 ]; then
    echo -e "${verde}Tests passed successfully!${sin_color}"
else
    echo -e "${rojo}Tests failed.${sin_color}"
fi


echo -e "\n${verde}Cleaning up...${sin_color}"
for archivo in test/*; do
    if [ "$archivo" ] && [ "${archivo##*.}" != "sh" ]; then
        rm "$archivo"
        echo "Eliminado: $archivo"
    fi
done

# # TODO: Check if the tests passed and set the exit status accordingly
# if [ $? -eq 0 ]; then
#     exit 0  # Success
# else
#     exit 1  # Failure
# fi

# RSA
# echo "2a" > message

# cat message | ./mypgp -rsa -c 010001-19bb > ciphered
# b104

# cat ciphered | ./mypgp -rsa -d 81b3-19bb
# 2a