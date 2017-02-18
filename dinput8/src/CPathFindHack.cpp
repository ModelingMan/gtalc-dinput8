#include "CPathFindHack.h"
#include "vcversion.h"
#include <algorithm>

bool CPathFindHack::initialise()
{
	return true;
}

// paths improvements from Silent
void CPathFindHack::StoreNodeInfoCar(short modelId, short nodeNum, char nodeType, char nextNode, short posX, short posY, short posZ, float median, char leftLanes, char rightLanes, bool ignoredByTraffic, bool restrictedNode, char speedLimit, bool isRoadblock, bool isBoatNode, unsigned char spawnRate)
{
	auto& currentNode = CPathFind::InfoForTileCars[modelId].m_node[nodeNum];

	currentNode.NodeType = nodeType;
	currentNode.NextNode = nextNode;
	currentNode.Pos.x = static_cast<float>(posX) / 16.0f;
	currentNode.Pos.y = static_cast<float>(posY) / 16.0f;
	currentNode.Pos.z = static_cast<float>(posZ) / 16.0f;
	currentNode.Median = static_cast<char>(8.0f * std::min(median, 15.0f));
	currentNode.LeftLanes = leftLanes;
	currentNode.RightLanes = rightLanes;

	// custom code begins here
	currentNode.SpeedLimit = speedLimit;
	currentNode.IsCrossroad = false;
	currentNode.Unknown2 = false;
	currentNode.IsRoadblock = isRoadblock;
	currentNode.IgnoredByTraffic = ignoredByTraffic;
	currentNode.BoatNode = isBoatNode;
	currentNode.RestrictedNode = restrictedNode;

	// custom code ends here
	currentNode.SpawnRate = std::min(spawnRate, (unsigned char)15);
	if (nodeNum == 11)
		CPathFind::InfoForTileCars[modelId].SwapConnectionsToBeRightWayRound();
}

void CPathFindHack::StoreNodeInfoPed(short modelId, short nodeNum, char nodeType, char nextNode, short posX, short posY, short posZ, float median, bool isCrossroad, bool ignoredByTraffic, bool restrictedNode, unsigned char spawnRate)
{
	auto& currentNode = CPathFind::InfoForTilePeds[modelId].m_node[nodeNum];

	currentNode.NodeType = nodeType;
	currentNode.NextNode = nextNode;
	currentNode.Pos.x = static_cast<float>(posX) / 16.0f;
	currentNode.Pos.y = static_cast<float>(posY) / 16.0f;
	currentNode.Pos.z = static_cast<float>(posZ) / 16.0f;
	currentNode.Median = static_cast<char>(8.0f * std::min(median, 31.0f));
	currentNode.LeftLanes = 0;
	currentNode.RightLanes = 0;

	// custom code begins here
	currentNode.SpeedLimit = 0;
	currentNode.IsCrossroad = isCrossroad;
	currentNode.Unknown2 = false;
	currentNode.IsRoadblock = false;
	currentNode.IgnoredByTraffic = ignoredByTraffic;
	currentNode.BoatNode = false;
	currentNode.RestrictedNode = restrictedNode;

	// custom code ends here
	currentNode.SpawnRate = std::min(spawnRate, (unsigned char)15);
	if (nodeNum == 11)
		CPathFind::InfoForTilePeds[modelId].SwapConnectionsToBeRightWayRound();
}
