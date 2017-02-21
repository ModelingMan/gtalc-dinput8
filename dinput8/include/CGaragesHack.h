#pragma once

#include "vcclasses.h"

class CGaragesHack : public CGarages
{
public:
	static bool initialise();
	static bool HasImportExportGarageCollectedThisCar(short index, int slot);
	static void InitHack();
};

class CGarageHack : public CGarage
{
public:
	void MarkThisCarAsCollectedForCraig(int model);
	bool HasCraigCollectedThisCar(int model);
	bool DoesCraigNeedThisCar(int model);
	static void UpdateType7HackProxy(void);
	void UpdateType7Hack(void);
	static void UpdateType14HackProxy(void);
	void UpdateType14Hack(void);
	float CalcDistToGarageRectangleSquared(float x, float y);
	static void UpdateType5HackProxy(void);
	static bool UpdateType5Hack(int);
};
