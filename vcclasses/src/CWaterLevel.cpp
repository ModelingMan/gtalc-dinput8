#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_RenderBoatWakes = vcversion::AdjustOffset(0x005BE2F0);
static unsigned long g_GetWaterLevelNoWaves = vcversion::AdjustOffset(0x005C2BE0);

__declspec(naked) void CWaterLevel::RenderBoatWakes(void)
{
	__asm jmp g_RenderBoatWakes;
}

__declspec(naked) bool CWaterLevel::GetWaterLevelNoWaves(float, float, float, float *)
{
	__asm jmp g_GetWaterLevelNoWaves;
}
