#include "vcclasses.h"
#include "vcversion.h"

float &CWeather::Foggyness = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0094DDC0));
float &CWeather::Rain = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00975340));
float &CWeather::InterpolationValue = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009787D8));
float &CWeather::WetRoads = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009B6A9C));
short &CWeather::NewWeatherType = *reinterpret_cast<short *>(vcversion::AdjustOffset(0x00A10A2E));
short &CWeather::ForcedWeatherType = *reinterpret_cast<short *>(vcversion::AdjustOffset(0x00A10A42));
short &CWeather::OldWeatherType = *reinterpret_cast<short *>(vcversion::AdjustOffset(0x00A10AAA));
bool &CWeather::bScriptsForceRain = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10B38));

static unsigned long g_ForceWeatherNow = vcversion::AdjustOffset(0x0057D550);

__declspec(naked) void CWeather::ForceWeatherNow(short)
{
	__asm jmp g_ForceWeatherNow;
}
