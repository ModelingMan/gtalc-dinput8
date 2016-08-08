#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetBlipSprite = vcversion::AdjustOffset(0x004C3780);
static unsigned long g_ChangeBlipScale = vcversion::AdjustOffset(0x004C3840);
static unsigned long g_SetEntityBlip = vcversion::AdjustOffset(0x004C3B40);
static unsigned long g_SetShortRangeCoordBlip = vcversion::AdjustOffset(0x004C3C00);
static unsigned long g_GetActualBlipArrayIndex = vcversion::AdjustOffset(0x004C5D70);

__declspec(naked) void CRadar::SetBlipSprite(int, int)
{
	__asm jmp g_SetBlipSprite;
}

__declspec(naked) void CRadar::ChangeBlipScale(int, int)
{
	__asm jmp g_ChangeBlipScale;
}

__declspec(naked) int CRadar::SetEntityBlip(int, int, int, int)
{
	__asm jmp g_SetEntityBlip;
}

__declspec(naked) int CRadar::SetShortRangeCoordBlip(int, float, float, float, int, int)
{
	__asm jmp g_SetShortRangeCoordBlip;
}

__declspec(naked) int CRadar::GetActualBlipArrayIndex(int)
{
	__asm jmp g_GetActualBlipArrayIndex;
}
