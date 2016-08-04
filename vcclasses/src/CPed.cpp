#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetAmmo = vcversion::AdjustOffset(0x004FF780);
static unsigned long g_GiveWeapon = vcversion::AdjustOffset(0x004FFA30);
static unsigned long g_IsPedInControl = vcversion::AdjustOffset(0x00501950);
static unsigned long g_Say = vcversion::AdjustOffset(0x005226B0);

__declspec(naked) void CPed::SetAmmo(int, unsigned int)
{
	__asm jmp g_SetAmmo;
}

__declspec(naked) void CPed::GiveWeapon(int, unsigned int, bool)
{
	__asm jmp g_GiveWeapon;
}

__declspec(naked) bool CPed::IsPedInControl(void)
{
	__asm jmp g_IsPedInControl;
}

__declspec(naked) void CPed::Say(unsigned short)
{
	__asm jmp g_Say;
}
