﻿#include <iostream>
#include <fstream>
#include <bitset>
#include "IGeneratingRoundKeys.cpp"
#include "IEncryptionConversion.cpp"
#include "ISymmetricAlgorithm.cpp"
#include "IFаistelNet.cpp"

uint8_t pBlock[32] = {
    15, 6, 19, 20, 28, 11, 27, 16, 0, 14, 22, 25, 4, 17, 30, 9,
    1, 7, 23, 13, 31, 26, 2, 8, 18, 12, 29, 5, 21, 10, 3, 24
};

uint8_t sBlock[8][4][16] =
{
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};


//определение перестановки расширенного ключа
uint8_t C1[28]{
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36
};

uint8_t D1[28]{
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};
//ключ ki выбирается из перечисленных битов
uint8_t CDi[]{
    13, 16, 10, 23, 0, 4, 2, 27, 14, 5, 20, 9, 22, 18, 11, 3,
    25, 7, 15, 6, 26, 19, 12, 1, 40, 51, 30, 36, 46, 54, 29, 39,
    50, 44, 32, 47, 43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31
};
//расширение E
uint8_t ExpansionE[] = {
    31, 0, 1, 2, 3, 4,
    3, 4, 5, 6, 7, 8,
    7, 8, 9, 10, 11, 12,
    11, 12, 13, 14, 15, 16,
    15, 16, 17, 18, 19, 20,
    19, 20, 21, 22, 23, 24,
    23, 24, 25, 26, 27, 28,
    27, 28, 29, 30, 31, 0
};

//1
template <size_t T, size_t N>
std::bitset<T> p_permuntation(std::bitset<N> inputArray, uint8_t (&pBlock)[T]) {
    std::bitset<T> outputArray;

    for (int i = 0; i < T; i++) {
        outputArray[i] = inputArray[(int)pBlock[i]];
    }
    return outputArray;
};

std::bitset<4> block_search(int block, std::bitset<2> line, std::bitset<4> column, uint8_t sBlock[][4][16]) {
    for (int i = 0, j = 0; i < 4, j < 16; ) {
        if (((std::bitset<2>)i != line) && (std::bitset<4>)j != column) {
            i++;
            j++;
        }
        else if ((std::bitset<2>)i != line) {
            i++;
        }
        else if ((std::bitset<4>)j != column) {
            j++;
        }
        else {
            return (std::bitset<4>)sBlock[block][i][j];
        }
    }
};

//2
std::bitset<32> s_permuntation(std::bitset<48> inputArray, uint8_t sBlock[][4][16]) {
    std::bitset<4> blockArray;
    std::bitset<32> outputArray;

    for (int first = 0, i = 0; i < 8; i++, first += 6) {
        //inputArray[i+1]
        blockArray = block_search(i,
            (inputArray[first] | (inputArray[first + 5] << 1)),
            (inputArray[first + 1] | (inputArray[first + 2] << 1) | (inputArray[first + 3] << 2) | (inputArray[first + 4] << 3)),
            sBlock);

        for (int j = 0; j < blockArray.size(); j++)
        {
            outputArray |= (blockArray[j] << (j + (4 * i)));
        }

        //std::cout << nline << std::endl;
    }
    return outputArray;
};



//реализация генерации раундовых ключей
class GeneratingRoundKeys : IGeneratingRoundKeys {
private:
    static uint8_t CyclBitShift[]; //таблица битов циклического сдвига

public:
    std::bitset<48>* GenKey(std::bitset<64> key) {
        std::bitset<48>* roundKeys = new std::bitset<48>[16];
        auto permuntKeyC = p_permuntation<sizeof(C1)>(key, C1);
        auto permuntKeyD = p_permuntation<sizeof(D1)>(key, D1);

        for (int round = 0; round < 16; round++){
            auto shift = CyclBitShift[round];
            permuntKeyC = (permuntKeyC << shift) | (permuntKeyC >> (28 - shift));
            permuntKeyD = (permuntKeyD << shift) | (permuntKeyD >> (28 - shift));

            std::bitset<56> keyCD = ((permuntKeyD.to_ullong()) << 28) | permuntKeyC.to_ullong();
            roundKeys[round] = p_permuntation<sizeof(CDi)>(keyCD, CDi);
        }
        return roundKeys;
    }
};

uint8_t GeneratingRoundKeys::CyclBitShift[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};



//реализация шифрующего преобразования
class EncryptionConversion : IEncryptionConversion {
public:
    std::bitset<32> Conversion(std::bitset<32> inputArray, std::bitset<48> key) {
        auto expanBlock = p_permuntation<sizeof(ExpansionE)>(inputArray, ExpansionE);
        auto e_block = expanBlock ^ key;
        auto s_block = s_permuntation(e_block, sBlock);
        auto p_block = p_permuntation<sizeof(pBlock)>(s_block, pBlock);
        
        return p_block;
    }
};



class FeistelNet : public ISymmetricAlgorithm
{
private:
    EncryptionConversion* conversion;
    GeneratingRoundKeys* keyGen;

public:

    FeistelNet() {
        conversion = new EncryptionConversion();
        keyGen = new GeneratingRoundKeys();
    }

    virtual ~FeistelNet()
    {
        delete conversion;
        delete keyGen;
    }


    std::bitset<64> Encrypt(std::bitset<64> inputBlock, std::bitset<64> key) {
        uint32_t left = inputBlock.to_ullong() >> 32;
        uint32_t right = inputBlock.to_ullong() & ((1ULL << 32) - 1);    //1ULL - unsigned long long
        uint32_t nleft = 0, nright = 0;
        auto roundKey = keyGen->GenKey(key);

        for (int count_round = 0; count_round < 16; count_round++) {
            nleft = right;
            nright = left ^ conversion->Conversion(right, roundKey[count_round]).to_ullong();
            left = nleft;
            right = nright;
        }

        std::bitset<64> outBlock((uint64_t(nleft) << 32) | nright);
        return outBlock;
    }

    std::bitset<64> Decrypt(std::bitset<64> inputBlock, std::bitset<64> key) {
        uint32_t left = inputBlock.to_ullong() >> 32;
        uint32_t right = inputBlock.to_ullong() & ((1ULL << 32) - 1);
        uint32_t nleft = 0, nright = 0;
        auto roundKey = keyGen->GenKey(key);

        for (int count_round = 15; count_round >= 0; count_round--) {
            nright = left;
            nleft = right ^ conversion->Conversion(left, roundKey[count_round]).to_ullong();
            left = nleft;
            right = nright;
        }

        std::bitset<64> outBlock((uint64_t(nleft) << 32) | nright);
        return outBlock;
    }
};



int main()
{
    /*std::bitset<32> array_of_bits{"10101110001101010101110001101011"};

    std::cout << p_permuntation<32>(array_of_bits, pBlock, sizeof(pBlock)) << '\n';*/


    /*std::bitset<48> array_of_bits{ "101011100011010101011100011010111011011101011110" };

    std::cout << s_permuntation(array_of_bits, sBlock) << '\n';*/


    /*std::bitset<64> array_of_bits{ "1010111000110101010111000110101001001011000101001110101111111100" };

    std::cout << p_permuntation<28>(array_of_bits, C1) << '\n';*/


    /*GeneratingRoundKeys gen;
    EncryptionConversion enc;
    std::bitset<64> key{ "1010111000110101010111000110101001001011000101001110101111111100" };
    std::bitset<32> arr{ "10100101001110101010111010101001" };
    auto roundKeys = gen.GenKey(key);
    for (int i = 0; i < 16; i++) {
        std::cout << "Round " << i + 1 << ": " << roundKeys[i] << '\n';
    }

    auto encrypt = enc.Conversion(arr, roundKeys[0]);
    std::cout << "Encryption Conversion: " << encrypt << std::endl;

    delete[] roundKeys;*/


    /*std::bitset<64> arr{ "1010110010101010101010101010100101111010101001011010100100111010" };
    std::bitset<64> key{ "1010111000110101010111000110101001001011000101001110101111111100" };
    FeistelNet test;
    auto encrypted = test.Encrypt(arr, key);
    auto decrypted = test.Decrypt(encrypted, key);

    std::cout << "Encrypted data: " << encrypted << "\nInput array:    " << arr << "\nDecrypted data: " << decrypted << std::endl;*/


    std::ifstream file("Test.txt", std::ios::binary | std::ios::ate);
    std::bitset<64> arr;
    int byte_counter = 0;

    std::bitset<64> key{ "1010111000110101010111000110101001001011000101001110101111111100" };

    if (!file.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    std::streamsize size = file.tellg(); //размер файла в байтах
    file.seekg(0, std::ios::beg);//возвращение в начало файла (чтобы можно было начать чтение)

    uint64_t buffer;
    while (file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {
        std::bitset<64> bits(buffer);

        FeistelNet test;

        //создание файла и запись в него шифрования исходного файла
        std::ofstream out_e("Encryption_result.bin", std::ios::binary | std::ios::app);
        auto encrypted = test.Encrypt(bits, key);
        uint64_t buffer_e = encrypted.to_ullong();
        out_e.write(reinterpret_cast<char*>(&buffer_e), sizeof(buffer_e));


        //создание файла и запись в него дешифрованного файла шифрования
        std::ofstream out_d("Decryption_result.bin", std::ios::binary | std::ios::app);
        auto decrypted = test.Decrypt(encrypted, key);
        uint64_t buffer_d = decrypted.to_ullong();
        out_d.write(reinterpret_cast<char*>(&buffer_d), sizeof(buffer_d));

        //std::cout << bits << std::endl;
    }
    
    

    file.close();
    return 0;
    
}