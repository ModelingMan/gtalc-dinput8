#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetHasCollidedWith = vcversion::AdjustOffset(0x004B9010);
static unsigned long g_RemoveAndAdd = vcversion::AdjustOffset(0x004BAEE0);

__declspec(naked) bool CPhysical::GetHasCollidedWith(CEntity *)
{
	__asm jmp g_GetHasCollidedWith;
}

__declspec(naked) void CPhysical::RemoveAndAdd(void)
{
	__asm jmp g_RemoveAndAdd;
}
