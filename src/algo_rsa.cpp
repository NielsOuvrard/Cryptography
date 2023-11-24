#include "config.hpp"

inf_int str_hexa_to_int(std::string str)
{
    inf_int res = 0;
    for (int i = 0; i < str.length(); i++) {
        res = res * 16 + CHAR_HEX_TO_INT(str[i]);
    }
    return res;
}

inf_int str_hexa_to_int_rev(std::string str)
{
    inf_int res = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        res = res * 16 + CHAR_HEX_TO_INT(str[i]);
    }
    return res;
}

inf_int pgcd(inf_int a, inf_int b)
{
    while (b != 0) {
        inf_int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

inf_int len_nbr(inf_int value)
{
    inf_int len = 0;
    while (value != 0) {
        value = value / 10;
        len++;
    }
    return len;
}

void showLittleEndianHex(inf_int value)
{
    for (int i = 0; i < len_nbr(value); ++i) {
        // Deja de mostrar al final
        if (i > 0 && (value >> (i * 8)) == 0) {
            break;
        }
        uint8_t byte = static_cast<uint8_t>((value >> (i * 8)) & 0xFF);
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
}

// Función para encontrar el inverso multiplicativo de 'a' módulo 'm'
inf_int modInverse(inf_int a, inf_int m)
{
    inf_int m0 = m, t, q;
    inf_int x0 = 0, x1 = 1;

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

std::string inverse_two_by_two(std::string value)
{
    std::string new_value = "";
    for (int i = 0; i < value.length(); i += 2) {
        std::string tmp = "";
        tmp += value[i + 1];
        tmp += value[i];
        new_value = new_value + tmp;
    }
    return new_value;
}

std::string inverse_two_by_two_rev(std::string value)
{
    std::string new_value = "";
    for (int i = 0; i < value.length(); i += 2) {
        std::string tmp = "";
        tmp += value[i];
        tmp += value[i + 1];
        new_value = tmp + new_value;
    }
    return new_value;
}

void generateKeyPair(std::string p_str, std::string q_str)
{
    inf_int p = str_hexa_to_int_rev(inverse_two_by_two(p_str));
    inf_int q = str_hexa_to_int_rev(inverse_two_by_two(q_str));
    inf_int n = p * q;
    inf_int phi = (p - 1) * (q - 1);

    inf_int e = 0;
    inf_int d = 0;
    inf_int i = 0;

    e = 65537;
    // * another way to find e
    /*
    for (i = 2; i < phi; i++) {
        if (pgcd(i, phi) == 1) {
            e = i;
            break;
        }
    }
    */

    // Calculate the private key exponent (d)
    d = modInverse(e, phi);

    // Display public and private keys
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

inf_int modPow(inf_int base, inf_int exponent, inf_int modulus)
{
    inf_int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

inf_int pow_boost(inf_int a, inf_int b)
{
    inf_int res = 1;

    while (b > 0) {
        if (b % 2 == 1)
            res *= a;

        a *= a;
        b /= 2;
    }

    return res;
}

void rsaEncrypt(std::string input, std::pair<inf_int, inf_int> keyPair)
{
    inf_int e = keyPair.first;
    inf_int n = keyPair.second;
    inf_int c = 0;
    inf_int m = str_hexa_to_int_rev(inverse_two_by_two(input));
    c = modPow(m, e, n);
    showLittleEndianHex(c);
    std::cout << std::endl;
}

void rsaDecrypt(std::string input, std::pair<inf_int, inf_int> keyPair)
{
    inf_int d = keyPair.first;
    inf_int n = keyPair.second;
    inf_int m = 0;
    inf_int c = str_hexa_to_int_rev(inverse_two_by_two(input));
    m = modPow(c, d, n);
    showLittleEndianHex(m);
    std::cout << std::endl;
}
