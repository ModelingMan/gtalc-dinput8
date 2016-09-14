#pragma once

#include "vcclasses.h"

class CBridgeHack
{
public:
	static CEntity *pWeight;
	static CEntity *pLiftRoad;
	static CEntity *pLiftPart;
	static float DefaultZLiftWeight;
	static float DefaultZLiftPart;
	static float DefaultZLiftRoad;
	static int State;
	static int OldState;
	static float OldLift;
	static unsigned int TimeOfBridgeBecomingOperational;
	// additional objects
	static CEntity *pLodWeight;
	static CEntity *pLodLiftPart;

	static bool initialise();

	static void Init(void);
	static void Update(void);
	static void FindBridgeEntities(void);
};
