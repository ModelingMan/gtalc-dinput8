#pragma once

#include "renderware.h"

class CWeaponEffectsHack
{
public:
	static bool initialise();

	static void InitHackProxy(void);
	static RwTexture *InitHack(void);
};
