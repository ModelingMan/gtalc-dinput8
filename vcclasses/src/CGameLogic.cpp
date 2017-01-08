#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_AddShortCutDropOffPointForMission = vcversion::AdjustOffset(0x0042ADF0);

__declspec(naked) void CGameLogic::AddShortCutDropOffPointForMission(CVector, float)
{
	__asm jmp g_AddShortCutDropOffPointForMission;
}
