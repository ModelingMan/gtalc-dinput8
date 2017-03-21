#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_Interpolate = vcversion::AdjustOffset(0x004D0560);

__declspec(naked) float CTimeCycle::Interpolate(unsigned char *, unsigned char *)
{
	__asm jmp g_Interpolate;
}
