#pragma once

#include "vcclasses.h"

class CShinyTextsHack : public CShinyTexts
{
public:
	static bool initialise();

	static void RegisterOne(CVector, CVector, CVector, CVector, float, float, float, float, float, float, float, float, unsigned char, unsigned char, unsigned char, unsigned char, float);
	static void RegisterOneCallProxy();
	static void RegisterOneCall(CMatrix &);
};
