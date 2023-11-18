#include "config.hpp"
const uint8_t Rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};


// Function to create a 4x4 matrix from a hexadecimal string
std::array<std::array<uint8_t, 4>, 4> create_map_from_str(const std::string &str)
{
    std::array<std::array<uint8_t, 4>, 4> map_map = {0};

    std::string reversed = inverse_two_by_two_rev(str);// little endian

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            map_map[i][j] = CHAR_HEX_TO_INT(reversed[i * 8 + j * 2]) * 16 + CHAR_HEX_TO_INT(reversed[i * 8 + j * 2 + 1]);
        }
    }
    return map_map;
}

// Function to perform the multiplication in the finite field GF(2^8)
uint8_t gmul(uint8_t a, uint8_t b)
{
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

// Function to display a matrix
void display_map(const std::array<std::array<uint8_t, 4>, 4> &map)
{
    std::cout << "Map:" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(map[i][j]) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Function to perform an XOR operation between two 4x4 matrices
std::array<std::array<uint8_t, 4>, 4> xor_operation(const std::array<std::array<uint8_t, 4>, 4> &key, const std::array<std::array<uint8_t, 4>, 4> &input)
{
    std::array<std::array<uint8_t, 4>, 4> new_map = {0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_map[i][j] = key[i][j] ^ input[i][j];
        }
    }
    return new_map;
}

// Function to generate the S-Box
void generate_s_box(uint8_t s_box[256])
{
    for (int i = 0; i < 256; ++i) {
        s_box[i] = (i <= 0x7F) ? gmul(i, 0x02) : gmul(i, 0x02) ^ 0x1B;
    }
}

unsigned char gf28_inverse(uint8_t a)
{
    uint8_t val = a;
    for (int i = 0; i < 7; ++i) {
        val = (val << 1) ^ ((val & 0x80) ? 0x1B : 0);
    }
    return val;
}

// Function to perform the substitution in the S-Box generation
uint8_t s_box_substitution(uint8_t a, uint8_t s_box[256])
{
    uint8_t b = gf28_inverse(a);
    return b ^ 0x63;
}

// Function to perform byte substitution (SubBytes)
void sub_byte(std::array<std::array<uint8_t, 4>, 4> &map, uint8_t s_box[256])
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int row = map[i][j] / 0x10;// Row in the S-Box
            int col = map[i][j] % 0x10;// Column in the S-Box
            map[i][j] = s_box[row * 0x10 + col];
        }
    }
}

// Function to shift the rows of a 4x4 matrix
void shift_rows(std::array<std::array<uint8_t, 4>, 4> &map)
{
    for (int i = 1; i < 4; ++i) {
        std::rotate(map[i].begin(), map[i].begin() + i, map[i].end());
    }
}

// Function to mix the columns of a 4x4 matrix
void mix_columns(std::array<std::array<uint8_t, 4>, 4> &map)
{
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
void add_round_key(std::array<std::array<uint8_t, 4>, 4> &map, const std::array<std::array<uint8_t, 4>, 4> &round_key)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            map[i][j] ^= round_key[i][j];
        }
    }
}

// Function to generate the round key from the main key
void generate_round_key(std::array<std::array<uint8_t, 4>, 4> &round_key, const std::array<std::array<uint8_t, 4>, 4> &main_key, int round, uint8_t s_box[256])
{
    // Rotate the last column to the top
    std::rotate(round_key[0].begin(), round_key[0].begin() + 1, round_key[0].end());
    std::rotate(round_key[1].begin(), round_key[1].begin() + 1, round_key[1].end());
    std::rotate(round_key[2].begin(), round_key[2].begin() + 1, round_key[2].end());
    std::rotate(round_key[3].begin(), round_key[3].begin() + 1, round_key[3].end());

    // Substitute the bytes using the S-Box
    for (int i = 0; i < 4; ++i) {
        round_key[i][0] = s_box_substitution(round_key[i][0], s_box);
    }

    // XOR with the corresponding main key column
    for (int i = 0; i < 4; ++i) {
        round_key[i][0] ^= main_key[i][0];
    }

    // XOR with the round constant for the first byte
    round_key[0][0] ^= Rcon[round];
}


std::string map_hex_to_str(const std::array<std::array<uint8_t, 4>, 4> &map)
{
    std::stringstream result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(map[row][col]);
        }
    }

    return result.str();
}

std::string map_to_str_little_endian(const std::array<std::array<uint8_t, 4>, 4> &map)
{
    std::stringstream result;

    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            // Convert each element to a two-digit uppercase hexadecimal string
            result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(map[row][col]);
        }
    }

    return result.str();
}

void inv_mix_columns(std::array<std::array<uint8_t, 4>, 4> &map)
{
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

std::string aesEncrypt(const std::string &input, const std::string &key)
{
    uint8_t s_box[256];
    generate_s_box(s_box);

    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);

    // input
    // c2486f4796f0657481a655c559b38aaa

    // key
    // 6b50fd39f06d33cfefe6936430b6c94f

    std::array<std::array<uint8_t, 4>, 4> round_key;

    add_round_key(input_map, main_key);

    int num_rounds = 10;

    for (int round = 1; round <= num_rounds; ++round) {
        sub_byte(input_map, s_box);

        shift_rows(input_map);

        mix_columns(input_map);

        round_key = main_key;
        generate_round_key(round_key, main_key, round, s_box);

        add_round_key(input_map, round_key);
        display_map(input_map);
    }

    sub_byte(input_map, s_box);

    shift_rows(input_map);

    round_key = main_key;
    generate_round_key(round_key, main_key, num_rounds, s_box);

    add_round_key(input_map, round_key);
    display_map(input_map);
    return map_hex_to_str(input_map);
}


std::string aesDecrypt(const std::string &input, const std::string &key)
{
    uint8_t s_box[256];
    generate_s_box(s_box);

    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);
    std::array<std::array<uint8_t, 4>, 4> round_key;

    int num_rounds = 10;

    round_key = main_key;
    generate_round_key(round_key, main_key, num_rounds, s_box);

    add_round_key(input_map, round_key);
    shift_rows(input_map);
    sub_byte(input_map, s_box);

    for (int round = num_rounds - 1; round >= 1; --round) {
        round_key = main_key;
        generate_round_key(round_key, main_key, round, s_box);

        add_round_key(input_map, round_key);
        inv_mix_columns(input_map);
        shift_rows(input_map);
        sub_byte(input_map, s_box);
    }

    round_key = main_key;
    add_round_key(input_map, round_key);
    display_map(input_map);
    return map_hex_to_str(input_map);
}
