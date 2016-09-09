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
	void ProcessCrane(void);
	void ProcessCinemaScriptObject(unsigned int);
	void ProcessLaunderetteScriptObject(unsigned int);
	void ProcessSawMillScriptObject(unsigned int);
	void ProcessAirportScriptObject(unsigned int);
	void ProcessHomeScriptObject(unsigned int);
	static void DisplayRadioStationNameHack(float, float, wchar_t *);
};
