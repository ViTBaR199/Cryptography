#pragma once
#include <iostream>
#include <bitset>
#include "ISymmetricAlgorithm.cpp"
#include "IEncryptionConversion.cpp"
#include "IGeneratingRoundKeys.cpp"

class IFeistelNet : public ISymmetricAlgorithm
{
private:
    IEncryptionConversion* conversion;
    IGeneratingRoundKeys* keyGen;

public:
    IFeistelNet(IEncryptionConversion* conv, IGeneratingRoundKeys* kg);

    virtual ~IFeistelNet()
    {
        delete conversion;
        delete keyGen;
    }

    IFeistelNet(IFeistelNet const&) = delete;
    IFeistelNet& operator=(IFeistelNet const&) = delete;
    IFeistelNet(IFeistelNet&&) = delete;
    IFeistelNet& operator=(IFeistelNet&&) = delete;

    virtual std::bitset<64> Encrypt(std::bitset<64> block, std::bitset<64> key) = 0;
    virtual std::bitset<64> Decrypt(std::bitset<64> block, std::bitset<64> key) = 0;
};