#include <iostream>
#include "IGeneratingRoundKeys.h"
#include "EncryptionConversion.h"

//первый номер
unsigned char* P_block(unsigned char* arr1, unsigned char* arr2, const int size_perm) {
    unsigned char* new_arr = new unsigned char[size_perm];
    for (int i = 0; i < size_perm; i++) {
        int index = arr2[i] - '0';
        char temp = arr1[i];
        new_arr[i] = arr1[index];
    }
    return new_arr;
}

//второй номер
unsigned char* S_block(unsigned char* arr1, unsigned char* arr_k, const char size_k) {
    //замена идёт по всему массиву справа налево
    unsigned char* new_arr = new unsigned char[sizeof(arr1)];
    for (int i = sizeof(arr1) - 1; i >= 0;)
    {
        for (int j = (size_k - '0') - 1; j >= 0 && i >= 0; j--)
        {
            new_arr[i] = arr_k[j];
            i--;
        }
    }
    return new_arr;
}


int main()
{
    //для 1-го задания
    const int size = 8;
    unsigned char arr1[] = { '1', '0', '1', '1', '0', '1', '0', '1' };
    unsigned char arr2[] = { '6', '4', '3', '0', '1', '7', '2', '5' };
    
    //для 2-го задания
    char k = '3';
    unsigned char arr_k[] = { '0', '1', '0' };

    //проверка первой функции
    //unsigned char* last_check = P_block(arr1, arr2, size);
    //for (int i = 0; i < sizeof(last_check); i++)
    //{
    //    std::cout << last_check[i];
    //}
    //std::cout << std::endl;

    ////проверка второй функции
    //unsigned char* ultra_last_check = S_block(arr1, arr_k, k);
    //for (int i = 0; i < sizeof(last_check); i++)
    //{
    //    std::cout << ultra_last_check[i];
    //}

}