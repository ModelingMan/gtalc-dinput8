#include "vcclasses.h"
#include "vcversion.h"

static unsigned long g_StartFrenzy = vcversion::AdjustOffset(0x00429B60);
static unsigned long g_ResetOnPlayerDeath = vcversion::AdjustOffset(0x00429F90);

__declspec(naked) void CDarkel::StartFrenzy(int, int, unsigned short, int, wchar_t *, int, int, int, bool, bool)
{
	__asm jmp g_StartFrenzy;
}

__declspec(naked) void CDarkel::ResetOnPlayerDeath(void)
{
	__asm jmp g_ResetOnPlayerDeath;
}
