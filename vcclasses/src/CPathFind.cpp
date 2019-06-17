#include "vcclasses.h"
#include "vcversion.h"

CPathInfoForObject *&CPathFind::InfoForTileCars = *reinterpret_cast<CPathInfoForObject **>(vcversion::AdjustOffset(0x009785E8));
CPathInfoForObject *&CPathFind::InfoForTilePeds = *reinterpret_cast<CPathInfoForObject **>(vcversion::AdjustOffset(0x00978678));

static unsigned long g_FindNodeCoorsForScript = vcversion::AdjustOffset(0x00435280);
static unsigned long g_StoreDetachedNodeInfoPed = vcversion::AdjustOffset(0x00435FA0);
static unsigned long g_FindNthNodeClosestToCoors = vcversion::AdjustOffset(0x00437070);

__declspec(naked) void CPathFind::FindNodeCoorsForScript(CVector &, int)
{
	__asm jmp g_FindNodeCoorsForScript;
}

__declspec(naked) void CPathFind::StoreDetachedNodeInfoPed(int, char, int, float, float, float, float, bool, bool, bool, unsigned char)
{
	__asm jmp g_StoreDetachedNodeInfoPed;
}

__declspec(naked) int CPathFind::FindNthNodeClosestToCoors(CVector, unsigned char, float, bool, bool, int, bool)
{
	__asm jmp g_FindNthNodeClosestToCoors;
}
