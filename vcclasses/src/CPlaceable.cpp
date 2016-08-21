#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_IsWithinArea_3d = vcversion::AdjustOffset(0x004BB900);
static unsigned long g_IsWithinArea_2d = vcversion::AdjustOffset(0x004BB9E0);

__declspec(naked) bool CPlaceable::IsWithinArea(float, float, float, float, float, float)
{
	__asm jmp g_IsWithinArea_3d;
}

__declspec(naked) bool CPlaceable::IsWithinArea(float, float, float, float)
{
	__asm jmp g_IsWithinArea_2d;
}
