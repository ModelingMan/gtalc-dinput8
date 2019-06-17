#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_RegisterOne = vcversion::AdjustOffset(0x00570FA0);

__declspec(naked) void CMoneyMessages::RegisterOne(CVector, char *, unsigned char, unsigned char, unsigned char, float, float)
{
	__asm jmp g_RegisterOne;
}
