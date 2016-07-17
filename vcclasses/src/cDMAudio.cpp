#include "vcclasses.h"
#include "vcversion.h"

int &cDMAudio::garageEntity = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0068767C));

static unsigned long g_PlayFrontEndSound = vcversion::AdjustOffset(0x005F9960);
static unsigned long g_PlayOneShot = vcversion::AdjustOffset(0x005F9DA0);

__declspec(naked) void cDMAudio::PlayFrontEndSound(int id, int unk)
{
	__asm jmp g_PlayFrontEndSound;
}

__declspec(naked) void cDMAudio::PlayOneShot(int, unsigned short, float)
{
	__asm jmp g_PlayOneShot;
}
