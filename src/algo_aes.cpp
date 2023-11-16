#include "config.hpp"

// Fonction pour créer une matrice 4x4 à partir d'une chaîne hexadécimale
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
        map_map[row][col] = (CHAR_HEX_TO_INT(str[i * 2]) * 16) + CHAR_HEX_TO_INT(str[i * 2 + 1]);
    }
    return map_map;
}

// Fonction pour afficher une matrice
void display_map(std::array<std::array<uint8_t, 4>, 4> map)
{
    std::cout << "map : " << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "    ";
        for (int j = 0; j < 4; j++) {
            int a = map[i][j];
            std::cout << std::hex << a << " ";
        }
        std::cout << std::endl;
    }
}

// * /////////////////////////////////////////////////////////////////////////// OU EXCLUSIF

// Fonction pour effectuer une opération OU exclusif entre deux matrices 4x4
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

// * /////////////////////////////////////////////////////////////////////////// SUBSTITUTION D'Octets (SUB BYTES)

// Fonction pour calculer l'inverse dans le corps fini GF(2^8)
unsigned char gf28_inverse(uint8_t a)
{
    uint8_t val = a;
    for (int i = 0; i < 7; ++i) {
        val = (val << 1) ^ ((val & 0x80) ? 0x1B : 0);
    }
    return val;
}

// Fonction pour effectuer la substitution dans la génération de la S-Box
uint8_t s_boxSubstitution(uint8_t a)
{
    // Substitution affine dans le corps fini GF(2^8)
    uint8_t b = gf28_inverse(a);
    return b ^ 0x63; // Constante de la S-Box
}

// Fonction pour générer la S-Box
void generateS_box(uint8_t s_box[256])
{
    for (int i = 0; i < 256; ++i) {
        s_box[i] = s_boxSubstitution(static_cast<uint8_t>(i));
    }
}

// Fonction pour effectuer la substitution d'octets (SubBytes)
void sub_byte(std::array<std::array<uint8_t, 4>, 4> &map, uint8_t s_box[256])
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Obtenir les coordonnées dans la S-Box
            int row = map[i][j] / 0x10; // Ligne dans la S-Box
            int col = map[i][j] % 0x10; // Colonne dans la S-Box

            // Effectuer la substitution
            map[i][j] = s_box[row * 0x10 + col];
        }
    }
}

//////////////////////////////////////////////////////////////////////////// DÉCALAGE DES LIGNES (SHIFT ROWS)

// Fonction pour décaler les lignes d'une matrice 4x4
void shift_rows(std::array<std::array<uint8_t, 4>, 4> &map)
{
    for (int i = 1; i < 4; ++i) {
        std::rotate(map[i].begin(), map[i].begin() + i, map[i].end());
    }
}

////////////////////////////////////////////////////////////////////////// MÉLANGE DES COLONNES (MIX COLUMNS)

// Fonction pour effectuer la multiplication dans le corps fini GF(2^8)
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
            a ^= 0x1B;  // Constante de multiplication dans GF(2^8) (corqs fini GF(2^8) (8bits/part) fined filed GF(2^8))
        }
        b >>= 1;
    }
    return p;
}


// Fonction pour mélanger les colonnes d'une matrice 4x4
void mix_columns(std::array<std::array<uint8_t, 4>, 4> &map)
{
    for (int i = 0; i < 4; ++i) {
        uint8_t a[4];  // Colonne tmp

        // Copier les valeur originale dans la colonne temporair
        for (int j = 0; j < 4; ++j) {
            a[j] = map[j][i];
        }

        // Effectuer les opérations de mélange sur la colonne temporaire
        map[0][i] = gmul(a[0], 0x02) ^ gmul(a[1], 0x03) ^ a[2] ^ a[3];
        map[1][i] = a[0] ^ gmul(a[1], 0x02) ^ gmul(a[2], 0x03) ^ a[3];
        map[2][i] = a[0] ^ a[1] ^ gmul(a[2], 0x02) ^ gmul(a[3], 0x03);
        map[3][i] = gmul(a[0], 0x03) ^ a[1] ^ a[2] ^ gmul(a[3], 0x02);
    }
}

////////////////////////////////////////////////////////////////////////// Ajouter la clé (ADD ROUND KEY)

// Fonction pour fenvelopper une clé autour d'une matrice 4x4
void add_round_key(std::array<std::array<uint8_t, 4>, 4> &map, const std::array<std::array<uint8_t, 4>, 4> &round_key)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            map[i][j] ^= round_key[i][j];
        }
    }
}


// Génération de la clé de tour à partir de la clé principale
void generate_round_key(std::array<std::array<uint8_t, 4>, 4> &round_key, const std::array<std::array<uint8_t, 4>, 4> &main_key, int round)
{
    // Rotation des octets
    uint8_t temp = round_key[0][0];
    round_key[0][0] = round_key[0][1];
    round_key[0][1] = round_key[0][2];
    round_key[0][2] = round_key[0][3];
    round_key[0][3] = temp;

    // Substitution des octets
    for (int i = 0; i < 4; ++i) {
        round_key[i][0] = s_boxSubstitution(round_key[i][0]);
    }

    // Génération de la constante de tour
    uint8_t rcon = 0x01 << (round - 1);

    // XOR avec la constante de tour
    round_key[0][0] ^= rcon;

    // XOR avec la clé du tour précédent
    for (int i = 0; i < 4; ++i) {
        round_key[i][0] ^= round_key[i][3];
    }

    // XOR avec la clé principale
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            round_key[i][j] ^= main_key[i][j];
        }
    }
}

std::string map_hex_to_str(const std::array<std::array<uint8_t, 4>, 4>& map) {
    std::stringstream result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            // Convert each element to a two-digit uppercase hexadecimal string
            result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(map[row][col]);
        }
    }

    return result.str();
}

std::string aesEncryptDecrypt(const std::string &input, const std::string &key)
{
    uint8_t s_box[256];
    generateS_box(s_box);

    std::array<std::array<uint8_t, 4>, 4> input_map = create_map_from_str(input);
    std::array<std::array<uint8_t, 4>, 4> main_key = create_map_from_str(key);
    std::array<std::array<uint8_t, 4>, 4> round_key;

    // Clé principale inchangée
    std::array<std::array<uint8_t, 4>, 4> original_main_key = main_key;

    // Clé de tour initiale
    add_round_key(input_map, main_key);

    // Nombre de tours en fonction de la taille de la clé
    int num_rounds = 10; // Changer en fonction de la taille de la clé 
    // TODO: 10 pour 128 bits, 12 pour 192 bits, 14 pour 256 bits

    // Boucle des tours (sauf le dernier)
    for (int round = 1; round < num_rounds; ++round) {
        sub_byte(input_map, s_box);
        shift_rows(input_map);
        mix_columns(input_map);

        // Génération de la clé de tour à partir de la clé principale
        round_key = main_key;
        generate_round_key(round_key, original_main_key, round);

        // Ajout de la clé de tour
        add_round_key(input_map, round_key);
    }

    // Dernier tour sans MixColumns
    sub_byte(input_map, s_box);
    shift_rows(input_map);

    // Génération de la clé de tour à partir de la clé principale pour le dernier tour
    round_key = main_key;
    generate_round_key(round_key, original_main_key, num_rounds);

    // Ajout de la clé de tour finale
    add_round_key(input_map, round_key);

    // display_map(input_map);
    // std::string output(input.size(), '0');
    return map_hex_to_str(input_map);
}

// La séquence standard est la suivante :
// SubBytes
// ShiftRows
// MixColumns
// AddRoundKey