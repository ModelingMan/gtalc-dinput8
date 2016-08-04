#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetHasCollidedWith = vcversion::AdjustOffset(0x004B9010);

__declspec(naked) bool CPhysical::GetHasCollidedWith(CEntity *)
{
	__asm jmp g_GetHasCollidedWith;
}
