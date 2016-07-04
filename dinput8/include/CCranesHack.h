#pragma once

#include "vcclasses.h"

#define OFFSETHEIGHT 6.0f
#define MILITARYCRANETOTAL 0xFF

class CCranesHack : public CCranes
{
public:
	static bool initialise();

	static void RegisterCarForMilitaryCrane(unsigned int model);
	static bool DoesMilitaryCraneHaveThisOneAlready(unsigned int model);
	static bool IsThisCarPickedUp(float positionX, float positionY, unsigned int vehicle);
	static void DeActivateCrane(float positionX, float positionY);
	static void ActivateCrane(float pickupX1, float pickupX2, float pickupY1, float pickupY2, float dropoffX, float dropoffY, float dropoffZ, float dropoffHeading, bool isCrusher, bool isMilitary, float positionX, float positionY);
	static void AddThisOneCrane(unsigned int entity);
	static void InitCranes(void);
};

class CCraneHack : public CCrane
{
public:
	bool DoesCranePickUpThisCarType(unsigned int model);
};
