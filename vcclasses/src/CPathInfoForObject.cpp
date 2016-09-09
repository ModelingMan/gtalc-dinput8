#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SwapConnectionsToBeRightWayRound = vcversion::AdjustOffset(0x0043C060);

__declspec(naked) void CPathInfoForObject::SwapConnectionsToBeRightWayRound(void)
{
	__asm jmp g_SwapConnectionsToBeRightWayRound;
}
