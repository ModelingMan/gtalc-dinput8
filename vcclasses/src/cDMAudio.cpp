#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_PlayFrontEndSound = vcversion::AdjustOffset(0x005F9960);

__declspec(naked) void cDMAudio::PlayFrontEndSound(int id, int unk)
{
	__asm jmp g_PlayFrontEndSound;
}