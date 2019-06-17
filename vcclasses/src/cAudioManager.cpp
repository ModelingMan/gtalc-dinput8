#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_GetPhrase = vcversion::AdjustOffset(0x005DA690);
static unsigned long g_ProcessLoopingScriptObject = vcversion::AdjustOffset(0x005DC5A0);
static unsigned long g_GetPlayerTalkSfx = vcversion::AdjustOffset(0x005E9990);
static unsigned long g_SetupPedComments = vcversion::AdjustOffset(0x005EB2A0);
static unsigned long g_GetDistanceSquared = vcversion::AdjustOffset(0x005F5AA0);
static unsigned long g_AddSampleToRequestedQueue = vcversion::AdjustOffset(0x005F7560);
static unsigned long g_RandomDisplacement = vcversion::AdjustOffset(0x005F77E0);
static unsigned long g_ComputeVolume = vcversion::AdjustOffset(0x005F7A20);
static unsigned long g_PlayOneShot = vcversion::AdjustOffset(0x005F83B0);

__declspec(naked) unsigned int cAudioManager::GetPhrase(unsigned int &, unsigned int &, unsigned int, unsigned int)
{
	__asm jmp g_GetPhrase;
}

__declspec(naked) void cAudioManager::ProcessLoopingScriptObject(unsigned char)
{
	__asm jmp g_ProcessLoopingScriptObject;
}

__declspec(naked) unsigned int cAudioManager::GetPlayerTalkSfx(CPed *, unsigned short)
{
	__asm jmp g_GetPlayerTalkSfx;
}

__declspec(naked) void cAudioManager::SetupPedComments(cPedParams &, unsigned short)
{
	__asm jmp g_SetupPedComments;
}

__declspec(naked) float cAudioManager::GetDistanceSquared(CVector const &)
{
	__asm jmp g_GetDistanceSquared;
}

__declspec(naked) void cAudioManager::AddSampleToRequestedQueue()
{
	__asm jmp g_AddSampleToRequestedQueue;
}

__declspec(naked) unsigned int cAudioManager::RandomDisplacement(unsigned int)
{
	__asm jmp g_RandomDisplacement;
}

__declspec(naked) unsigned char cAudioManager::ComputeVolume(unsigned char, float, float)
{
	__asm jmp g_ComputeVolume;
}

__declspec(naked) void cAudioManager::PlayOneShot(int, unsigned short, float)
{
	__asm jmp g_PlayOneShot;
}
