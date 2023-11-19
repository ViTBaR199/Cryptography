#pragma once
#include <iostream>
#include <bitset>

class IGeneratingRoundKeys
{
public:
    virtual std::bitset<48>* GenKey(std::bitset<64> key) = 0;
    IGeneratingRoundKeys() {};
    virtual ~IGeneratingRoundKeys() {};
};

