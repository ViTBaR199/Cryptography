#pragma once
#include <iostream>
#include <bitset>
#include "ISymmetricAlgorithm.cpp"
#include "EncryptionConversion.cpp"
#include "IGeneratingRoundKeys.cpp"

class FeistelNet : public ISymmetricAlgorithm
{
private:
    IEncryptionConversion* conversion;
    IGeneratingRoundKeys* keyGen;

public:
    FeistelNet(IEncryptionConversion* conv, IGeneratingRoundKeys* kg) {
        this->conversion = conv;
        this->keyGen = kg;
    }

    virtual ~FeistelNet() {}

    virtual std::bitset<8> SymAlg(std::bitset<8> block, std::bitset<8> key) override
    {
        std::bitset<8>* roundKeys = keyGen->GenKey(key);

        // Здесь должна быть сама реализация,
        // предположительно...
        // ...

        return block;
    }
};

