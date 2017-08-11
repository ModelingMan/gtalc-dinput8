#include "vcclasses.h"
#include "vcversion.h"

CZoneInfo *CTheZones::ZoneInfoArray = reinterpret_cast<CZoneInfo *>(vcversion::AdjustOffset(0x007FA370));
CZone *CTheZones::InfoZoneArray = reinterpret_cast<CZone *>(vcversion::AdjustOffset(0x00862508));
CZone *CTheZones::NavigationZoneArray = reinterpret_cast<CZone *>(vcversion::AdjustOffset(0x0094B990));
unsigned short &CTheZones::TotalNumberOfInfoZones = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x00A1096A));
unsigned short &CTheZones::TotalNumberOfNavigationZones = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x00A10A58));

static unsigned long g_InitialiseAudioZoneArray = vcversion::AdjustOffset(0x004DC430);
static unsigned long g_GetLevelFromPosition = vcversion::AdjustOffset(0x004DD300);
static unsigned long g_Init = vcversion::AdjustOffset(0x004DDFA0);

__declspec(naked) void CTheZones::InitialiseAudioZoneArray(void)
{
	__asm jmp g_InitialiseAudioZoneArray;
}

__declspec(naked) int CTheZones::GetLevelFromPosition(CVector const *)
{
	__asm jmp g_GetLevelFromPosition;
}

__declspec(naked) void CTheZones::Init(void)
{
	__asm jmp g_Init;
}
