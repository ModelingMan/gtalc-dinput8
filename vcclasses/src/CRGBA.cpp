#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_constructor = vcversion::AdjustOffset(0x00541570);

__declspec(naked) CRGBA::CRGBA(unsigned char, unsigned char, unsigned char, unsigned char)
{
	__asm jmp g_constructor;
}
