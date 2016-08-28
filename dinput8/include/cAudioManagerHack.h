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
	unsigned int CinemaRandomness();
	void ProcessLaunderetteScriptObject(unsigned int);
	void ProcessSawMillScriptObject(unsigned int);
	unsigned int SawmillRandomness();
	void ProcessAirportScriptObject(unsigned int);
	unsigned int AirportRandomness();
	void ProcessHomeScriptObject(unsigned int);
	unsigned int Home1Randomness();
	unsigned int Home2Randomness();
	unsigned int Home3Randomness();
};
