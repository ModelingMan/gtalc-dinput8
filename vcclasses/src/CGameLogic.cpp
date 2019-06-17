#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_AddShortCutDropOffPointForMission = vcversion::AdjustOffset(0x0042ADF0);
static unsigned long g_ClearShortCut = vcversion::AdjustOffset(0x0042B730);

__declspec(naked) void CGameLogic::AddShortCutDropOffPointForMission(CVector, float)
{
	__asm jmp g_AddShortCutDropOffPointForMission;
}

__declspec(naked) void CGameLogic::ClearShortCut(void)
{
	__asm jmp g_ClearShortCut;
}
