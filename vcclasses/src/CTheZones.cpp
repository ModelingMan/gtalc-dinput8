#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetLevelFromPosition = vcversion::AdjustOffset(0x004DD300);

__declspec(naked) int CTheZones::GetLevelFromPosition(CVector const *)
{
	__asm jmp g_GetLevelFromPosition;
}
