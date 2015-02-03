#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_Get = vcversion::AdjustOffset(0x00584F30);

__declspec(naked) wchar_t *CText::Get(const char *)
{
	__asm jmp g_Get;
}