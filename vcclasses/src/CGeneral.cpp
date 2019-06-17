#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetATanOfXY = vcversion::AdjustOffset(0x004A55E0);

__declspec(naked) float CGeneral::GetATanOfXY(float, float)
{
	__asm jmp g_GetATanOfXY;
}
