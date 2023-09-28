#pragma once
#include <iostream>
#include <bitset>

class IEncryptionConversion
{
public:
    virtual std::bitset<8> Conversion(std::bitset<8> block) = 0;
    IEncryptionConversion() {};
    virtual ~IEncryptionConversion() {};
};
