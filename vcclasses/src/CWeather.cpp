#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_ForceWeatherNow = vcversion::AdjustOffset(0x0057D550);

__declspec(naked) void CWeather::ForceWeatherNow(short)
{
	__asm jmp g_ForceWeatherNow;
}
