#pragma once

#include "vcclasses.h"

class cAudioManagerHack : public cAudioManager
{
public:
	static bool initialise();

	bool ProcessFrontEndHack(unsigned char);
	static void ProcessFrontEndHackProxy();
	void ProcessLoopingScriptObjectHack(unsigned char);
	unsigned int GetPlayerTalkSfx(CPed *ped, unsigned short type);
	static void InitialiseAudioZoneArray();
	static void SetupSuspectLastSeenReportHackProxy();
	static int SetupSuspectLastSeenReportHack(int model);
};
