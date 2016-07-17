#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetPad = vcversion::AdjustOffset(0x004AB060);

__declspec(naked) unsigned long CPad::GetPad(int)
{
	__asm jmp g_GetPad;
}
