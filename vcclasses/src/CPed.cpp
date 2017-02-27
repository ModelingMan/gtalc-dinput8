#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_ClearFollowPath = vcversion::AdjustOffset(0x004F7920);
static unsigned long g_SetAmmo = vcversion::AdjustOffset(0x004FF780);
static unsigned long g_GrantAmmo = vcversion::AdjustOffset(0x004FF840);
static unsigned long g_GiveWeapon = vcversion::AdjustOffset(0x004FFA30);
static unsigned long g_IsPedInControl = vcversion::AdjustOffset(0x00501950);
static unsigned long g_AddInCarAnims = vcversion::AdjustOffset(0x00512520);
static unsigned long g_SetObjective = vcversion::AdjustOffset(0x00521F10);
static unsigned long g_Say = vcversion::AdjustOffset(0x005226B0);

__declspec(naked) void CPed::ClearFollowPath(void)
{
	__asm jmp g_ClearFollowPath;
}

__declspec(naked) void CPed::SetAmmo(int, unsigned int)
{
	__asm jmp g_SetAmmo;
}

__declspec(naked) void CPed::GrantAmmo(int, unsigned int)
{
	__asm jmp g_GrantAmmo;
}

__declspec(naked) void CPed::GiveWeapon(int, unsigned int, bool)
{
	__asm jmp g_GiveWeapon;
}

__declspec(naked) bool CPed::IsPedInControl(void)
{
	__asm jmp g_IsPedInControl;
}

__declspec(naked) void CPed::AddInCarAnims(CVehicle *, bool)
{
	__asm jmp g_AddInCarAnims;
}

__declspec(naked) void CPed::SetObjective(unsigned int, void *)
{
	__asm jmp g_SetObjective;
}

__declspec(naked) void CPed::Say(unsigned short)
{
	__asm jmp g_Say;
}
