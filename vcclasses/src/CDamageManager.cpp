#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetEngineStatus = vcversion::AdjustOffset(0x005A97F0);
static unsigned long g_SetWheelStatus = vcversion::AdjustOffset(0x005A9840);

__declspec(naked) void CDamageManager::SetEngineStatus(unsigned int)
{
	__asm jmp g_SetEngineStatus;
}

__declspec(naked) void CDamageManager::SetWheelStatus(int, unsigned int)
{
	__asm jmp g_SetWheelStatus;
}
