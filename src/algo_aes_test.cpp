#include "config.hpp"
const uint8_t Rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};


// Function to create a 4x4 matrix from a hexadecimal string
std::array<std::array<uint8_t, 4>, 4> create_map_from_str(const std::string &str)
{
    std::array<std::array<uint8_t, 4>, 4> map_map = {0};

    int row = 0;
    int col = 0;
    for (int i = 0; i < 16; i++, col++) {
        if (col >= 4) {
            row++;
            col = 0;
        }
        map_map[row][col] = (str[i * 2] <= '9' ? str[i * 2] - '0' : str[i * 2] - 'A' + 10) * 16 +
                            (str[i * 2 + 1] <= '9' ? str[i * 2 + 1] - '0' : str[i * 2 + 1] - 'A' + 10);
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

// * //////////////////////////////////////////////////////////////////////////// * //
// Rijndael S-box
const unsigned char sbox[256] = {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};


static const uint8_t Sbox[16][16] = {
        {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
        {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
        {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
        {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
        {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
        {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
        {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
        {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
        {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
        {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
        {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
        {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
        {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
        {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
        {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
        {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

// Constants for the key expansion
#define NB 4 // Number of columns in the state
#define NK 8 // Number of 32-bit words in the key
#define NR 14// Number of rounds

inf_int power(inf_int base, inf_int exponent)
{
    inf_int result = 1;
    // base = base % mod;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base);
        }
        exponent = exponent >> 1;// equivalent to exponent /= 2
        base = (base * base);
    }

    return result;
}


// Function to rotate a word (circular left shift)
void RotWord(std::array<uint8_t, 4> &word)
{
    uint8_t temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

// Function to perform SubWord operation
void SubWord(std::array<uint8_t, 4> &word)
{
    for (size_t i = 0; i < 4; ++i) {
        word[i] = Sbox[word[i] >> 4][word[i] & 0x0F];
    }
}

// Function to generate the round constants
void GenerateRoundConstants(std::vector<uint8_t> &roundConstants)
{
    roundConstants.resize(10);
    roundConstants[0] = 0x01;
    for (size_t i = 1; i < roundConstants.size(); ++i) {
        // Generate round constants using Rijndael's finite field polynomial
        roundConstants[i] = static_cast<uint8_t>((roundConstants[i - 1] << 1) ^ ((roundConstants[i - 1] & 0x80) ? 0x1B : 0x00));
    }
}

// Function to perform key expansion for AES
void KeyExpansion(const std::array<std::array<uint8_t, 4>, 4> &key, std::vector<std::array<std::array<uint8_t, 4>, 4>> &roundKeys)
{
    roundKeys.clear();

    // Initialize roundKeys with the original key
    roundKeys.push_back(key);

    // Number of rounds based on key length (AES-128 has 10 rounds)
    const size_t numRounds = 10;

    // Number of 32-bit words in the key
    const size_t numWords = 4;

    // Number of words in the expanded key
    const size_t expandedKeySize = 4 * (numRounds + 1);

    // Round constants used for key expansion
    std::vector<uint8_t> roundConstants;
    GenerateRoundConstants(roundConstants);

    // Temporary storage for the expanded key
    std::vector<std::array<uint8_t, 4>> tempKey(expandedKeySize);

    // Copy the original key into the temporary key
    for (size_t i = 0; i < numWords; ++i) {
        tempKey[i] = {key[0][i], key[1][i], key[2][i], key[3][i]};
    }

    // Generate the rest of the expanded key
    for (size_t i = numWords; i < expandedKeySize; ++i) {
        std::array<uint8_t, 4> temp = tempKey[i - 1];

        // Perform key schedule core every 4 words
        if (i % numWords == 0) {
            RotWord(temp);
            SubWord(temp);
            temp[0] ^= roundConstants[i / numWords - 1];
        }

        // XOR the result with the word numWords back
        for (size_t j = 0; j < 4; ++j) {
            tempKey[i][j] = tempKey[i - numWords][j] ^ temp[j];
        }
    }

    // Copy the temporary key into the roundKeys vector
    for (size_t i = 1; i < expandedKeySize; i += numWords) {
        roundKeys.push_back({tempKey[i], tempKey[i + 1], tempKey[i + 2], tempKey[i + 3]});
    }
}

std::string aesEncrypt(const std::string &input, const std::string &key)
{
    uint8_t s_box[256];
    generate_s_box(s_box);

    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);
    // std::array<std::array<uint8_t, 4>, 4> round_key;

    // inf_int int_key = str_hexa_to_int(inverse_two_by_two_rev(key));
    // inf_int int_message = str_hexa_to_int(inverse_two_by_two_rev(input));

    // Create a key schedule using key expansion
    std::vector<std::array<std::array<uint8_t, 4>, 4>> roundKeys;
    display_map(main_key);

    // Key expansion
    KeyExpansion(main_key, roundKeys);

    // add_round_key(input_map, main_key);

    // Initial round
    // inf_int state = message ^ keySchedule[0];

    int num_rounds = 14;

    for (int round = 1; round <= num_rounds; ++round) {
        sub_byte(input_map, s_box);
        shift_rows(input_map);
        mix_columns(input_map);

        // state ^= keySchedule[round];

        // old
        // round_key = main_key;
        // generate_round_key(round_key, main_key, round, s_box);
        // add_round_key(input_map, round_key);
        // display_map(input_map);
    }

    // Final round (without mix columns)
    sub_byte(input_map, s_box);
    shift_rows(input_map);
    // state ^= keySchedule[num_rounds];

    // old
    // round_key = main_key;
    // generate_round_key(round_key, main_key, num_rounds, s_box);
    // add_round_key(input_map, round_key);
    // display_map(input_map);


    return map_hex_to_str(input_map);
}

// 0fc668acd39462d17272fe863929973a


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
