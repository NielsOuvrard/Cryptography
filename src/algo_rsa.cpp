#include "config.hpp"

// uint64_t pgcd(uint64_t a, uint64_t b)
// {
//     uint64_t r = a % b;
//     while (r != 0) {
//         a = b;
//         b = r;
//         r = a % b;
//     }
//     return b;
// }

uint64_t pgcd(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void showLittleEndianHex(uint64_t value)
{
    for (int i = 0; i < sizeof(uint64_t); ++i) {
        // Deja de mostrar al final
        if (i > 0 && value >> (i * 8) == 0) {
            break;
        }
        uint8_t byte = static_cast<uint8_t>((value >> (i * 8)) & 0xFF);
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
}

// Función para encontrar el inverso multiplicativo de 'a' módulo 'm'
uint64_t modInverse(uint64_t a, uint64_t m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

void generateKeyPair(std::string p_str, std::string q_str)
{
    uint64_t p = str_hexa_to_int(p_str);
    uint64_t q = str_hexa_to_int(q_str);
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    uint64_t e = 0;
    uint64_t d = 0;
    uint64_t i = 0;

    if (65537 > phi) {
        e = 65537;
    } else {
        for (i = 2; i < phi; i++) {
            if (pgcd(i, phi) == 1) {
                e = i;
                break;
            }
        }
    }
    d = modInverse(e, phi);

    std::cout << "public key: ";
    showLittleEndianHex(e);
    std::cout << "-";
    showLittleEndianHex(n);
    std::cout << std::endl;
    std::cout << "private key: ";
    showLittleEndianHex(d);
    std::cout << "-";
    showLittleEndianHex(n);
    std::cout << std::endl;
}

/*

    for (int i = 0; i < 8; i++) {
        uint8_t bit = 0;// (n >> i) & 1;
        for (int j = 0; j < 8; j++) {
            bit = (n >> (i * 8 + j)) & 1;
        }
        std::cout << INT_TO_CHAR_HEX(bit);
    }
*/