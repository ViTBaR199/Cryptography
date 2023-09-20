#include <iostream>

//первый номер
void P_block(unsigned char* arr1, unsigned char* arr2, const int size_perm) {
    for (int i = 0; i < size_perm; i++) {
        int index = arr2[i] - '0';
        char temp = arr1[i];
        arr2[i] = arr1[index];

        std::cout << arr2[i];
    }
    std::cout << "\n";
}

//второй номер
void S_block(unsigned char* arr1, unsigned char* arr_k, const char size_k) {
    //замена идёт по всему массиву справа налево
    for (int i = sizeof(arr1) - 1; i >= 0;)
    {
        for (int j = (size_k - '0') - 1; j >= 0 && i >= 0; j--)
        {
            arr1[i] = arr_k[j];
            i--;
        }
    }

    for (int i = 0; i < sizeof(arr1); i++)
    {
        std::cout << arr1[i];
    }

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

    P_block(arr1, arr2, size);   
    std::cout << '\n';
    S_block(arr1, arr_k, k);
    
    return 0;
}