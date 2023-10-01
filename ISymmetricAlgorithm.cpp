#pragma once
#include <iostream>
#include <bitset>

class ISymmetricAlgorithm
{
public:
    virtual std::bitset<64> SymAlg(std::bitset<64> block, std::bitset<64> key) = 0;
    ISymmetricAlgorithm() {};
    virtual ~ISymmetricAlgorithm() {};
};

