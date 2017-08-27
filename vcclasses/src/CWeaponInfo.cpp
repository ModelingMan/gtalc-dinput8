#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetWeaponInfo = vcversion::AdjustOffset(0x005D5710);

__declspec(naked) CWeaponInfo *CWeaponInfo::GetWeaponInfo(int)
{
	__asm jmp g_GetWeaponInfo;
}
