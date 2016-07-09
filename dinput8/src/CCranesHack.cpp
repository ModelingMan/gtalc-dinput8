#include "CCranesHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"

#include <math.h>

// FindCarInSectorList
static void FindCarInSectorList();
unsigned long findCarProceedJump = vcversion::AdjustOffset(0x0005A81EC);
unsigned long findCarEndJump = vcversion::AdjustOffset(0x005A82F4);

bool CCranesHack::initialise()
{
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x005A8CBF)) = MILITARYCRANETOTAL;
	*reinterpret_cast<unsigned char *>(vcversion::AdjustOffset(0x005A8CCC)) = MILITARYCRANETOTAL;

	call(0x005A8CB9, &CCranesHack::RegisterCarForMilitaryCrane, PATCH_NOTHING);
	call(0x005A8232, &CCranesHack::DoesMilitaryCraneHaveThisOneAlready, PATCH_NOTHING);
	call(0x004A4EC4, &CCranesHack::InitCranes, PATCH_NOTHING);
	call(0x004A4993, &CCranesHack::InitCranes, PATCH_NOTHING);
	bool(__thiscall CCraneHack::* function)(unsigned int) = &CCraneHack::DoesCranePickUpThisCarType;
	call(0x005A821E, (unsigned long &)function, PATCH_NOTHING);
	call(0x005A8275, (unsigned long &)function, PATCH_NOTHING);
	call(0x005A81DF, &FindCarInSectorList, PATCH_JUMP);

	return true;
}

void CCranesHack::RegisterCarForMilitaryCrane(unsigned int model)
{
	switch (model) {
	case 137:
		carsCollectedMilitaryCrane |= 1;
		break;
	case 146:
		carsCollectedMilitaryCrane |= 2;
		break;
	case 156:
		carsCollectedMilitaryCrane |= 4;
		break;
	case 157:
		carsCollectedMilitaryCrane |= 8;
		break;
	case 162:
		carsCollectedMilitaryCrane |= 0x10;
		break;
	case 163:
		carsCollectedMilitaryCrane |= 0x20;
		break;
	case 220:
		carsCollectedMilitaryCrane |= 0x40;
		break;
	case 236:
		carsCollectedMilitaryCrane |= 0x80;
		break;
	}
}

bool CCranesHack::DoesMilitaryCraneHaveThisOneAlready(unsigned int model)
{
	switch (model) {
	case 137:
		return !!(carsCollectedMilitaryCrane & 1);
	case 146:
		return !!(carsCollectedMilitaryCrane & 2);
	case 156:
		return !!(carsCollectedMilitaryCrane & 4);
	case 157:
		return !!(carsCollectedMilitaryCrane & 8);
	case 162:
		return !!(carsCollectedMilitaryCrane & 0x10);
	case 163:
		return !!(carsCollectedMilitaryCrane & 0x20);
	case 220:
		return !!(carsCollectedMilitaryCrane & 0x40);
	case 236:
		return !!(carsCollectedMilitaryCrane & 0x80);
	}
	return false;
}

bool CCranesHack::IsThisCarPickedUp(float positionX, float positionY, unsigned int vehicle)
{
	float craneObjectX, craneObjectY, distance;
	if (numCranes > 0) {
		for (int i = 0; i < numCranes; i++) {
			craneObjectX = *(float *)(cranes[i].object + 0x34);
			craneObjectY = *(float *)(cranes[i].object + 0x38);
			distance = sqrt(pow(positionX - craneObjectX, 2) + pow(positionY - craneObjectY, 2));
			if (distance < 100.0 && cranes[i].vehicle == vehicle && (cranes[i].status == 2 || cranes[i].status == 4)) {
				return true;
			}
		}
	}
	return false;
}

void CCranesHack::DeActivateCrane(float positionX, float positionY)
{
	int index = -1;
	float craneObjectX, craneObjectY, minDistance, distance;
	minDistance = 100.0;
	if (numCranes > 0) {
		for (int i = 0; i < numCranes; i++) {
			craneObjectX = *(float *)(cranes[i].object + 0x34);
			craneObjectY = *(float *)(cranes[i].object + 0x38);
			distance = sqrt(pow(positionX - craneObjectX, 2) + pow(positionY - craneObjectY, 2));
			if (distance < minDistance) {
				index = i;
				minDistance = distance;
			}
		}
	}
	if (index == -1) return;
	cranes[index].activity = 2;
	cranes[index].status = 0;
}

void CCranesHack::ActivateCrane(float pickupX1, float pickupX2, float pickupY1, float pickupY2, float dropoffX, float dropoffY, float dropoffZ, float dropoffHeading, bool isCrusher, bool isMilitary, float positionX, float positionY)
{
	int index = -1;
	float craneObjectX, craneObjectY, minDistance, distance, pickupCenterX, pickupCenterY;
	minDistance = 100.0;
	if (numCranes > 0) {
		for (int i = 0; i < numCranes; i++) {
			craneObjectX = *(float *)(cranes[i].object + 0x34);
			craneObjectY = *(float *)(cranes[i].object + 0x38);
			distance = sqrt(pow(positionX - craneObjectX, 2) + pow(positionY - craneObjectY, 2));
			if (distance < minDistance) {
				index = i;
				minDistance = distance;
			}
		}
	}
	if (index == -1) return;
	cranes[index].pickupX1 = pickupX1;
	cranes[index].pickupX2 = pickupX2;
	cranes[index].pickupY1 = pickupY1;
	cranes[index].pickupY2 = pickupY2;
	cranes[index].dropoffX = dropoffX;
	cranes[index].dropoffY = dropoffY;
	cranes[index].dropoffZ = dropoffZ;
	cranes[index].activity = 1;
	cranes[index].vehicle = 0;
	cranes[index].countCollected = 0;
	cranes[index].dropoffHeading = dropoffHeading;
	cranes[index].isCrusher = isCrusher;
	cranes[index].isMilitary = isMilitary;
	cranes[index].timer = 0;
	cranes[index].status = 0;
	pickupCenterX = (pickupX1 + pickupX2) / 2;
	pickupCenterY = (pickupY1 + pickupY2) / 2;
	craneObjectX = *(float *)(cranes[index].object + 0x34);
	craneObjectY = *(float *)(cranes[index].object + 0x38);
	if (isCrusher) {
		cranes[index].armPickupHeight = -0.95099998f + OFFSETHEIGHT;
	} else if (isMilitary) {
		cranes[index].armPickupHeight = 10.7862f + OFFSETHEIGHT;
	} else {
		cranes[index].armPickupHeight = CWorld::FindGroundZForCoord(pickupCenterX, pickupCenterY);
	}
	cranes[index].armPickupRotation = CGeneral::GetATanOfXY(pickupCenterX - craneObjectX, pickupCenterY - craneObjectY);
	cranes[index].armPickupDistance = sqrt(pow(pickupCenterX - craneObjectX, 2) + pow(pickupCenterY - craneObjectY, 2));
	cranes[index].armDropoffRotation = CGeneral::GetATanOfXY(dropoffX - craneObjectX, dropoffY - craneObjectY);
	cranes[index].armDropoffDistance = sqrt(pow(dropoffX - craneObjectX, 2) + pow(dropoffY - craneObjectY, 2));
	cranes[index].armDropoffHeight = dropoffZ;
}

void CCranesHack::AddThisOneCrane(unsigned int entity)
{
	// reset orientation
	*(float *)(entity + 4) = 1.0;
	*(float *)(entity + 8) = 0.0;
	*(float *)(entity + 0xC) = 0.0;
	*(float *)(entity + 0x14) = 0.0;
	*(float *)(entity + 0x18) = 1.0;
	*(float *)(entity + 0x1C) = 0.0;
	*(float *)(entity + 0x24) = 0.0;
	*(float *)(entity + 0x28) = 0.0;
	*(float *)(entity + 0x2C) = 1.0;
	// add crane to array
	if (numCranes < 8) {
		int index = numCranes;
		cranes[index].object = entity;
		cranes[index].activity = 0;
		// initialise rotation
		cranes[index].armCurrentRotation = (float)(numCranes);
		while (cranes[index].armCurrentRotation > 6.283) {
			cranes[index].armCurrentRotation -= 6.283;
		}
		cranes[index].armCurrentDistance = 20.0f;
		cranes[index].armCurrentHeight = 20.0f + OFFSETHEIGHT;
		cranes[index].timer = 0;
		cranes[index].status = 0;
		cranes[index].unk3 = 0;
		cranes[index].isNotCab = *(unsigned short *)(entity + 0x5C) == 893 ? 0 : 1;
		cranes[index].hook = 0;
		// new! magnet for cranes!
		if (cranes[index].isNotCab || *(float *)(entity + 0x38) > 0.0) {
			auto allocateObject = (unsigned int(__cdecl *)(unsigned int))vcversion::AdjustOffset(0x004E4070);
			unsigned int object = allocateObject(0x194);
			if (object) {
				auto createObject = (unsigned int(__thiscall *)(int, int, bool))vcversion::AdjustOffset(0x004E41B0);
				object = createObject(object, 1365, false);
			}
			*(unsigned char *)(object + 0x16C) = 2;
			*(unsigned char *)(object + 0x51) = *(unsigned char *)(object + 0x51) & 0xFE;
			*(unsigned char *)(object + 0x52) = (*(unsigned char *)(object + 0x52) & 0xFD) | 2;
			*(unsigned char *)(object + 0x11A) = *(unsigned char *)(object + 0x11A) & 0xFD;
			cranes[index].hook = object;
		}
		numCranes++;
	}
}

void CCranesHack::InitCranes()
{
	carsCollectedMilitaryCrane = 0;
	numCranes = 0;
	unsigned int buildings = *(unsigned int *)vcversion::AdjustOffset(0x0097F240);
	unsigned int buildingObjects = *(unsigned int *)buildings; // pointer to entity array of buildings
	unsigned int buildingValidities = *(unsigned int *)(buildings + 4); // pointer to char array of valid and invalid buildings
	int numberOfBuildings = *(int *)(buildings + 8); // number of buildings
	for (int i = 0; i < numberOfBuildings; i++) {
		if (((*(char *)(buildingValidities + i)) & 0x80) != 0x80) { // is building in array valid
			unsigned short buildingModel = *(unsigned short *)(buildingObjects + i * 0x64 + 0x5C); // pointer to building model
			if (buildingModel == 882 || buildingModel == 883 || buildingModel == 893) {
				AddThisOneCrane(buildingObjects + i * 0x64);
			}
		}
	}
}

bool CCraneHack::DoesCranePickUpThisCarType(unsigned int model)
{
	if (isCrusher) {
		if (model == 137 || // Firetruck
			model == 138 || // Trashmaster
			model == 155 || // Hunter
			model == 158 || // Securicar
			model == 161 || // Bus
			model == 162 || // Rhino
			model == 167 || // Coach
			model == 177 || // Sea Sparrow
			model == 190 || // Skimmer
			model == 194 || // Dodo
			model == 199 || // Sparrow
			model == 217 || // Maverick
			model == 218 || // VCN Maverick
			model == 227) { // Police Maverick
			return false;
		}
		return true;
	} else if (isMilitary) {
		if (model == 137 || // Firetruck
			model == 146 || // Ambulance
			model == 156 || // Police
			model == 157 || // Enforcer
			model == 162 || // Rhino
			model == 163 || // Barracks OL
			model == 220 || // Fbi Car
			model == 236) { // Vice Cheetah
			return true;
		}
		return false;
	}
	return true;
}

void __declspec(naked) FindCarInSectorList()
{
	__asm
	{
		cmp dword ptr [ebp+29Ch], 0 // is vehicle type car
		jz proceed
		cmp dword ptr [ebp+29Ch], 5 // is vehicle type bike
		jz proceed
		jmp findCarEndJump
	proceed:
		jmp findCarProceedJump
	}
}
