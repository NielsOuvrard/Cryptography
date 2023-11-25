#!/bin/bash

source ./test/function_test.sh

error_encontrado=false
prefix_message="[ ${naraja}PGP${sin_color} ] "
index=1

test_universal "b1fa29d40054f3fcb1c15fe4d63d3887" "6b50fd39f06d33cfefe6936430b6c94f" "-pgp"
test_universal "c4fb29a41184f9fc11cc5ff4da3d3887" "6b50fd39f06d33cfefe6936430b6c94f" "-pgp"
test_universal "a1fa29d40054f3fc31912fe4d63c3f31" "6b50fd39f06d33cfefe6936430b6c94f" "-pgp"

if [ "$error_encontrado" = false ]; then
    exit 0  # Success
else
    exit 1  # Failure
fi

