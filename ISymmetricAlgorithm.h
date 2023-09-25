#pragma once


class ISymmetricAlgorithm
{
	virtual unsigned char* SymAlg(unsigned char* block, unsigned char* key) = 0;
	ISymmetricAlgorithm();
	virtual ~ISymmetricAlgorithm();
};

