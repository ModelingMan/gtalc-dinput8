#pragma once

#include "vcclasses.h"

class CObjectHack : public CObject
{
public:
	static short nBodyCastHealth;

	static bool initialise();
	static void InitHackProxy();
	void InitHack();
	void ObjectDamageHack(float);
};
