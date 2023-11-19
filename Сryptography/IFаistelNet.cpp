#pragma once
#include <iostream>
#include <bitset>
#include "ISymmetricAlgorithm.cpp"
#include "IEncryptionConversion.cpp"
#include "IGeneratingRoundKeys.cpp"

class IFeistelNet : public ISymmetricAlgorithm
{
public:
    IFeistelNet() {};
    virtual ~IFeistelNet() {};
    IFeistelNet(IFeistelNet const&) = delete;
    IFeistelNet& operator=(IFeistelNet const&) = delete;
    IFeistelNet(IFeistelNet&&) = delete;
    IFeistelNet& operator=(IFeistelNet&&) = delete;
};