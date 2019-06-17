#pragma once

#include "vcclasses.h"

class CWeaponHack : public CWeapon
{
public:
	static bool initialise();

	bool IsType2Handed(void);
};
