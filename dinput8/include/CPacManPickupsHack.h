#pragma once

#include "vcclasses.h"
#include "Globals.h"

#define MAX_PACMAN_PICKUP 256

class CPacManPickupHack
{
public:
	CVector position;
	CObject *object;
	unsigned char state;
	unsigned char padding[3];

	void Update(void);
};

class CPacManPickupsHack
{
public:
	static int PillsEatenInRace;
	static CPacManPickupHack aPMPickups[MAX_PACMAN_PICKUP];
	static bool bPMActive;

	static bool initialise();
	static void ResetPowerPillsCarriedByPlayer(void);
	static int QueryPowerPillsCarriedByPlayer(void);
	static void StartPacManScramble(CVector, float, short);
	static void CleanUpPacManStuff(void);
	static void ResetPowerPillsEatenInRace(void);
	static int QueryPowerPillsEatenInRace(void);
	static void StartPacManRace(int raceType = 0);
	static void Render(void);
	static void GenerateOnePMPickUp(CVector pos);
	static void GeneratePMPickUpsForRace(void);
	static void GeneratePMPickUps(CVector, float, short);
	static void Update(void);
	static void Init(void);
};
