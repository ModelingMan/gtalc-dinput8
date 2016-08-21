#include "vcclasses.h"
#include "vcversion.h"

unsigned short& CTheScripts::CommandsExecuted = *reinterpret_cast<unsigned short *>(vcversion::AdjustOffset(0x00A10A66));
unsigned char *CTheScripts::ScriptSpace = reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00821280));

static unsigned long g_HighlightImportantArea = vcversion::AdjustOffset(0x0045F080);

__declspec(naked) void CTheScripts::HighlightImportantArea(unsigned int, float, float, float, float, float)
{
	__asm jmp g_HighlightImportantArea;
}
