#pragma once

#include "vcclasses.h"

class CVehicleHack : public CVehicle
{
public:
	static bool initialise();

	static void IsOpenTopCarHackProxy();
	bool IsOpenTopCarHack();
	static void AutomobilePreRenderHack();
};
