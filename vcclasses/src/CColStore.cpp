#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_RequestCollision = vcversion::AdjustOffset(0x0062A140);

__declspec(naked) void CColStore::RequestCollision(CVector2D const&)
{
	__asm jmp g_RequestCollision;
}
