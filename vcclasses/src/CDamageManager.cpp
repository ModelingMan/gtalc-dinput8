#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_SetEngineStatus = vcversion::AdjustOffset(0x005A97F0);
static unsigned long g_SetWheelStatus = vcversion::AdjustOffset(0x005A9840);
static unsigned long g_GetEngineStatus = vcversion::AdjustOffset(0x005A97E0);

__declspec(naked) void CDamageManager::SetEngineStatus(unsigned int)
{
	__asm jmp g_SetEngineStatus;
}

__declspec(naked) void CDamageManager::SetWheelStatus(int, unsigned int)
{
	__asm jmp g_SetWheelStatus;
}

__declspec(naked) unsigned int CDamageManager::GetEngineStatus()
{
	__asm jmp g_GetEngineStatus;
}
