#pragma once

#include "vcclasses.h"

class CGaragesHack : public CGarages
{
public:
	static bool initialise();
	static bool HasImportExportGarageCollectedThisCar(short index, int slot); // CGarages::HasImportExportGarageCollectedThisCar
	static void InitHack();
};

class CGarageHack : public CGarage
{
public:
	void MarkThisCarAsCollectedForCraig(int model);           // CGarage::MarkThisCarAsCollectedForCraig
	bool HasCraigCollectedThisCar(int model);                 // CGarage::HasCraigCollectedThisCar
	bool DoesCraigNeedThisCar(int model);                     // CGarage::DoesCraigNeedThisCar
	static void UpdateType7HackProxy(void);
	void UpdateType7Hack(void);
	static void UpdateType14HackProxy(void);
	void UpdateType14Hack(void);
	float CalcDistToGarageRectangleSquared(float x, float y); // CGarage::CalcDistToGarageRectangleSquared
	static void UpdateType5HackProxy(void);
	static bool UpdateType5Hack(int);
	static void SprayShopCostHack();
	static void SprayShopCostHack2();
};
