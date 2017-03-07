#include "vcclasses.h"
#include "vcversion.h"

IntroTextLine *CTheScripts::IntroTextLines = reinterpret_cast<IntroTextLine *>(vcversion::AdjustOffset(0x007F0EA0));
unsigned char *CTheScripts::ScriptSpace = reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00821280));
CRunningScript **CTheScripts::pActiveScripts = reinterpret_cast<CRunningScript **>(vcversion::AdjustOffset(0x00975338));
CMissionCleanup &CTheScripts::MissionCleanUp = *reinterpret_cast<CMissionCleanup *>(vcversion::AdjustOffset(0x0097F060));
unsigned short &CTheScripts::NumberOfIntroTextLinesThisFrame = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x00A10A48));
unsigned short &CTheScripts::CommandsExecuted = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x00A10A66));

static unsigned long g_HighlightImportantArea = vcversion::AdjustOffset(0x0045F080);
static unsigned long g_ClearSpaceForMissionEntity = vcversion::AdjustOffset(0x0045F180);

__declspec(naked) void CTheScripts::HighlightImportantArea(unsigned int, float, float, float, float, float)
{
	__asm jmp g_HighlightImportantArea;
}

__declspec(naked) void CTheScripts::ClearSpaceForMissionEntity(CVector const &, CEntity *)
{
	__asm jmp g_ClearSpaceForMissionEntity;
}
