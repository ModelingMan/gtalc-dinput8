#include "CCranesHack.h"
#include "Globals.h"

#include <math.h>

bool CCranesHack::IsThisCarPickedUp(float positionX, float positionY, unsigned int vehicle)
{
	float craneObjectX, craneObjectY, distance;
	if (*numCranes > 0) {
		for (int i = 0; i < *numCranes; i++) {
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
	if (*numCranes > 0) {
		for (int i = 0; i < *numCranes; i++) {
			craneObjectX = *(float *)(cranes[i].object + 0x34);
			craneObjectY = *(float *)(cranes[i].object + 0x38);
			distance = sqrt(pow(positionX - craneObjectX, 2) + pow(positionY - craneObjectY, 2));
			if (distance < minDistance) {
				index = i;
				minDistance = distance;
			}
		}
	}
	cranes[index].activity = 2;
	cranes[index].status = 0;
}

void CCranesHack::ActivateCrane(float pickupX1, float pickupX2, float pickupY1, float pickupY2, float dropoffX, float dropoffY, float dropoffZ, float dropoffHeading, bool isCrusher, bool isMilitary, float positionX, float positionY)
{
	int index = -1;
	float craneObjectX, craneObjectY, minDistance, distance, pickupCenterX, pickupCenterY;
	minDistance = 100.0;
	if (*numCranes > 0) {
		for (int i = 0; i < *numCranes; i++) {
			craneObjectX = *(float *)(cranes[i].object + 0x34);
			craneObjectY = *(float *)(cranes[i].object + 0x38);
			distance = sqrt(pow(positionX - craneObjectX, 2) + pow(positionY - craneObjectY, 2));
			if (distance < minDistance) {
				index = i;
				minDistance = distance;
			}
		}
	}
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
		cranes[index].armPickupHeight = -0.95099998f;
	} else if (isMilitary) {
		cranes[index].armPickupHeight = 10.7862f;
	} else {
		cranes[index].armPickupHeight = CWorld::FindGroundZForCoord(pickupCenterX, pickupCenterY);
	}
	cranes[index].armPickupRotation = CGeneral::GetATanOfXY(pickupCenterX - craneObjectX, pickupCenterY - craneObjectY);
	cranes[index].armPickupDistance = sqrt(pow(pickupCenterX - craneObjectX, 2) + pow(pickupCenterY - craneObjectY, 2));
	cranes[index].armDropoffRotation = CGeneral::GetATanOfXY(dropoffX - craneObjectX, dropoffY - craneObjectY);
	cranes[index].armDropoffDistance = sqrt(pow(dropoffX - craneObjectX, 2) + pow(dropoffY - craneObjectY, 2));
	cranes[index].armDropoffHeight = dropoffZ;
}
