#include "config.hpp"
std::array<uint8_t, 256> sbox = {
        0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
        0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
        0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
        0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
        0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
        0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
        0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
        0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
        0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
        0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
        0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
        0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
        0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
        0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
        0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
        0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

const std::array<uint8_t, 10> Rcon = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

// Function to create a 4x4 matrix from a hexadecimal string
std::array<std::array<uint8_t, 4>, 4> create_map_from_str(const std::string &str) {
    std::array<std::array<uint8_t, 4>, 4> map_map = {0};

    int row = 0;
    int col = 0;
    for (int i = 0; i < 32; i += 2) {
        if (col >= 4) {
            row++;
            col = 0;
        }
        map_map[col][row] = (str[i] <= '9' ? str[i] - '0' : str[i] - 'A' + 10) * 16 +
                            (str[i + 1] <= '9' ? str[i + 1] - '0' : str[i + 1] - 'A' + 10);
        col++;
    }
    return map_map;
}

// Function to perform the multiplication in the finite field GF(2^8)
uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    uint8_t carry;
    for (int i = 0; i < 8; ++i) {
        if (b & 1) {
            p ^= a;
        }
        carry = a & 0x80;
        a <<= 1;
        if (carry) {
            a ^= 0x1B;
        }
        b >>= 1;
    }
    return p;
}

// Function to perform byte substitution (SubBytes)
void sub_byte(std::array<std::array<uint8_t, 4>, 4> &map, const std::array<uint8_t, 256> &sbox) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int row = map[i][j] / 0x10;
            int col = map[i][j] % 0x10;
            map[i][j] = sbox[row * 0x10 + col];
        }
    }
}

// Function to shift the rows of a 4x4 matrix
void shift_rows(std::array<std::array<uint8_t, 4>, 4> &map) {
    for (int i = 1; i < 4; ++i) {
        std::rotate(map[i].begin(), map[i].begin() + i, map[i].end());
    }
}

// Function to mix the columns of a 4x4 matrix
void mix_columns(std::array<std::array<uint8_t, 4>, 4> &map) {
    for (int i = 0; i < 4; ++i) {
        uint8_t a[4];
        for (int j = 0; j < 4; ++j) {
            a[j] = map[j][i];
        }

        map[0][i] = gmul(a[0], 0x02) ^ gmul(a[1], 0x03) ^ a[2] ^ a[3];
        map[1][i] = a[0] ^ gmul(a[1], 0x02) ^ gmul(a[2], 0x03) ^ a[3];
        map[2][i] = a[0] ^ a[1] ^ gmul(a[2], 0x02) ^ gmul(a[3], 0x03);
        map[3][i] = gmul(a[0], 0x03) ^ a[1] ^ a[2] ^ gmul(a[3], 0x02);
    }
}

// Function to add the key (AddRoundKey)
void add_round_key(std::array<std::array<uint8_t, 4>, 4> &map, const std::array<std::array<uint8_t, 4>, 4> &round_key) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            map[i][j] ^= round_key[i][j];
        }
    }
}

// Function to generate the S-Box
void generate_sbox(std::array<uint8_t, 256> &sbox) {
    for (int i = 0; i < 256; ++i) {
        sbox[i] = (i <= 0x7F) ? gmul(i, 0x02) : gmul(i, 0x02) ^ 0x1B;
    }
}

// Function to generate the round key from the main key
void generate_round_key(std::array<std::array<uint8_t, 4>, 4> &round_key,
                        const std::array<std::array<uint8_t, 4>, 4> &main_key, int round,
                        const std::array<uint8_t, 256> &sbox) {
    // Rotate the last column to the top
    std::rotate(round_key[0].begin(), round_key[0].begin() + 1, round_key[0].end());
    std::rotate(round_key[1].begin(), round_key[1].begin() + 1, round_key[1].end());
    std::rotate(round_key[2].begin(), round_key[2].begin() + 1, round_key[2].end());
    std::rotate(round_key[3].begin(), round_key[3].begin() + 1, round_key[3].end());

    // Substitute the bytes using the S-Box
    for (int i = 0; i < 4; ++i) {
        round_key[i][0] = sbox[round_key[i][0]];
    }

    // XOR with the corresponding main key column
    for (int i = 0; i < 4; ++i) {
        round_key[i][0] ^= main_key[i][0];
    }

    // XOR with the round constant for the first byte
    round_key[0][0] ^= Rcon[round];
}

// Function to convert a map to a hexadecimal string
std::string map_to_hex_string(const std::array<std::array<uint8_t, 4>, 4> &map) {
    std::stringstream result;
    for (const auto &row : map) {
        for (const auto &cell : row) {
            result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(cell);
        }
    }
    return result.str();
}

// Function to display a map
void display_map(const std::array<std::array<uint8_t, 4>, 4> &map) {
    for (const auto &row : map) {
        for (const auto &cell : row) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(cell) << ' ';
        }
        std::cout << '\n';
    }
}

// Function to perform AES encryption
std::string aesEncrypt(const std::string &input, const std::string &key) {
    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);
    std::array<std::array<uint8_t, 4>, 4> round_key;

    generate_sbox(const_cast<std::array<uint8_t, 256> &>(sbox));

    add_round_key(input_map, main_key);

    int num_rounds = 10;

    for (int round = 1; round <= num_rounds; ++round) {
        sub_byte(input_map, sbox);
        shift_rows(input_map);
        mix_columns(input_map);

        round_key = main_key;
        generate_round_key(round_key, main_key, round, sbox);

        add_round_key(input_map, round_key);
    }

    sub_byte(input_map, sbox);
    shift_rows(input_map);

    round_key = main_key;
    generate_round_key(round_key, main_key, num_rounds, sbox);

    add_round_key(input_map, round_key);

    return map_to_hex_string(input_map);
}


std::string aesDecrypt(const std::string &input, const std::string &key)
{
    // std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    // std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);
    // std::array<std::array<uint8_t, 4>, 4> round_key;

    // int num_rounds = 10;

    // round_key = main_key;
    // generate_round_key(round_key, main_key, num_rounds, sbox);

    // add_round_key(input_map, round_key);
    // shift_rows(input_map);
    // sub_byte(input_map, sbox);

    // for (int round = num_rounds - 1; round >= 1; --round) {
    //     round_key = main_key;
    //     generate_round_key(round_key, main_key, round, sbox);

    //     add_round_key(input_map, round_key);
    //     inv_mix_columns(input_map);
    //     shift_rows(input_map);
    //     sub_byte(input_map, sbox);
    // }

    // round_key = main_key;
    // add_round_key(input_map, round_key);
    // return map_hex_to_str(input_map);
    return "";
}
