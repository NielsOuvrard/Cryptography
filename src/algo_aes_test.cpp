#include "config.hpp"

std::array<uint8_t, 256> sbox_transposed = {
        0x63, 0xCA, 0xB7, 0x04, 0x09, 0x53, 0xD0, 0x51, 0xCD, 0x60, 0xE0, 0xE7, 0xBA, 0x70, 0xE1, 0x8C, // 0
        0x7C, 0x82, 0xFD, 0xC7, 0x83, 0xD1, 0xEF, 0xA3, 0x0C, 0x81, 0x32, 0xC8, 0x78, 0x3E, 0xF8, 0xA1, // 1
        0x77, 0xC9, 0x93, 0x23, 0x2C, 0x00, 0xAA, 0x40, 0x13, 0x4F, 0x3A, 0x37, 0x25, 0xB5, 0x98, 0x89, // 2
        0x7B, 0x7D, 0x26, 0xC3, 0x1A, 0xED, 0xFB, 0x8F, 0xEC, 0xDC, 0x0A, 0x6D, 0x2E, 0x66, 0x11, 0x0D, // 3
        0xF2, 0xFA, 0x36, 0x18, 0x1B, 0x20, 0x43, 0x92, 0x5F, 0x22, 0x49, 0x8D, 0x1C, 0x48, 0x69, 0xBF, // 4
        0x6B, 0x59, 0x3F, 0x96, 0x6E, 0xFC, 0x4D, 0x9D, 0x97, 0x2A, 0x06, 0xD5, 0xA6, 0x03, 0xD9, 0xE6, // 5
        0x6F, 0x47, 0xF7, 0x05, 0x5A, 0xB1, 0x33, 0x38, 0x44, 0x90, 0x24, 0x4E, 0xB4, 0xF6, 0x8E, 0x42, // 6
        0xC5, 0xF0, 0xCC, 0x9A, 0xA0, 0x5B, 0x85, 0xF5, 0x17, 0x88, 0x5C, 0xA9, 0xC6, 0x0E, 0x94, 0x68, // 7
        0x30, 0xAD, 0x34, 0x07, 0x52, 0x6A, 0x45, 0xBC, 0xC4, 0x46, 0xC2, 0x6C, 0xE8, 0x61, 0x9B, 0x41, // 8
        0x01, 0xD4, 0xA5, 0x12, 0x3B, 0xCB, 0xF9, 0xB6, 0xA7, 0xEE, 0xD3, 0x56, 0xDD, 0x35, 0x1E, 0x99, // 9
        0x67, 0xA2, 0xE5, 0x80, 0xD6, 0xBE, 0x02, 0xDA, 0x7E, 0xB8, 0xAC, 0xF4, 0x74, 0x57, 0x87, 0x2D, // A
        0x2B, 0xAF, 0xF1, 0xE2, 0xB3, 0x39, 0x7F, 0x21, 0x3D, 0x14, 0x62, 0xEA, 0x1F, 0xB9, 0xE9, 0x0F, // B
        0xFE, 0x9C, 0x71, 0xEB, 0x29, 0x4A, 0x50, 0x10, 0x64, 0xDE, 0x91, 0x65, 0x4B, 0x86, 0xCE, 0xB0, // C
        0xD7, 0xA4, 0xD8, 0x27, 0xE3, 0x4C, 0x3C, 0xFF, 0x5D, 0x5E, 0x95, 0x7A, 0xBD, 0xC1, 0x55, 0x54, // D
        0xAB, 0x72, 0x31, 0xB2, 0x2F, 0x58, 0x9F, 0xF3, 0x19, 0x0B, 0xE4, 0xAE, 0x8B, 0x1D, 0x28, 0xBB, // E
        0x76, 0xC0, 0x15, 0x75, 0x84, 0xCF, 0xA8, 0xD2, 0x73, 0xDB, 0x79, 0x08, 0x8A, 0x9E, 0xDF, 0x16  // F
};

const std::array<uint8_t, 256> inv_sbox = {
        0x52, 0x7C, 0x54, 0x08, 0x72, 0x6C, 0x90, 0xD0, 0x3A, 0x96, 0x47, 0xFC, 0x1F, 0x60, 0xA0, 0x17, 
        0x09, 0xE3, 0x7B, 0x2E, 0xF8, 0x70, 0xD8, 0x2C, 0x91, 0xAC, 0xF1, 0x56, 0xDD, 0x51, 0xE0, 0x2B, 
        0x6A, 0x39, 0x94, 0xA1, 0xF6, 0x48, 0xAB, 0x1E, 0x11, 0x74, 0x1A, 0x3E, 0xA8, 0x7F, 0x3B, 0x04, 
        0xD5, 0x82, 0x32, 0x66, 0x64, 0x50, 0x00, 0x8F, 0x41, 0x22, 0x71, 0x4B, 0x33, 0xA9, 0x4D, 0x7E, 
        0x30, 0x9B, 0xA6, 0x28, 0x86, 0xFD, 0x8C, 0xCA, 0x4F, 0xE7, 0x1D, 0xC6, 0x88, 0x19, 0xAE, 0xBA, 
        0x36, 0x2F, 0xC2, 0xD9, 0x68, 0xED, 0xBC, 0x3F, 0x67, 0xAD, 0x29, 0xD2, 0x07, 0xB5, 0x2A, 0x77, 
        0xA5, 0xFF, 0x23, 0x24, 0x98, 0xB9, 0xD3, 0x0F, 0xDC, 0x35, 0xC5, 0x79, 0xC7, 0x4A, 0xF5, 0xD6, 
        0x38, 0x87, 0x3D, 0xB2, 0x16, 0xDA, 0x0A, 0x02, 0xEA, 0x85, 0x89, 0x20, 0x31, 0x0D, 0xB0, 0x26, 
        0xBF, 0x34, 0xEE, 0x76, 0xD4, 0x5E, 0xF7, 0xC1, 0x97, 0xE2, 0x6F, 0x9A, 0xB1, 0x2D, 0xC8, 0xE1, 
        0x40, 0x8E, 0x4C, 0x5B, 0xA4, 0x15, 0xE4, 0xAF, 0xF2, 0xF9, 0xB7, 0xDB, 0x12, 0xE5, 0xEB, 0x69, 
        0xA3, 0x43, 0x95, 0xA2, 0x5C, 0x46, 0x58, 0xBD, 0xCF, 0x37, 0x62, 0xC0, 0x10, 0x7A, 0xBB, 0x14, 
        0x9E, 0x44, 0x0B, 0x49, 0xCC, 0x57, 0x05, 0x03, 0xCE, 0xE8, 0x0E, 0xFE, 0x59, 0x9F, 0x3C, 0x63, 
        0x81, 0xC4, 0x42, 0x6D, 0x5D, 0xA7, 0xB8, 0x01, 0xF0, 0x1C, 0xAA, 0x78, 0x27, 0x93, 0x83, 0x55, 
        0xF3, 0xDE, 0xFA, 0x8B, 0x65, 0x8D, 0xB3, 0x13, 0xB4, 0x75, 0x18, 0xCD, 0x80, 0xC9, 0x53, 0x21, 
        0xD7, 0xE9, 0xC3, 0xD1, 0xB6, 0x9D, 0x45, 0x8A, 0xE6, 0xDF, 0xBE, 0x5A, 0xEC, 0x9C, 0x99, 0x0C, 
        0xFB, 0xCB, 0x4E, 0x25, 0x92, 0x84, 0x06, 0x6B, 0x73, 0x6E, 0x1B, 0xF4, 0x5F, 0xEF, 0x61, 0x7D
};


const std::array<uint8_t, 16> Rcon = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

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

void zor_three_value (std::array<uint8_t, 4> &col, std::array<uint8_t, 4> &col2, std::array<uint8_t, 4> &col3) {
    for (int i = 0; i < 4; ++i) {
        col[i] ^= col2[i] ^ col3[i];
    }
}

void generate_all_round_key(std::array<std::array<uint8_t, 4>, 4> (&round_key)[11], const std::array<std::array<uint8_t, 4>, 4> &main_key, const std::array<uint8_t, 256> &sbox)
{
    round_key[0] = main_key;
    std::array<std::array<uint8_t, 4>, 4> tmp = main_key;
    std::array<uint8_t, 4> last_lign;
    std::array<uint8_t, 4> current_col;
    std::array<uint8_t, 4> next_col;

    for (int round = 1; round < 11; ++round) {
        if (round != 1)
            tmp = round_key[round - 1];
        std::array<std::array<uint8_t, 4>, 4> tmp_;
        last_lign = {{tmp[1][3], tmp[2][3], tmp[3][3], tmp[0][3]}};
        
        for (int col = 0; col < 4; ++col) {
            current_col = {{tmp[0][col], tmp[1][col], tmp[2][col], tmp[3][col]}};
            if (col == 0) {
                sub_byte_col(last_lign, sbox);
                for (int i = 0; i < 4; ++i) {
                    if (i == 0)
                        tmp_[i][col] = current_col[i] ^= last_lign[i] ^ Rcon[round - 1];
                    else {
                        tmp_[i][col] = current_col[i] ^ last_lign[i];
                    }
                }
            } else {
                std::array<uint8_t, 4> first_col = {{tmp_[0][col - 1], tmp_[1][col - 1], tmp_[2][col - 1], tmp_[3][col - 1]}};
                for (int i = 0; i < 4; ++i) {
                    tmp_[i][col] = current_col[i] ^ first_col[i];
                }
            }
        }
        round_key[round] = tmp_;
    }
}

void generate_all_round_key_decrypt(std::array<std::array<uint8_t, 4>, 4> (&round_key)[11], const std::array<std::array<uint8_t, 4>, 4> &main_key, const std::array<uint8_t, 256> &sbox)
{
    round_key[10] = main_key;
    std::array<std::array<uint8_t, 4>, 4> tmp = main_key;
    std::array<uint8_t, 4> last_lign;
    std::array<uint8_t, 4> current_col;
    std::array<uint8_t, 4> next_col;

    for (int round = 9; round >= 0; --round) {
        if (round != 9)
            tmp = round_key[round + 1];
        std::array<std::array<uint8_t, 4>, 4> tmp_;
        last_lign = {{tmp[1][3], tmp[2][3], tmp[3][3], tmp[0][3]}};

        for (int col = 0; col < 4; ++col) {
            current_col = {{tmp[0][col], tmp[1][col], tmp[2][col], tmp[3][col]}};
            if (col == 0) {
                sub_byte_col(last_lign, sbox);
                for (int i = 0; i < 4; ++i) {
                    if (i == 0)
                        tmp_[i][col] = current_col[i] ^= last_lign[i] ^ Rcon[round];
                    else {
                        tmp_[i][col] = current_col[i] ^ last_lign[i];
                    }
                }
            } else {
                std::array<uint8_t, 4> first_col = {{tmp_[0][col - 1], tmp_[1][col - 1], tmp_[2][col - 1], tmp_[3][col - 1]}};
                for (int i = 0; i < 4; ++i) {
                    tmp_[i][col] = current_col[i] ^ first_col[i];
                }
            }
        }
        round_key[round] = tmp_;
    }
}


// Function to convert a map to a hexadecimal string
std::string map_to_hex_string(const std::array<std::array<uint8_t, 4>, 4> &map) {
    std::stringstream result;
    for (const auto &row : map) {
        for (auto it = row.rbegin(); it != row.rend(); ++it) {
            result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*it);
        }
    }
    return result.str();
}

std::string arrayToHexString(const std::array<std::array<uint8_t, 4>, 4>& inputArray) {
    std::ostringstream oss;

    for (const auto& row : inputArray) {
        for (const auto& element : row) {
            oss << std::hex << std::setw(1) << static_cast<int>(element >> 4);
            oss << std::hex << std::setw(1) << static_cast<int>(element & 0x0F);
        }
    }
    return oss.str();
}

std::array<std::array<uint8_t, 4>, 4> convert_big_to_little(const std::array<std::array<uint8_t, 4>, 4>& input) {
       return {{
        input[0][0], input[1][0], input[2][0], input[3][0],
        input[0][1], input[1][1], input[2][1], input[3][1],
        input[0][2], input[1][2], input[2][2], input[3][2],
        input[0][3], input[1][3], input[2][3], input[3][3]
    }};
}

// Function to shift the rows of a 4x4 matrix in the inverse direction
void inv_shift_rows(std::array<std::array<uint8_t, 4>, 4> &map) {
    for (int i = 1; i < 4; ++i) {
        std::rotate(map[i].begin(), map[i].begin() + (4 - i), map[i].end());
    }
}

// Function to perform the inverse byte substitution (InvSubBytes)
void inv_sub_byte(std::array<std::array<uint8_t, 4>, 4> &map, const std::array<uint8_t, 256> &sbox) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int row = map[i][j] / 0x10;
            int col = map[i][j] % 0x10;
            map[i][j] = sbox[col * 0x10 + row];
        }
    }
}

// Function to perform the inverse mix columns operation
void inv_mix_columns(std::array<std::array<uint8_t, 4>, 4> &map) {
    for (int i = 0; i < 4; ++i) {
        uint8_t a[4];
        for (int j = 0; j < 4; ++j) {
            a[j] = map[j][i];
        }

        map[0][i] = gmul(a[0], 0x0E) ^ gmul(a[1], 0x0B) ^ gmul(a[2], 0x0D) ^ gmul(a[3], 0x09);
        map[1][i] = gmul(a[0], 0x09) ^ gmul(a[1], 0x0E) ^ gmul(a[2], 0x0B) ^ gmul(a[3], 0x0D);
        map[2][i] = gmul(a[0], 0x0D) ^ gmul(a[1], 0x09) ^ gmul(a[2], 0x0E) ^ gmul(a[3], 0x0B);
        map[3][i] = gmul(a[0], 0x0B) ^ gmul(a[1], 0x0D) ^ gmul(a[2], 0x09) ^ gmul(a[3], 0x0E);
    }
}

std::string aesEncrypt(const std::string &input, const std::string &key) {
    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);

    // input // c2486f4796f0657481a655c559b38aaa
    // key //   6b50fd39f06d33cfefe6936430b6c94f
    // pass //  0fc668acd39462d17272fe863929973a

    std::array<std::array<uint8_t, 4>, 4> round_keys[11];

    // Générer tt les les clés de tour en 1 fois
    generate_all_round_key(round_keys, main_key, sbox_transposed);

    int num_rounds = 10;

    add_round_key(input_map, round_keys[0]);

    for (int round = 1; round < num_rounds; ++round) {
        sub_byte(input_map, sbox_transposed);
        shift_rows(input_map);
        mix_columns(input_map);
        add_round_key(input_map, round_keys[round]);
    }

    sub_byte(input_map, sbox_transposed);
    shift_rows(input_map);
    add_round_key(input_map, round_keys[10]);
    return arrayToHexString(convert_big_to_little(input_map));
}



std::string aesDecrypt(const std::string &input, const std::string &key) {
    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);

    std::array<std::array<uint8_t, 4>, 4> round_keys[11];

    generate_all_round_key(round_keys, main_key, sbox_transposed);

    int num_rounds = 10;

    std::cout << "Round 0 Key + input: ";
    display_map(round_keys[10]);
    display_map(input_map);
    std::cout << "\n" << std::endl;

    std::cout << "\nadd_round_key: ";
    add_round_key(input_map, round_keys[10]);
    display_map(input_map);
    std::cout << "\nshift_row: ";
    inv_shift_rows(input_map);
    display_map(input_map);
    std::cout << "sub_byte: ";
    inv_sub_byte(input_map, inv_sbox);
    display_map(input_map);

    for (int round = num_rounds - 1; round >= 1; --round) {
        std::cout << "Round " << round << "\n";
        display_map(input_map);
        std::cout << "\nadd_round_key: ";
        add_round_key(input_map, round_keys[round]);
        display_map(input_map);
        std::cout << "\nmix_col: ";
        inv_mix_columns(input_map);
        display_map(input_map);
        std::cout << "\nshift_row: ";
        inv_shift_rows(input_map);
        display_map(input_map);
        std::cout << "sub_byte: ";
        inv_sub_byte(input_map, inv_sbox);
        display_map(input_map);
        std::cout << "\n\n" << std::endl;
    }
        display_map(input_map);

    add_round_key(input_map, round_keys[0]);
        display_map(input_map);

    return arrayToHexString(convert_big_to_little(input_map));
}

// input // 0fc668acd39462d17272fe863929973a
// key //   6b50fd39f06d33cfefe6936430b6c94f
// pass //  c2486f4796f0657481a655c559b38aaa
