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

// 19bb
// bb19

// 19bbff
// ffbb19

// 19bbffa3
// a3ffbb19

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

    // if (65537 > phi) {
    e = 65537;
    // } else {
    // for (i = 2; i < phi; i++) {
    //     if (pgcd(i, phi) == 1) {
    //         e = i;
    //         break;
    //     }
    // }
    // }
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

// * ∼/B-CNA-500> ./mypgp -rsa -g 4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1 bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb
// public key: 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3
// private key: 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3

// inf_int str_hexa_to_int(std::string str);
// std::string int_to_str_hexa(inf_int n);

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


// * ∼/B-CNA-500> echo "c1fa29d40054f3fcb1c15fe4d63d3887" > message
// * ∼/B-CNA-500> cat message | ./mypgp -rsa -c 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3 > ciphered
// * ∼/B-CNA-500> cat ciphered
// dc0bd7367d04e5a9e9e14467ff38de0625b3cfa5aabbe86def48bfc93e97aab713d70abf83d263a6dd6570c6d297cc44bad2e0dd2cf7b4c3e0a9749d68ca11a8

// * ∼/B-CNA-500> cat ciphered | ./mypgp -rsa -d 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3
// c1fa29d40054f3fcb1c15fe4d63d3887
