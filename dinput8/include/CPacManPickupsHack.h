#pragma once

#include "vcclasses.h"

#define MAX_PACMAN_PICKUP 256

class CPacManPickupHack
{
public:
	CVector position;
	CObject *object;
	unsigned char state;
	unsigned char padding[3];

	void Update(void);                                      // CPacManPickup::Update
};

class CPacManPickupsHack
{
public:
	static int PillsEatenInRace;                            // CPacManPickups::PillsEatenInRace
	static CPacManPickupHack aPMPickups[MAX_PACMAN_PICKUP]; // CPacManPickups::aPMPickUps
	static bool bPMActive;                                  // CPacManPickups::bPMActive

	static bool initialise();
	static void ResetPowerPillsCarriedByPlayer(void);       // CPacManPickups::ResetPowerPillsCarriedByPlayer
	static int QueryPowerPillsCarriedByPlayer(void);        // CPacManPickups::QueryPowerPillsCarriedByPlayer
	static void StartPacManScramble(CVector, float, short); // CPacManPickups::StartPacManScramble
	static void CleanUpPacManStuff(void);                   // CPacManPickups::CleanUpPacManStuff
	static void ResetPowerPillsEatenInRace(void);           // CPacManPickups::ResetPowerPillsEatenInRace
	static int QueryPowerPillsEatenInRace(void);            // CPacManPickups::QueryPowerPillsEatenInRace
	static void StartPacManRace(int raceType = 0);          // CPacManPickups::StartPacManRace
	static void Render(void);                               // CPacManPickups::Render
	static void GenerateOnePMPickUp(CVector pos);           // CPacManPickups::GenerateOnePMPickUp
	static void GeneratePMPickUpsForRace(void);             // CPacManPickups::GeneratePMPickUpsForRace
	static void GeneratePMPickUps(CVector, float, short);   // CPacManPickups::GeneratePMPickUps
	static void Update(void);                               // CPacManPickups::Update
	static void Init(void);                                 // CPacManPickups::Init
};
