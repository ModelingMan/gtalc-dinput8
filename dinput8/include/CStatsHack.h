#pragma once

#include "vcclasses.h"

class CStatsHack : public CStats
{
public:
	static bool initialise();
	static void MissionsPassedHack();
	static void HighestLevelFireMissionHack();
	static void StoresKnockedOffHack();
	static void AssassinationsHack();
};
