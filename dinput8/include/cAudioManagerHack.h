#pragma once

#include "vcclasses.h"

class cAudioManagerHack : public cAudioManager
{
public:
	static bool initialise();

	bool ProcessFrontEndHack(unsigned char);
	static void ProcessFrontEndHackProxy();
	void ProcessLoopingScriptObjectHack(unsigned char);
	static void InitialiseAudioZoneArrayHack(void);
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
	void ProcessPoliceCellBeatingScriptObject(unsigned int);
	static void DisplayRadioStationNameHack(float, float, wchar_t *);
	static void InitialiseHack(void);
	static void ProcessVehicleSirenOrAlarmHack(void);
	unsigned int GetPedCommentSfxHack(CPed *, unsigned short);
	unsigned int GetPlayerTalkSfx(CPed *, unsigned short);
	unsigned int GetMedicTalkSfx(CPed *, unsigned short);
	unsigned int GetFiremanTalkSfx(CPed *, unsigned short);
	unsigned int GetNormalMaleTalkSfx(CPed *, unsigned short);
	unsigned int GetAsianTaxiDriverTalkSfx(CPed *, unsigned short);
	unsigned int GetPimpTalkSfx(CPed *, unsigned short);
	unsigned int GetMafiaTalkSfx(CPed *, unsigned short);
	unsigned int GetTriadTalkSfx(CPed *, unsigned short);
	unsigned int GetDiabloTalkSfx(CPed *, unsigned short);
	unsigned int GetYakuzaTalkSfx(CPed *, unsigned short);
	unsigned int GetYardieTalkSfx(CPed *, unsigned short);
	unsigned int GetColombianTalkSfx(CPed *, unsigned short);
	unsigned int GetHoodTalkSfx(CPed *, unsigned short);
	unsigned int GetBlackCriminalTalkSfx(CPed *, unsigned short);
	unsigned int GetWhiteCriminalTalkSfx(CPed *, unsigned short);
	unsigned int GetSpecialCharacterTalkSfx(CPed *, unsigned short);
	unsigned int GetEightBallTalkSfx(CPed *, unsigned short);
	unsigned int GetSalvatoreTalkSfx(CPed *, unsigned short);
	unsigned int GetMistyTalkSfx(CPed *, unsigned short);
	unsigned int GetBomberTalkSfx(CPed *, unsigned short);
	unsigned int GetSecurityGuardTalkSfx(CPed *, unsigned short);
	unsigned int GetChunkyTalkSfx(CPed *, unsigned short);
	unsigned int GetViceWhiteTalkSfx(CPed *, unsigned short);
	unsigned int GetViceBlackTalkSfx(CPed *, unsigned short);
	unsigned int GetGenericMaleTalkSfx(CPed *, unsigned short);
	unsigned int GetGenericFemaleTalkSfx(CPed *, unsigned short);
};
