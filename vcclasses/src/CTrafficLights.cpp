#include "vcclasses.h"
#include "vcversion.h"

bool &CTrafficLights::bGreenLightsCheat = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10ADC));

static unsigned long g_LightForPeds = vcversion::AdjustOffset(0x00465BE0);

__declspec(naked) unsigned char CTrafficLights::LightForPeds(void)
{
	__asm jmp g_LightForPeds;
}
