#pragma once
#include <iostream>
#include <bitset>

class ISymmetricAlgorithm
{
public:
    virtual std::bitset<8> SymAlg(std::bitset<8> block, std::bitset<8> key) = 0;
    ISymmetricAlgorithm() {};
    virtual ~ISymmetricAlgorithm() {};
};

