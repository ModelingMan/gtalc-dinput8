#pragma once

#include "vcclasses.h"

#define MAX_PROJECTILES 32

class CProjectileInfoHack : public CProjectileInfo
{
public:
	static bool initialise();

	static bool IsProjectileInRange(float x1, float y1, float z1, float x2, float y2, float z2, bool flag);
	static void UpdateHack();
};
