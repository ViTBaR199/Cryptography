#pragma once
#include <iostream>
#include <bitset>

class IGeneratingRoundKeys
{
public:
    virtual std::bitset<8>* GenKey(std::bitset<8> key) = 0;
    IGeneratingRoundKeys() {};
    virtual ~IGeneratingRoundKeys() {};
};

