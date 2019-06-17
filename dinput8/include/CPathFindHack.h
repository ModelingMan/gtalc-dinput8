#pragma once

#include "vcclasses.h"

class CPathFindHack : public CPathFind
{
public:
	static bool initialise();

	void StoreNodeInfoCar(short modelId, short nodeNum, char nodeType, char nextNode, short posX, short posY, short posZ, float median, char leftLanes, char rightLanes, bool ignoredByTraffic, bool restrictedNode, char speedLimit, bool isRoadblock, bool isBoatNode, unsigned char spawnRate);
	void StoreNodeInfoPed(short modelId, short nodeNum, char nodeType, char nextNode, short posX, short posY, short posZ, float median, bool isCrossroad, bool ignoredByTraffic, bool restrictedNode, unsigned char spawnRate);
};
