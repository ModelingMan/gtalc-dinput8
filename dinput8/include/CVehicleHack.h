#pragma once

#include "vcclasses.h"

class CVehicleHack : public CVehicle
{
public:
	static bool initialise();

	static void IsOpenTopCarHackProxy();
	bool IsOpenTopCarHack();
	static void AutomobilePreRenderHack();

	static void MoneyForExplosion_Inject1();
	static void MoneyForExplosion_Inject2();
	static void MoneyForCollision_Inject1();
	static void MoneyForCollision_Inject2();
	static void MoneyForCollision_Inject3();
	void AwardMoneyForCollision(float fDamageValue, bool flag);
};
