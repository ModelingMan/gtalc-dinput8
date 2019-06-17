#include "CFileLoaderHack.h"
#include "vcversion.h"
#include "Globals.h"
#include "SilentCall.h"
#include "CPathFindHack.h"

// LoadObjectTypesHack
static unsigned long loadObjectTypesEndJump = vcversion::AdjustOffset(0x0048D47E);

// paths improvements from Silent
bool CFileLoaderHack::initialise()
{
	InjectHook(0x0048CB4C, &CFileLoaderHack::LoadObjectTypesHack, PATCH_JUMP);

	auto function = &CPathFindHack::StoreNodeInfoCar;
	InjectHook(0x0048D479, (unsigned long &)function);

	return true;
}

void CFileLoaderHack::LoadPedPathNode(const char *line, int modelId, int nodeNum)
{
	int NodeType, NextNode, IsCrossroad;
	float posX, posY, posZ, Median;
	int LeftLanes, RightLanes, SpeedLimit, Flags;
	float SpawnRate = 1.0f;
	VCGlobals::sscanf(line, "%d %d %d %f %f %f %f %d %d %d %d %f",
		&NodeType, &NextNode, &IsCrossroad, &posX, &posY, &posZ, &Median, &LeftLanes, &RightLanes,
		&SpeedLimit, &Flags, &SpawnRate);

	if (modelId == -1)
		VCGlobals::ThePaths.StoreDetachedNodeInfoPed(nodeNum, static_cast<char>(NodeType), NextNode, posX, posY, posZ, Median, IsCrossroad != 0, (Flags & 1) != 0, (Flags & 4) != 0, static_cast<unsigned char>(15.0f * SpawnRate));
	else
		static_cast<CPathFindHack *>(&VCGlobals::ThePaths)->StoreNodeInfoPed(static_cast<short>(modelId), static_cast<short>(nodeNum), static_cast<char>(NodeType), static_cast<char>(NextNode), static_cast<short>(posX), static_cast<short>(posY), static_cast<short>(posZ), Median, IsCrossroad != 0, (Flags & 1) != 0, (Flags & 4) != 0, static_cast<unsigned char>(15.0f * SpawnRate));
}

void __declspec(naked) CFileLoaderHack::LoadObjectTypesHack()
{
	__asm
	{
		push edi
		push [esp+0Ch]
		push esi
		call CFileLoaderHack::LoadPedPathNode
		add esp, 0Ch
		jmp loadObjectTypesEndJump
	}
}
