#include "vcclasses.h"
#include "vcversion.h"

char *CPad::KeyBoardCheatString = reinterpret_cast<char *>(vcversion::AdjustOffset(0x00A10942));

static unsigned long g_GetPad = vcversion::AdjustOffset(0x004AB060);
static unsigned long g_AddToPCCheatString = vcversion::AdjustOffset(0x004ABD20);

__declspec(naked) unsigned long CPad::GetPad(int)
{
	__asm jmp g_GetPad;
}

__declspec(naked) void CPad::AddToPCCheatString(char)
{
	__asm jmp g_AddToPCCheatString;
}
