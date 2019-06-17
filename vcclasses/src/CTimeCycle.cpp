#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_StopExtraColour = vcversion::AdjustOffset(0x004CE9E0);
static unsigned long g_StartExtraColour = vcversion::AdjustOffset(0x004CEA00);
static unsigned long g_Interpolate = vcversion::AdjustOffset(0x004D0560);

__declspec(naked) void CTimeCycle::StopExtraColour(bool)
{
	__asm jmp g_StopExtraColour;
}

__declspec(naked) void CTimeCycle::StartExtraColour(int, bool)
{
	__asm jmp g_StartExtraColour;
}

__declspec(naked) float CTimeCycle::Interpolate(unsigned char *, unsigned char *)
{
	__asm jmp g_Interpolate;
}
