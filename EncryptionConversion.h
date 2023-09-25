#pragma once


class IEncryptionConversion
{
public:
	virtual unsigned char* Conversion(unsigned char* block) = 0;
	IEncryptionConversion();
	virtual ~IEncryptionConversion();
};

