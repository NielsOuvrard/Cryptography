#!/bin/bash

# Run your tests here
./mypgp

# Check if the tests passed and set the exit status accordingly
if [ $? -eq 0 ]; then
  echo "Tests passed successfully!"
  exit 0  # Success
else
  echo "Tests failed."
  exit 1  # Failure
fi