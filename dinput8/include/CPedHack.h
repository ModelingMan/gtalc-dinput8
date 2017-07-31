#pragma once

#include "vcclasses.h"

class CPedHack : CPed
{
public:
	static bool initialise();

	static void ServiceTalkingHackProxy();
	void ServiceTalkingHack();
	static void InflictDamageHack();
};
