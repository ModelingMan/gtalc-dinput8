#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_CamShake = vcversion::AdjustOffset(0x0046FF21);

__declspec(naked) void CCamera::CamShake(float, float, float, float)
{
	__asm jmp g_CamShake;
}
