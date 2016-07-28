#pragma once

#include "vcclasses.h"

class CGaragesHack : public CGarages
{
public:
	static bool initialise();
	static bool HasImportExportGarageCollectedThisCar(short index, int slot);
};

class CGarageHack : public CGarage
{
public:
	void MarkThisCarAsCollectedForCraig(int model);
	bool HasThisCarBeenCollected(int model);
	bool HasThisCarNotBeenCollected(int model);
	static void UpdateType7HackProxy(void);
	void UpdateType7Hack(void);
	static void UpdateType14HackProxy(void);
	void UpdateType14Hack(void);
	float ProximityToGarageArea(float x, float y);
};
