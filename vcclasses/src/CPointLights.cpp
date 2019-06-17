#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_AddLight = vcversion::AdjustOffset(0x00567700);

__declspec(naked) void CPointLights::AddLight(unsigned char, CVector, CVector, float, float, float, float, unsigned char, bool)
{
	__asm jmp g_AddLight;
}
