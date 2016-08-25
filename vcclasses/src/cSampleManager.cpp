#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetSampleBaseFrequency = vcversion::AdjustOffset(0x005D6EE0);
static unsigned long g_GetSampleLoopEndOffset = vcversion::AdjustOffset(0x005D6EA0);
static unsigned long g_GetSampleLoopStartOffset = vcversion::AdjustOffset(0x005D6EC0);

__declspec(naked) unsigned int cSampleManager::GetSampleBaseFrequency(unsigned int)
{
	__asm jmp g_GetSampleBaseFrequency;
}

__declspec(naked) unsigned int cSampleManager::GetSampleLoopEndOffset(unsigned int)
{
	__asm jmp g_GetSampleLoopEndOffset;
}

__declspec(naked) unsigned int cSampleManager::GetSampleLoopStartOffset(unsigned int)
{
	__asm jmp g_GetSampleLoopStartOffset;
}
