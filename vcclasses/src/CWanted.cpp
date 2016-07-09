#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetWantedLevelCheat = vcversion::AdjustOffset(0x004D1F80);

__declspec(naked) void CWanted::SetWantedLevelCheat(int)
{
	__asm jmp g_SetWantedLevelCheat;
}
