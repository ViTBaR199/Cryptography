#pragma once


class IGeneratingRoundKeys
{
public:
	virtual unsigned char** GenKey(unsigned char* key) = 0;
	IGeneratingRoundKeys();
	virtual ~IGeneratingRoundKeys();
};

