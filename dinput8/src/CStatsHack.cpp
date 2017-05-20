#include "CStatsHack.h"
#include <Windows.h>
#include "vcversion.h"
#include "Globals.h"
#include "SilentCall.h"

#define METRES_TO_MILES 0.0006213712f // originally 0.0005988024
#define METRES_TO_FEET 3.28084f // originally 3.3333333

static bool additionalStats;
int &CStatsHack::LongestFlightInDodo = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00974C00)); // uses CStats::GarbagePickups
int &CStatsHack::MissionsPassed = *reinterpret_cast<int *>(vcversion::AdjustOffset(0x00A0FC8C)); // uses CStats::MovieStunts

enum eStatType
{
	STAT_TYPE_INT,
	STAT_TYPE_FLOAT,
	STAT_TYPE_PERCENT,
	STAT_TYPE_CASH,
	STAT_TYPE_DEGREE
};

bool CStatsHack::initialise()
{
	additionalStats = !!GetPrivateProfileInt("Misc", "AdditionalStats", 0, "./gta-lc.ini");
	InjectHook(0x0048FA1C, &CStatsHack::ConstructStatLine);
	InjectHook(0x0048FB34, &CStatsHack::ConstructStatLine);
	InjectHook(0x0048FBC5, &CStatsHack::ConstructStatLine);
	InjectHook(0x0048FD61, &CStatsHack::ConstructStatLine);
	InjectHook(0x0049B9B2, &CStatsHack::ConstructStatLine);
	InjectHook(0x0049BEB6, &CStatsHack::ConstructStatLine);

	// replace missions passed stat
	Patch<void *>(0x00456C0F, &CStatsHack::MissionsPassed);
	Patch<void *>(0x004CE592, &CStatsHack::MissionsPassed);
	Patch<void *>(0x006382FE, &CStatsHack::MissionsPassed);
	return true;
}

void CStatsHack::RegisterLongestFlightInDodo(int value)
{
	if (value > LongestFlightInDodo)
		LongestFlightInDodo = value;
}

void CStatsHack::AddTextLine(const char *string)
{
	VCGlobals::gUString[0] = 0;
	VCGlobals::UnicodeStrCpy(VCGlobals::gUString2, VCGlobals::TheText.Get(string));
}

int CStatsHack::ConstructStatLine(int line)
{
	int offset = 0;
	if (line == offset++) {
		BuildStatLine("PL_STAT", 0, 0, 0, 0); // Player stats
		return 0;
	}
	return offset;
}
