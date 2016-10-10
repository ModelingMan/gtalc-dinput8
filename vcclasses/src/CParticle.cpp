#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_AddParticle = vcversion::AdjustOffset(0x00563CC0);

__declspec(naked) void CParticle::AddParticle(int, CVector const &, CVector const &, CEntity *, float, RwRGBA const &, int, int, int, int)
{
	__asm jmp g_AddParticle;
}
