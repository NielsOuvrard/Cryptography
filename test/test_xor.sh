echo "68656c6c6f20776f726c64" > test/message
cat test/message | ./mypgp -xor -c -b 7665727920736563726574 > ciphered

if [ "$(cat ciphered)" == "1e001e154f53120c000910" ]; then
  echo "XOR test passed successfully!"
  exit 0  # Success
else
  echo "XOR test failed."
  exit 1  # Failure
fi