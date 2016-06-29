#include "vcclasses.h"
#include "vcversion.h"

CPlayerInfo *CWorld::Players = reinterpret_cast<CPlayerInfo *>(vcversion::AdjustOffset(0x0094AD28));

static unsigned long g_FindGroundZForCoord = vcversion::AdjustOffset(0x004D5540);

__declspec(naked) float CWorld::FindGroundZForCoord(float, float)
{
	__asm jmp g_FindGroundZForCoord;
}
