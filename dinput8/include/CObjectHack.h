#pragma once

#include "vcclasses.h"

class CObjectHack : public CObject
{
public:
	static bool initialise();

	static short nBodyCastHealth;

	static void InitHackProxy();
	void InitHack();
	void ObjectDamageHack(float);
};
