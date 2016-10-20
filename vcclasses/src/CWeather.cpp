#include "vcclasses.h"
#include "vcversion.h"

float &CWeather::Foggyness = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0094DDC0));
float &CWeather::WetRoads = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009B6A9C));
bool &CWeather::bScriptsForceRain = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B38));

static unsigned long g_ForceWeatherNow = vcversion::AdjustOffset(0x0057D550);

__declspec(naked) void CWeather::ForceWeatherNow(short)
{
	__asm jmp g_ForceWeatherNow;
}
