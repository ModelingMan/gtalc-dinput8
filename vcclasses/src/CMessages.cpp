#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_AddToPreviousBriefArray = vcversion::AdjustOffset(0x00583DE0);

__declspec(naked) void CMessages::AddToPreviousBriefArray(wchar_t *, int, int, int, int, int, int, unsigned short *)
{
	__asm jmp g_AddToPreviousBriefArray;
}