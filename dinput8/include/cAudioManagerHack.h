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
	static void InitialiseAudioZoneArray(void);
	static void SetupSuspectLastSeenReportHackProxy(void);
	static int SetupSuspectLastSeenReportHack(int model);
	void ProcessCraneAndBridge(void);
	void ProcessBridgeMotor(void);
	void ProcessBridgeWarning(void);
	void ProcessBridgeOneShots(void);
	void ProcessCinemaScriptObject(unsigned int);
	void ProcessLaunderetteScriptObject(unsigned int);
	void ProcessSawMillScriptObject(unsigned int);
	void ProcessAirportScriptObject(unsigned int);
	void ProcessHomeScriptObject(unsigned int);
	static void DisplayRadioStationNameHack(float, float, wchar_t *);
	static void InitialiseHack(void);
};
