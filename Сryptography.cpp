﻿#include <iostream>
#include <bitset>
#include "IGeneratingRoundKeys.h"
#include "EncryptionConversion.h"


unsigned int pBlock[32] = {
    16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
};


unsigned int sBlock[8][4][16] =
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


//первый номер
//unsigned char* P_block(unsigned char* arr1, unsigned char* arr2, const int size_perm) {
//    unsigned char* new_arr = new unsigned char[size_perm];
//    for (int i = 0; i < size_perm; i++) {
//        int index = arr2[i] - '0';
//        char temp = arr1[i];
//        new_arr[i] = arr1[index];
//    }
//    return new_arr;
//}

unsigned char* P_block(unsigned char array[], const unsigned int pBlock[][8]) {
    unsigned char* newArray = new unsigned char[4] {0, 0, 0, 0};

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 8; j++) {
            int bitIndex = pBlock[i][j];
            int byteIndex = bitIndex / 8;
            int offset = bitIndex % 8;

            unsigned char bit = (array[byteIndex] >> offset) & 1;
            newArray[i] |= (bit << j);  
        }
    }
    return newArray;
}

//1
std::bitset<32> p_permuntation(std::bitset<32> inputArray, unsigned int pBlock[]) {
    std::bitset<32> outputArray;

    for (int i = 0; i < 32; i++) {
        unsigned char bits = pBlock[i] - 1;
        outputArray[i] = inputArray[(int)bits];
    }
    return outputArray;
}

std::bitset<4> block_search(int block, std::bitset<2> line, std::bitset<4> column, unsigned int sBlock[][4][16]) {
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
}

//2
std::bitset<32> s_permuntation(std::bitset<48> inputArray, unsigned int sBlock[][4][16]) {
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
}

int main()
{
    /*std::bitset<32> array_of_bits{"10101110001101010101110001101011"};

    std::cout << p_permuntation(array_of_bits, pBlock) << '\n';*/

    std::bitset<48> array_of_bits{ "101011100011010101011100011010111011011101011110" };

    std::cout << s_permuntation(array_of_bits, sBlock) << '\n';
}