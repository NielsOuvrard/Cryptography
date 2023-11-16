#!/bin/bash

source ./test/function_test.sh

error_encontrado=false
prefix_message="[ ${viola}RSA${sin_color} ] "
index=1

test_universal "2a" "010001-19bb" "-rsa"

if [ "$error_encontrado" = false ]; then
    exit 0  # Success
else
    exit 1  # Failure
fi

# RSA
# echo "2a" > message

# cat message | ./mypgp -rsa -c 010001-19bb > ciphered
# b104

# cat ciphered | ./mypgp -rsa -d 81b3-19bb
# 2a



# * ∼/B-CNA-500> ./mypgp -rsa -g 4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1 bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb
# public key: 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3
# private key: 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3

# * ∼/B-CNA-500> echo "c1fa29d40054f3fcb1c15fe4d63d3887" > message
# * ∼/B-CNA-500> cat message | ./mypgp -rsa -c 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3 > ciphered
# * ∼/B-CNA-500> cat ciphered
# dc0bd7367d04e5a9e9e14467ff38de0625b3cfa5aabbe86def48bfc93e97aab713d70abf83d263a6dd6570c6d297cc44bad2e0dd2cf7b4c3e0a9749d68ca11a8
# * ∼/B-CNA-500> cat ciphered | ./mypgp -rsa -d 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3
# c1fa29d40054f3fcb1c15fe4d63d3887
