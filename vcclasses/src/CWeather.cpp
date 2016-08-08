#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CWeather::bScriptsForceRain = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10B38));

static unsigned long g_ForceWeatherNow = vcversion::AdjustOffset(0x0057D550);

__declspec(naked) void CWeather::ForceWeatherNow(short)
{
	__asm jmp g_ForceWeatherNow;
}
