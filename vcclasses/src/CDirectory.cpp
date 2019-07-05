#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_FindItem = vcversion::AdjustOffset(0x00487220);

__declspec(naked) bool CDirectory::FindItem(const char *name, unsigned int &offset, unsigned int &size)
{
	__asm jmp g_FindItem;
}