#include "vcclasses.h"
#include "vcversion.h"

float &CStats::ShootingRangeRank = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974B08));
float &CStats::GarbagePickups = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974C00));
float &CStats::LoanSharkVisits = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974C28));
float &CStats::TopShootingRangeScore = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0D8A4));
float &CStats::MovieStunts = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0FC8C));

static unsigned long g_AnotherKillFrenzyPassed = vcversion::AdjustOffset(0x004CDBA7);

__declspec(naked) void CStats::AnotherKillFrenzyPassed(void)
{
	__asm jmp g_AnotherKillFrenzyPassed;
}
