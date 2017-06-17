#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_constructor = vcversion::AdjustOffset(0x005B2B50);

__declspec(naked) CPlane::CPlane(int, unsigned char)
{
	__asm jmp g_constructor;
}
