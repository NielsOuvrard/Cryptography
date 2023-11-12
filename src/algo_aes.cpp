#include "config.hpp"

// std::string xorEncrypt(const std::string &message, const std::string &key)
// {
//     std::string encryptedMessage;
//     for (size_t i = 0; i < message.length(); ++i) {
//         char encryptedByte = message[i] ^ key[i];
//         encryptedMessage += encryptedByte;
//     }

//     return stringToHex(encryptedMessage);
// }

// std::string xorDecrypt(const std::string &encryptedMessage, const std::string &key)
// {
//     std::string hexDecryptedMessage = hexToString(encryptedMessage);
//     return hexToString(xorEncrypt(encryptedMessage, key));
// }

std::array<std::array<uint8_t, 4>, 4> create_map_from_str(const std::string &str)
{
    std::array<std::array<uint8_t, 4>, 4> map_map = {0};

    // std::cout << "str: " << str << std::endl;
    int row = 0;
    int col = 0;
    for (int i = 0; i < 16; i++, col++) {
        if (col >= 4) {
            row++;
            col = 0;
        }
        map_map[row][col] = (CHAR_HEX_TO_INT(str[i * 2]) * 16) + CHAR_HEX_TO_INT(str[i * 2 + 1]);
        // std::cout << "map_map[" << row << "][" << col << "] = " << std::hex << map_map[row][col] << std::endl;
    }
    return map_map;
}

void display_map(std::array<std::array<uint8_t, 4>, 4> map)
{
    std::cout << "map: " << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "    ";
        for (int j = 0; j < 4; j++) {
            int a = map[i][j];
            std::cout << std::hex << a << " ";
        }
        std::cout << std::endl;
    }
}

// * /////////////////////////////////////////////////////////////////////////// OR EXCLISIF

std::array<std::array<uint8_t, 4>, 4> or_exclisif_operation(std::array<std::array<uint8_t, 4>, 4> key, std::array<std::array<uint8_t, 4>, 4> input)
{
    std::array<std::array<uint8_t, 4>, 4> new_map = {0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            new_map[i][j] = key[i][j] ^ input[i][j];
        }
    }
    return new_map;
}

// void sub_bytes(std::array<std::array<uint8_t, 4>, 4> &map)
// {
//     std::array<std::array<uint8_t, 4>, 4> new_map = {0};

//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; i++) {
//             new_map[i][j] = S_BOX[map[i][j]];
//         }
//     }
//     map = new_map;

// }
// * /////////////////////////////////////////////////////////////////////////// SUB BYTES
// Función para calcular el inverso en el cuerpo finito GF(2^8)
unsigned char gf28_inverse(uint8_t a)
{
    uint8_t val = a;
    for (int i = 0; i < 7; ++i) {
        val = (val << 1) ^ ((val & 0x80) ? 0x1B : 0);
    }
    return val;
}

// Función para realizar la sustitución en la generación de la S-Box
uint8_t s_boxSubstitution(uint8_t a)
{
    // Sustitución afín en el cuerpo finito GF(2^8)
    uint8_t b = gf28_inverse(a);
    return b ^ 0x63;// Constante de la S-Box
}

// Función para generar la S-Box
void generateS_box(uint8_t s_box[256])
{
    for (int i = 0; i < 256; ++i) {
        s_box[i] = s_boxSubstitution(static_cast<uint8_t>(i));
    }
}

void sub_byte(std::array<std::array<uint8_t, 4>, 4> &map, uint8_t s_box[256])
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Obtener las coordenadas en la S-Box
            int row = map[i][j] / 0x10;// Fila en la S-Box
            int col = map[i][j] % 0x10;// Columna en la S-Box

            // Realizar la sustitución
            map[i][j] = s_box[row * 0x10 + col];
        }
    }
}

// * /////////////////////////////////////////////////////////////////////////// SHIFT ROWS

void shift_rows(std::array<std::array<uint8_t, 4>, 4> &map)
{
    for (int i = 1; i < 4; ++i) {
        std::rotate(map[i].begin(), map[i].begin() + i, map[i].end());
    }
}

// * /////////////////////////////////////////////////////////////////////////// MIX COLUMNS

void mix_columns(std::array<std::array<uint8_t, 4>, 4> &map)
{
}

std::string aesEncryptDecrypt(const std::string &input, const std::string &key)
{

    uint8_t s_box[256];
    generateS_box(s_box);

    std::cout << "S-Box:" << std::endl;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(s_box[i * 16 + j]) << " ";
        }
        std::cout << std::endl;
    }

    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);

    display_map(input_map);

    sub_byte(input_map, s_box);

    display_map(input_map);

    shift_rows(input_map);

    display_map(input_map);

    // std::array<std::array<uint8_t, 4>, 4> key_map = create_map_from_str(key);

    // display_map(key_map);
    // display_map(input_map);

    // std::array<std::array<uint8_t, 4>, 4> new_map = or_exclisif_operation(key_map, input_map);

    // display_map(new_map);

    // for (size_t i = 0; i < input.size(); i++) {
    //     char a = CHAR_HEX_TO_INT(input[i]) ^ CHAR_HEX_TO_INT(key[i % key.size()]);
    //     output[i] = INT_TO_CHAR_HEX(a);
    // }

    std::string output(input.size(), '0');
    return output;
}

// 3c24744d2bc520ecc7144b55ab5fdc85
// 10 rondas para clave de 128 bits
// 12 rondas para clave de 192 bits
// 14 rondas para clave de 256 bits