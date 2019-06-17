#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_Normalise = vcversion::AdjustOffset(0x004DFEA0);

__declspec(naked) void CVector::Normalise(void)
{
	__asm jmp g_Normalise;
}
