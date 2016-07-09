#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GiveWeapon = vcversion::AdjustOffset(0x004FFA30);

__declspec(naked) void CPed::GiveWeapon(int, unsigned int, bool)
{
	__asm jmp g_GiveWeapon;
}
