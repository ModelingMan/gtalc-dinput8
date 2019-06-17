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
		DWORD flOldProtect;
		void *address = reinterpret_cast<void *>(vcversion::AdjustOffset(0x005BE31D));
		VirtualProtect(address, 4, PAGE_EXECUTE_READWRITE, &flOldProtect);
		Patch<float>(0x005BE31D, pos.z - 0.03f);
		VirtualProtect(address, 4, flOldProtect, &flOldProtect);
	}
	CWaterLevel::RenderBoatWakes();
}
