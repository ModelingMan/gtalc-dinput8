#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_constructor = vcversion::AdjustOffset(0x00615740);

__declspec(naked) CBike::CBike(int, unsigned char)
{
	__asm jmp g_constructor;
}
