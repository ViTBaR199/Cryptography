#pragma once
#include <iostream>
#include <bitset>

class IEncryptionConversion
{
public:
    virtual std::bitset<32> Conversion(std::bitset<32> inputBlock, std::bitset<48> key) = 0;
    IEncryptionConversion() {};
    virtual ~IEncryptionConversion() {};
};
