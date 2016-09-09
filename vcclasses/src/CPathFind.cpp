#include "vcclasses.h"
#include "vcversion.h"

CPathInfoForObject *&CPathFind::InfoForTileCars = *reinterpret_cast<CPathInfoForObject **>(vcversion::AdjustOffset(0x009785E8));
CPathInfoForObject *&CPathFind::InfoForTilePeds = *reinterpret_cast<CPathInfoForObject **>(vcversion::AdjustOffset(0x00978678));

static unsigned long g_StoreDetachedNodeInfoPed = vcversion::AdjustOffset(0x00435FA0);

__declspec(naked) void CPathFind::StoreDetachedNodeInfoPed(int, char, int, float, float, float, float, bool, bool, bool, unsigned char)
{
	__asm jmp g_StoreDetachedNodeInfoPed;
}
