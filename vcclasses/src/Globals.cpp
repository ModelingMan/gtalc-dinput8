#include "Globals.h"
#include "vcversion.h"

namespace VCGlobals
{
	CCamera& TheCamera = *reinterpret_cast<CCamera *>(vcversion::AdjustOffset(0x007E4688));
	CText& TheText = *reinterpret_cast<CText *>(vcversion::AdjustOffset(0x0094B220));
	cDMAudio& DMAudio = *reinterpret_cast<cDMAudio *>(vcversion::AdjustOffset(0x00A10B8A));
	cSampleManager& SampleManager = *reinterpret_cast<cSampleManager *>(vcversion::AdjustOffset(0x00983B90));

	char *ScrollCharSet = reinterpret_cast<char *>(vcversion::AdjustOffset(0x00696674));

	ScriptParameter *ScriptParams = reinterpret_cast<ScriptParameter *>(vcversion::AdjustOffset(0x007D7438));

	RsGlobalType& Globals = *reinterpret_cast<RsGlobalType *>(vcversion::AdjustOffset(0x009B48D8));

	float &timeScale = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0097F264));

	CPlayerPed *(*g_pFindPlayerPed)() = *reinterpret_cast<CPlayerPed *(*)()>(vcversion::AdjustOffset(0x004BC120));
	CPlayerPed *FindPlayerPed()
	{
		return g_pFindPlayerPed();
	}

	CVehicle *(*g_pFindPlayerVehicle)() = *reinterpret_cast<CVehicle *(*)()>(vcversion::AdjustOffset(0x004BC1E0));
	CVehicle *FindPlayerVehicle()
	{
		return g_pFindPlayerVehicle();
	}
}
