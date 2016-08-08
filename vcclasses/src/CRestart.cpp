#include "vcclasses.h"
#include "vcversion.h"

unsigned char &CRestart::OverrideHospitalLevel = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10AE6));
unsigned char &CRestart::OverridePoliceStationLevel = *reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x00A10AEA));

static unsigned long g_OverrideNextRestart = vcversion::AdjustOffset(0x004429E0);

__declspec(naked) void CRestart::OverrideNextRestart(CVector const &, float)
{
	__asm jmp g_OverrideNextRestart;
}
