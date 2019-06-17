#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_RemoveEntityFromList = vcversion::AdjustOffset(0x004518E0);

__declspec(naked) void CMissionCleanup::RemoveEntityFromList(int, unsigned char)
{
	__asm jmp g_RemoveEntityFromList;
}
