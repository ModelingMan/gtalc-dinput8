#pragma once

#include "vcclasses.h"

class CStatsHack : public CStats
{
public:
	static int &LongestFlightInDodo; // uses CStats::GarbagePickups
	static int &MissionsPassed; // uses CStats::MovieStunts

	static bool initialise();
	static void RegisterLongestFlightInDodo(int);
	static void AddTextLine(const char *);
	static int ConstructStatLine(int);
};
