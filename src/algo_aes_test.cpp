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

std::array<uint8_t, 256> sbox_transposed = {
        0x63, 0xCA, 0xB7, 0x04, 0x09, 0x53, 0xD0, 0x51, 0xCD, 0x60, 0xE0, 0xE7, 0xBA, 0x70, 0xE1, 0x8C, 
        0x7C, 0x82, 0xFD, 0xC7, 0x83, 0xD1, 0xEF, 0xA3, 0x0C, 0x81, 0x32, 0xC8, 0x78, 0x3E, 0xF8, 0xA1, 
        0x77, 0xC9, 0x93, 0x23, 0x2C, 0x00, 0xAA, 0x40, 0x13, 0x4F, 0x3A, 0x37, 0x25, 0xB5, 0x98, 0x89, 
        0x7B, 0x7D, 0x26, 0xC3, 0x1A, 0xED, 0xFB, 0x8F, 0xEC, 0xDC, 0x0A, 0x6D, 0x2E, 0x66, 0x11, 0x0D, 
        0xF2, 0xFA, 0x36, 0x18, 0x1B, 0x20, 0x43, 0x92, 0x5F, 0x22, 0x49, 0x8D, 0x1C, 0x48, 0x69, 0xBF, 
        0x6B, 0x59, 0x3F, 0x96, 0x6E, 0xFC, 0x4D, 0x9D, 0x97, 0x2A, 0x06, 0xD5, 0xA6, 0x03, 0xD9, 0xE6,
        0x6F, 0x47, 0xF7, 0x05, 0x5A, 0xB1, 0x33, 0x38, 0x44, 0x90, 0x24, 0x4E, 0xB4, 0xF6, 0x8E, 0x42, 
        0xC5, 0xF0, 0xCC, 0x9A, 0xA0, 0x5B, 0x85, 0xF5, 0x17, 0x88, 0x5C, 0xA9, 0xC6, 0x0E, 0x94, 0x68, 
        0x30, 0xAD, 0x34, 0x07, 0x52, 0x6A, 0x45, 0xBC, 0xC4, 0x46, 0xC2, 0x6C, 0xE8, 0x61, 0x9B, 0x41, 
        0x01, 0xD4, 0xA5, 0x12, 0x3B, 0xCB, 0xF9, 0xB6, 0xA7, 0xEE, 0xD3, 0x56, 0xDD, 0x35, 0x1E, 0x99, 
        0x67, 0xA2, 0xE5, 0x80, 0xD6, 0xBE, 0x02, 0xDA, 0x7E, 0xB8, 0xAC, 0xF4, 0x74, 0x57, 0x87, 0x2D, 
        0x2B, 0xAF, 0xF1, 0xE2, 0xB3, 0x39, 0x7F, 0x21, 0x3D, 0x14, 0x62, 0xEA, 0x1F, 0xB9, 0xE9, 0x0F, 
        0xFE, 0x9C, 0x71, 0xEB, 0x29, 0x4A, 0x50, 0x10, 0x64, 0xDE, 0x91, 0x65, 0x4B, 0x86, 0xCE, 0xB0, 
        0xD7, 0xA4, 0xD8, 0x27, 0xE3, 0x4C, 0x3C, 0xFF, 0x5D, 0x5E, 0x95, 0x7A, 0xBD, 0xC1, 0x55, 0x54, 
        0xAB, 0x72, 0x31, 0xB2, 0x2F, 0x58, 0x9F, 0xF3, 0x19, 0x0B, 0xE4, 0xAE, 0x8B, 0x1D, 0x28, 0xBB, 
        0x76, 0xC0, 0x15, 0x75, 0x84, 0xCF, 0xA8, 0xD2, 0x73, 0xDB, 0x79, 0x08, 0x8A, 0x9E, 0xDF, 0x16
};

const std::array<uint8_t, 10> Rcon = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

// Function to convert a hexadecimal character to its corresponding 4-bit value
uint8_t hexCharToValue(char c) {
    if (c >= '0' && c <= '9') {
        return static_cast<uint8_t>(c - '0');
    } else if (c >= 'a' && c <= 'f') {
        return static_cast<uint8_t>(c - 'a' + 10);
    } else if (c >= 'A' && c <= 'F') {
        return static_cast<uint8_t>(c - 'A' + 10);
    } else {
        // Handle invalid characters
        throw std::invalid_argument("Invalid hexadecimal character");
    }
}

// Function to display a map
void display_map(const std::array<std::array<uint8_t, 4>, 4> &map) {
    std::cout << '\n';
    std::cout << '\n';
    for (const auto &row : map) {
        for (const auto &cell : row) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(cell) << ' ';
        }
        std::cout << '\n';
    }
}

// Function to convert a substring of length 2 to a uint8_t
uint8_t stringTobits(const std::string &substring) {
    if (substring.length() != 2) {
        // Handle invalid input length
        throw std::invalid_argument("Invalid substring length. Must be 2 characters.");
    }

    uint8_t result = 0;

    for (size_t i = 0; i < 2; ++i) {
        result |= hexCharToValue(substring[i]) << (4 * (1 - i));
    }

    return result;
}

// Function to create a 4x4 matrix from a hexadecimal string
std::array<std::array<uint8_t, 4>, 4> create_map_from_str(const std::string &str) {
    return {{
        stringTobits(str.substr(0, 2)), stringTobits(str.substr(8, 2)), stringTobits(str.substr(16, 2)), stringTobits(str.substr(24, 2)),
        stringTobits(str.substr(2, 2)), stringTobits(str.substr(10, 2)), stringTobits(str.substr(18, 2)), stringTobits(str.substr(26, 2)),
        stringTobits(str.substr(4, 2)), stringTobits(str.substr(12, 2)), stringTobits(str.substr(20, 2)), stringTobits(str.substr(28, 2)),
        stringTobits(str.substr(6, 2)), stringTobits(str.substr(14, 2)), stringTobits(str.substr(22, 2)), stringTobits(str.substr(30, 2))
    }};
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
            map[i][j] = sbox[col * 0x10 + row];
        }
    }
}

void sub_byte_col(std::array<uint8_t, 4> &map, const std::array<uint8_t, 256> &sbox) {
        for (int j = 0; j < 4; ++j) {
            int row = map[j] / 0x10;
            int col = map[j] % 0x10;
            map[j] = sbox[col * 0x10 + row];
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

std::array<uint8_t, 4> rot_word(std::array<uint8_t, 4> &map) {
    return{{map[1], map[2], map[3], map[0]}};
}

void display_col (std::array<uint8_t, 4> &col) {
    for (int i = 0; i < 4; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(col[i]);
    }
    std::cout << std::endl;
}

void generate_all_round_key(std::array<std::array<uint8_t, 4>, 4> (&round_key)[11], const std::array<std::array<uint8_t, 4>, 4> &main_key, const std::array<uint8_t, 256> &sbox)
{
    round_key[0] = main_key;
    std::array<std::array<uint8_t, 4>, 4> tmp = main_key;
    std::array<uint8_t, 4> last_col;
    std::array<uint8_t, 4> current_col;

    for (int round = 1; round < 10; ++round) {
        std::array<std::array<uint8_t, 4>, 4> tmp_;
        round_key[round - 1] = tmp;
        last_col = tmp[3];
        for (int col = 0; col < 4; ++col) {
            current_col = tmp[col];
            display_col(current_col);
            if (col == 0) {
                std::array<uint8_t, 4> test = rot_word(current_col);
                std::cout << "rot_word: ";
                display_col(test);
                sub_byte_col(test, sbox);
                std::cout << "sub_byte: ";
                display_col(test);
                for (int i = 0; i < 4; ++i) {
                    tmp_[col][i] = current_col[i] ^ test[i] ^ Rcon[round];
                }
                std::cout << "xor: "; // probleme zor here reprendre ici
                display_col(tmp_[col]);
            } else {
                current_col = tmp[col];
            }
        }

        // rot_word(tmp);
        sub_byte(tmp, sbox);
        for (int i = 0; i < 4; ++i) {
            round_key[round][0][i] ^= round_key[round][3][i] ^ Rcon[round];
        }
        for (int i = 1; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                round_key[round][i][j] ^= round_key[round][i - 1][j];
            }
        }
    }
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

// Function to perform AES encryption
std::string aesEncrypt(const std::string &input, const std::string &key) {
    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);
    // input // c24 86 f4 79 6f 06 57 48 1a 65 5c 55 9b 38 aa a
    // key //   6b50fd39f06d33cfefe6936430b6c94f
    // pass //  0fc668acd39462d17272fe863929973a
    // generate_sbox(const_cast<std::array<uint8_t, 256> &>(sbox));
    // std::cout << input << std::endl;
    // for (int i = 0; i < 4; ++i) {
        // sub_byte(input_map, sbox_transposed);
        // display_map(input_map);

        // shift_rows(input_map);
        // display_map(input_map);

        // mix_columns(input_map);
        // display_map(input_map);

        // generate_all_round_key(round_key, main_key, sbox_transposed);
    // }


    std::array<std::array<uint8_t, 4>, 4> round_key;
    std::array<std::array<uint8_t, 4>, 4> round_keys[11];

    // Générer et afficher les clés de tour

    generate_all_round_key(round_keys, main_key, sbox_transposed);

    for (int round = 0; round <= 10; ++round) {
        std::cout << "Round " << round << " Key: ";
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(round_keys[round][i][j]);
            }
        }
        std::cout << std::endl;
    }
    // int num_rounds = 10;

    // for (int round = 1; round <= num_rounds; ++round) {
    //     sub_byte(input_map, sbox_transposed);
    //     shift_rows(input_map);
    //     mix_columns(input_map);

    //     round_key = main_key;
    //     generate_round_key(round_key, main_key, round, sbox_transposed);

    //     add_round_key(input_map, round_key);
    // }

    // sub_byte(input_map, sbox_transposed);
    // shift_rows(input_map);

    // round_key = main_key;
    // generate_round_key(round_key, main_key, num_rounds, sbox_transposed);

    // add_round_key(input_map, round_key);

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
