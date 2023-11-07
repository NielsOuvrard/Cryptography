Certainly! Here's a README file for your program "mypgp" to explain its usage and functionality:

mypgp - Data Encryption and Decryption Tool

NOMENCLATURE
--------------------------
For ease of use, this tool represents data to be ciphered and encryption keys as sequences of bytes in hexadecimal. Each pair of hexadecimal characters represents a single byte in little-endian order, where the lower byte is on the lower address (left side).

For example, the string "4142434445464748" represents an array of 8 bytes: [65, 66, 67, 68, 69, 70, 71, 72]. A 32-bit integer with the value 1 is represented as: "0100000000", and the hexadecimal number 0x12345678 will be represented as: "78563412".

USAGE
--------------------------
To use mypgp, follow the command line syntax and options described below:

Terminal Command:
∼/B-CNA-500> ./mypgp -h

DESCRIPTION
--------------------------
```
./mypgp [-xor | -aes | -rsa] [-c | -d] [-b] KEY

The MESSAGE is read from standard input.

-xor: Perform encryption/decryption using the XOR algorithm.
-aes: Perform encryption/decryption using the AES algorithm.
-rsa: Perform encryption/decryption using the RSA algorithm.
-c: Indicates that the MESSAGE is clear text and should be ciphered.
-d: Indicates that the MESSAGE is ciphered text and should be deciphered.
-b: Block mode. For XOR and AES algorithms, this mode works on one block only. A block is of the same size as the key. It means the message must be of the same length as the key.

MESSAGE and KEY must be of the same size.

-g P Q: For RSA only, generate a public and private key pair from the prime numbers P and Q.

All symmetric algorithms must accept the "-b" option for block mode. In block mode, only one block will be treated. A block is of the same size as the key. The message must be of the same length as the key.

Without the "-b" modifier, your algorithm must work in stream mode, meaning the message to cipher/decipher can be of any length.

EXAMPLES
--------------------------
Here are some usage examples of the mypgp tool:

- Encrypt a message using XOR:
  ```
  ./mypgp -xor -c -b 4142434445464748
  ```

- Decrypt a message using AES:
  ```
  ./mypgp -aes -d -b 785634121110
  ```

- Generate RSA key pair from prime numbers P and Q:
  ```
  ./mypgp -rsa -g P Q
  ```

Note: Replace the example keys and input data with your actual data when using the tool.

CONTRIBUTIONS
--------------------------
Contributions and bug reports are welcome. If you encounter any issues or have suggestions, please create an issue on the project's GitHub repository.

LICENSE
--------------------------
This program is released under the MIT License. See the LICENSE file for details.

Feel free to modify this README to suit your specific needs, and make sure to include any additional information or details about the tool that may be necessary for users.