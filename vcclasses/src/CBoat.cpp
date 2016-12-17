#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_constructor = vcversion::AdjustOffset(0x005A6470);

__declspec(naked) CBoat::CBoat(int, unsigned char)
{
	__asm jmp g_constructor;
}
