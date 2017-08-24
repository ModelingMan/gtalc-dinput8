#include "vcclasses.h"
#include "vcversion.h"

bool &CWeapon::bPhotographHasBeenTaken = *reinterpret_cast<bool *>(vcversion::AdjustOffset(0x00A10AF4));

static unsigned long g_Shutdown = vcversion::AdjustOffset(0x005D4C90);

__declspec(naked) void CWeapon::Shutdown(void)
{
	__asm jmp g_Shutdown;
}
