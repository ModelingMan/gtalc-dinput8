#include "vcclasses.h"
#include "vcversion.h"

unsigned int &CTimer::m_snTimeInMilliseconds = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00974B2C));
float &CTimer::ms_fTimeStepNonClipped = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x009753A8));
float &CTimer::ms_fTimeStep = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00975424));
float &CTimer::ms_fTimeScale = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0097F264));
unsigned int &CTimer::m_FrameCounter = *reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x00A0D898));

static unsigned long g_Stop = vcversion::AdjustOffset(0x004D0DB0);
static unsigned long g_Resume = vcversion::AdjustOffset(0x004D0E50);
static unsigned long g_Suspend = vcversion::AdjustOffset(0x004D0ED0);
static unsigned long g_Update = vcversion::AdjustOffset(0x004D0F30);

__declspec(naked) void CTimer::Stop(void)
{
	__asm jmp g_Stop;
}

__declspec(naked) void CTimer::Resume(void)
{
	__asm jmp g_Resume;
}

__declspec(naked) void CTimer::Suspend(void)
{
	__asm jmp g_Suspend;
}

__declspec(naked) void CTimer::Update(void)
{
	__asm jmp g_Update;
}
