#include "vcclasses.h"
#include "Globals.h"
#include "vcversion.h"

static unsigned long g_AddSampleToRequestedQueue = vcversion::AdjustOffset(0x005F7560);
static unsigned long g_ComputeVolume = vcversion::AdjustOffset(0x005F7A20);
static unsigned long g_ProcessLoopingScriptObject = vcversion::AdjustOffset(0x005DC5A0);

__declspec(naked) void cAudioManager::AddSampleToRequestedQueue()
{
	__asm jmp g_AddSampleToRequestedQueue;
}

__declspec(naked) unsigned char cAudioManager::ComputeVolume(unsigned char, float, float)
{
	__asm jmp g_ComputeVolume;
}

__declspec(naked) void cAudioManager::ProcessLoopingScriptObject(unsigned char)
{
	__asm jmp g_ProcessLoopingScriptObject;
}

float cAudioManager::GetDistanceSquared(const CVector& pos)
{
	float x = pos.x - VCGlobals::TheCamera.GetMatrix().pos.x;
	float y = pos.y - VCGlobals::TheCamera.GetMatrix().pos.y;
	float z = 0.2f * (pos.z - VCGlobals::TheCamera.GetMatrix().pos.z);
	return x * x + y * y + z * z;
}