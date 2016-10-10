#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_AddObject = vcversion::AdjustOffset(0x004E8920);

__declspec(naked) void CParticleObject::AddObject(unsigned short, CVector const &, unsigned char)
{
	__asm jmp g_AddObject;
}
