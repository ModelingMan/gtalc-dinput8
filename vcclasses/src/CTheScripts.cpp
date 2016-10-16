#include "vcclasses.h"
#include "vcversion.h"

unsigned char *CTheScripts::ScriptSpace = reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00821280));
CMissionCleanup &CTheScripts::MissionCleanUp = *reinterpret_cast<CMissionCleanup *>(vcversion::AdjustOffset(0x0097F060));
unsigned short &CTheScripts::CommandsExecuted = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x00A10A66));

static unsigned long g_HighlightImportantArea = vcversion::AdjustOffset(0x0045F080);

__declspec(naked) void CTheScripts::HighlightImportantArea(unsigned int, float, float, float, float, float)
{
	__asm jmp g_HighlightImportantArea;
}
