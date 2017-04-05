#pragma once

#include "vcclasses.h"

class CBridgeHack
{
public:
	static CEntity *pWeight;                               // CBridge::pWeight
	static CEntity *pLiftRoad;                             // CBridge::pLiftRoad
	static CEntity *pLiftPart;                             // CBridge::pLiftPart
	static float DefaultZLiftWeight;                       // CBridge::DefaultZLiftWeight
	static float DefaultZLiftPart;                         // CBridge::DefaultZLiftPart
	static float DefaultZLiftRoad;                         // CBridge::DefaultZLiftRoad
	static int State;                                      // CBridge::State
	static int OldState;                                   // CBridge::OldState
	static float OldLift;                                  // CBridge::OldLift
	static unsigned int TimeOfBridgeBecomingOperational;   // CBridge::TimeOfBridgeBecomingOperational
	// additional objects
	static CEntity *pLodWeight;
	static CEntity *pLodLiftPart;

	static bool initialise();
	static void Init(void);                                // CBridge::Init
	static void Update(void);                              // CBridge::Update
	static bool ShouldLightsBeFlashing(void);              // CBridge::ShouldLightsBeFlashing
	static void FindBridgeEntities(void);                  // CBridge::FindBridgeEntities
	static bool ThisIsABridgeObjectMovingUp(unsigned int); // CBridge::ThisIsABridgeObjectMovingUp
};
