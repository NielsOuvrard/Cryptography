# Cryptography

Data Encryption and Decryption Tool

## NOMENCLATURE

For ease of use, this tool represents data to be ciphered and encryption keys as sequences of bytes in hexadecimal. Each pair of hexadecimal characters represents a single byte in little-endian order, where the lower byte is on the lower address (left side).

For example, the string `4142434445464748` represents an array of 8 bytes: [65, 66, 67, 68, 69, 70, 71, 72]. A 32-bit integer with the value 1 is represented as: `0100000000`, and the hexadecimal number `0x12345678` will be represented as: `78563412`.

## USAGE

To compile, you need to install `boost` library:

```bash
# Ubuntu
∼/Cryptography> sudo apt-get install libboost-all-dev

# Mac OS
∼/Cryptography> brew install boost

# Windows
∼/Cryptography> choco install boost
```

To use mypgp, follow the command line syntax and options described below:

Terminal Command:

```bash
∼/Cryptography> ./mypgp -h
```

## DESCRIPTION

```
./mypgp [-xor | -aes | -rsa | -pgp] [-c | -d] [-b] [KEY]
```

> The **MESSAGE** is read from standard input.

- `xor`: Perform encryption/decryption using the XOR algorithm.
- `aes`: Perform encryption/decryption using the AES algorithm.
- `rsa`: Perform encryption/decryption using the RSA algorithm.
- `pgp`: Perform encryption/decryption using both the RSA and AES algorithms.
- `c`: Indicates that the **MESSAGE** is clear text and should be ciphered.
- `d`: Indicates that the **MESSAGE** is ciphered text and should be deciphered.
- `b`: Block mode. For XOR and AES algorithms, this mode works on one block only. A block is of the same size as the key. It means the **message** must be of the same length as the key. **MESSAGE** and KEY must be of the same size.
- `g` `P` `Q`: For RSA only, generate a public and private key pair from the prime numbers P and Q.

> [!NOTE]\
>  All symmetric algorithms must accept the "-b" option for block mode. In block mode, only one block will be treated. A block is of the same size as the key. The message must be of the same length as the key.

Without the "-b" modifier, your algorithm must work in stream mode, meaning the message to cipher/decipher can be of any length.

## EXAMPLES

Here are some usage examples of the mypgp tool:

- Encrypt a message using XOR:

  ```bash
  cat message | ./mypgp -xor -c -b 4142434445464748
  ```

- Decrypt a message using AES:

  ```bash
  cat message | ./mypgp -aes -d -b 785634121110
  ```

- Generate RSA key pair from prime numbers P and Q:

  ```bash
  cat message | ./mypgp -rsa -g P Q
  ```

- Encrypt a message using PGP:
  ```bash
  cat message | ./mypgp -pgp -c -b 4142434445464748
  ```

## Unit Testing

To run the unit tests, follow the command line syntax and options described below:

Terminal Command:

```bash
∼/Cryptography> make test
```

the output should be:

```bash
[ XOR ] test 1.0 passed,   ciphered : 1e001e154f53120c000910
[ XOR ] test 1.5 passed, deciphered : 68656c6c6f20776f726c64
...
Tests passed successfully!

[ AES ] test 1.0 passed,   ciphered : 0449b86c61084ddf8f7756e27454acc8
[ AES ] test 1.5 passed, deciphered : c2416f4796f06574
...
Tests passed successfully!

[ RSA ] test 1.0 passed, ciphered:dc0bd7367d04e5a9e9e14467ff38de0625b3cfa5aabbe86def48bfc93e97aab713d70abf83d263a6dd6570c6d297cc44bad2e0dd2cf7b4c3e0a9749d68ca11a8
[ RSA ] test 1.5 passed.
...
Tests passed successfully!

[ PGP ] test 1.0 passed, ciphered:2518577e4c5b43f39200c83d8a388387e65cfad2bca86b6400a6b2ec7797babe819004a1005efa34af011147fd994d2d80239a846cff8672025927674661c1456e9838c0daec43e6e71305cf6cfa6b7b
[ PGP ] test 1.5 passed.
...
Tests passed successfully!

Cleaning up...
Eliminado: test/ciphered
Eliminado: test/deciphered
Eliminado: test/message
```

Note: Replace the example keys and input data with your actual data when using the tool.
