#include "vcclasses.h"
#include "vcversion.h"

int &cDMAudio::garageEntity = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x0068767C));

static unsigned long g_GetListenTimeArray = vcversion::AdjustOffset(0x005F96C0);
static unsigned long g_PlayRadioAnnouncement = vcversion::AdjustOffset(0x005F9940);
static unsigned long g_PlayFrontEndSound = vcversion::AdjustOffset(0x005F9960);
static unsigned long g_IsMP3RadioChannelAvailable = vcversion::AdjustOffset(0x005F9BB0);
static unsigned long g_PlayOneShot = vcversion::AdjustOffset(0x005F9DA0);
static unsigned long g_SetEntityStatus = vcversion::AdjustOffset(0x005F9DD0);
static unsigned long g_DestroyEntity = vcversion::AdjustOffset(0x005F9E00);
static unsigned long g_CreateEntity = vcversion::AdjustOffset(0x005F9E20);

__declspec(naked) float *cDMAudio::GetListenTimeArray(void)
{
	__asm jmp g_GetListenTimeArray;
}

__declspec(naked) void cDMAudio::PlayRadioAnnouncement(unsigned char)
{
	__asm jmp g_PlayRadioAnnouncement;
}

__declspec(naked) void cDMAudio::PlayFrontEndSound(int, int)
{
	__asm jmp g_PlayFrontEndSound;
}

__declspec(naked) bool cDMAudio::IsMP3RadioChannelAvailable(void)
{
	__asm jmp g_IsMP3RadioChannelAvailable;
}

__declspec(naked) void cDMAudio::PlayOneShot(int, unsigned short, float)
{
	__asm jmp g_PlayOneShot;
}

__declspec(naked) void cDMAudio::SetEntityStatus(int, unsigned char)
{
	__asm jmp g_SetEntityStatus;
}

__declspec(naked) void cDMAudio::DestroyEntity(int)
{
	__asm jmp g_DestroyEntity;
}

__declspec(naked) int cDMAudio::CreateEntity(int, void *)
{
	__asm jmp g_CreateEntity;
}
