#include "CWaterLevelHack.h"
#include <Windows.h>
#include "Globals.h"
#include "SilentCall.h"

bool CWaterLevelHack::initialise()
{
	// remove horizon ships
	if (!GetPrivateProfileInt("Misc", "AllowHorizonShips", 1, "./gta-lc.ini")) {
		Patch<unsigned short>(0x005BC5BC, 0xE990); // CWaterLevel::RenderShipsOnHorizon
	}

	// dynamic boat wake height
	InjectHook(0x005C0093, &CWaterLevelHack::RenderBoatWakesHack); // CWaterLevel::RenderTransparentWater

	return true;
}

void CWaterLevelHack::RenderBoatWakesHack()
{
	CVector pos;
	VCGlobals::FindPlayerCoors(&pos);
	if (CWaterLevel::GetWaterLevelNoWaves(pos.x, pos.y, pos.z, &pos.z)) {
		Patch<float>(0x005BE31D, pos.z - 0.03f);
	}
	CWaterLevel::RenderBoatWakes();
}
