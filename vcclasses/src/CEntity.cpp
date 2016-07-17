#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_RegisterReference = vcversion::AdjustOffset(0x004C6AC0);

__declspec(naked) void CEntity::RegisterReference(CEntity **)
{
	__asm jmp g_RegisterReference;
}
