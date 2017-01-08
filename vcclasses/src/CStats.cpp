#include "vcclasses.h"
#include "vcversion.h"

float &CStats::ShootingRangeRank = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974B08));
int &CStats::TotalNumberMissions = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974BF0));
float &CStats::GarbagePickups = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974C00));
float &CStats::LoanSharks = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00974C28));
int &CStats::IndustrialPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009751F4));
int &CStats::HighestLevelFireMission = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00975310));
int &CStats::SuburbanPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00978A0C));
float &CStats::StoresKnockedOff = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x0097F898));
int &CStats::CommercialPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x009B489C));
float &CStats::TopShootingRangeScore = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0D8A4));
float &CStats::MovieStunts = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A0FC8C));
int &CStats::MissionsGiven = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A1023C));
float &CStats::AutoPaintingBudget = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A10298));
float &CStats::Assassinations = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00A10918));

static unsigned long g_AnotherKillFrenzyPassed = vcversion::AdjustOffset(0x004CDBA7);

__declspec(naked) void CStats::AnotherKillFrenzyPassed(void)
{
	__asm jmp g_AnotherKillFrenzyPassed;
}
