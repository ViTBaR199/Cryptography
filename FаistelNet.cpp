#pragma once
#include <iostream>
#include <bitset>
#include "ISymmetricAlgorithm.cpp"
#include "IEncryptionConversion.cpp"
#include "IGeneratingRoundKeys.cpp"

class FeistelNet : public ISymmetricAlgorithm
{
private:
    IEncryptionConversion* conversion;
    IGeneratingRoundKeys* keyGen;
    std::bitset<64>* roundKey;

public:
    FeistelNet(IEncryptionConversion* conv, IGeneratingRoundKeys* kg) {
        this->conversion = conv;
        this->keyGen = kg;
    }

    virtual ~FeistelNet() {}

    virtual std::bitset<64> Encrypt(std::bitset<64> inputBlock) {
        uint32_t left = inputBlock.to_ullong() >> 32;
        uint32_t right = inputBlock.to_ullong() & ((1ULL << 32) - 1);    //1ULL - unsigned long long
        uint32_t nleft = 0, nright = 0;

        for (int count_round = 0; count_round < 16; count_round++) {
            nleft = right;
            nright = left ^ conversion->Conversion(right, roundKey[count_round]).to_ullong();
            left = nleft;
            right = nright;
        }

        std::bitset<64> outBlock((uint64_t(nleft) << 32) | nright);
        return outBlock;
    }

    std::bitset<64> Decrypt(std::bitset<64> inputBlock) {
        uint32_t left = inputBlock.to_ullong() >> 32;
        uint32_t right = inputBlock.to_ullong() & ((1ULL << 32) - 1);
        uint32_t nleft = 0;
        uint32_t nright = 0;

        for (int count_round = 15; count_round >= 0; count_round--) {
            nright = left;
            nleft = right ^ conversion->Conversion(left, roundKey[count_round]).to_ullong();
            left = nleft;
            right = nright;
        }

        std::bitset<64> outBlock((uint64_t(nleft) << 32) | nright);
        return outBlock;
    }

    void SetKey(std::bitset<64> key) {
        roundKey = keyGen->GenKey(key);
    }

    virtual std::bitset<64> SymAlg(std::bitset<64> block, std::bitset<64> key) override
    {
        std::bitset<64>* roundKeys = keyGen->GenKey(key);

        // Здесь должна быть сама реализация,
        // предположительно...
        // ...

        return block;
    }
};

