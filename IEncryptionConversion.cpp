#pragma once
#include <iostream>
#include <bitset>

class IEncryptionConversion
{
public:
    virtual std::bitset<64> Conversion(std::bitset<64> inputBlock, std::bitset<64> block) = 0;
    IEncryptionConversion() {};
    virtual ~IEncryptionConversion() {};
};
