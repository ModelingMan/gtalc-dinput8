#include "CGameLogicHack.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "Vehicles.h"
#include <Windows.h>

bool CGameLogicHack::isShortcutDropoffEnabled;
char CGameLogicHack::skipClearShortcutStage;

bool CGameLogicHack::initialise()
{
	// switch shortcut dropoff
	isShortcutDropoffEnabled = !!GetPrivateProfileInt("Misc", "UseShortcutDropoff", 0, "./gta-lc.ini");

	// use cabbie model
	Patch<unsigned long>(0x0042AE8D, vcversion::AdjustOffset(0x0094DDD8) + CAR_CABBIE * 0x14);
	Patch<unsigned int>(0x0042AEAC, CAR_CABBIE);
	Patch<unsigned int>(0x0042AFB3, CAR_CABBIE);
	Patch<unsigned int>(0x0042B87B, CAR_CABBIE);

	// skip clear taxi shortcut for custom opcode 036B
	skipClearShortcutStage = 0;
	InjectHook(0x00608CD9, &CGameLogicHack::ClearTaxiShotcutHack);
	InjectHook(0x00451746, &CGameLogicHack::ClearTaxiShotcutHack);

	return true;
}

void CGameLogicHack::ClearTaxiShotcutHack()
{
	if (skipClearShortcutStage) {
		skipClearShortcutStage--;
	} else {
		CGameLogic::ClearShortCut();
	}
}
