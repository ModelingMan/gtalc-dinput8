#include "CBridgeHack.h"
#include "vcversion.h"
#include "SilentCall.h"

#define MI_BRIDGEWEIGHT 1130
#define MI_BRIDGELIFT 1131
#define MI_BRIDGEROADSEGMENT 1138
#define MI_LODDGEWEIGHT 1180
#define MI_LODDGELIFT 1178

CEntity *CBridgeHack::pWeight;
CEntity *CBridgeHack::pLiftPart;
CEntity *CBridgeHack::pLiftRoad;
CEntity *CBridgeHack::pLodWeight;
CEntity *CBridgeHack::pLodLiftPart;
float CBridgeHack::DefaultZLiftWeight;
float CBridgeHack::DefaultZLiftPart;
float CBridgeHack::DefaultZLiftRoad;
int CBridgeHack::State;
int CBridgeHack::OldState;
float CBridgeHack::OldLift;
unsigned int CBridgeHack::TimeOfBridgeBecomingOperational;

bool ShouldCarStopForBridge(CVehicle *);

bool CBridgeHack::initialise()
{
	InjectHook(0x004A4EF6, &CBridgeHack::Init);
	InjectHook(0x004A4620, &CBridgeHack::Update);

	// workaround for vehicles to stop at lift bridge
	InjectHook(0x00463F80, &ShouldCarStopForBridge, PATCH_JUMP);

	return true;
}

void CBridgeHack::Init()
{
	FindBridgeEntities();
	OldLift = -1.0;
	if (pWeight) DefaultZLiftWeight = pWeight->GetZ();
	if (pLiftPart) DefaultZLiftPart = pLiftPart->GetZ();
	if (pLiftRoad) DefaultZLiftRoad = pLiftRoad->GetZ();
}

void CBridgeHack::Update()
{
	if (pLiftPart && pWeight) {
		int timeDifference;
		float lift;
		OldState = State;
		if (!CStats::CommercialPassed) {
			TimeOfBridgeBecomingOperational = 0;
			State = 0; // inactive
			lift = 25.0;
		} else {
			if (!TimeOfBridgeBecomingOperational) {
				TimeOfBridgeBecomingOperational = CTimer::m_snTimeInMilliseconds;
			}
			timeDifference = (CTimer::m_snTimeInMilliseconds - TimeOfBridgeBecomingOperational) & 0xFFFF;
			if (timeDifference < 10000) {
				State = 2; // moving down
				lift = 25.0f - static_cast<float>(timeDifference)* 25.0f * 0.0001f;
			} else if (timeDifference < 40000) {
				State = 3; // fully closed
				lift = 0.0;
			} else if (timeDifference < 50000) {
				State = 4; // ready to move up
				lift = 0.0;
			} else if (timeDifference < 60000) {
				State = 5; // moving up
				lift = static_cast<float>(timeDifference - 50000) * 25.0f * 0.0001f;
			} else {
				State = 1; // fully opened
				lift = 25.0;
			}
		}
		if (lift != OldLift) {
			pWeight->GetZ() = DefaultZLiftWeight - lift;
			pWeight->GetMatrix().UpdateRW();
			pWeight->UpdateRwFrame();
			if (pLiftRoad) {
				pLiftRoad->GetZ() = DefaultZLiftRoad + lift;
				pLiftRoad->GetMatrix().UpdateRW();
				pLiftRoad->UpdateRwFrame();
			}
			pLiftPart->GetZ() = DefaultZLiftPart + lift;
			pLiftPart->GetMatrix().UpdateRW();
			pLiftPart->UpdateRwFrame();

			// additional objects
			if (pLodWeight) {
				pLodWeight->GetZ() = DefaultZLiftWeight - lift;
				pLodWeight->GetMatrix().UpdateRW();
				pLodWeight->UpdateRwFrame();
			}
			if (pLodLiftPart) {
				pLodLiftPart->GetZ() = DefaultZLiftPart + lift;
				pLodLiftPart->GetMatrix().UpdateRW();
				pLodLiftPart->UpdateRwFrame();
			}

			OldLift = lift;
		}
		//if (State == 4  && OldState == 3) {
		//} else if (State == 3 && OldState == 2) {
		//}
	}
}

void CBridgeHack::FindBridgeEntities(void)
{
	pWeight = pLiftPart = pLiftRoad = 0;
	pLodWeight = pLodLiftPart = 0;
	for (int i = 0; i < CPools::ms_pBuildingPool->totalCount; i++) {
		if ((CPools::ms_pBuildingPool->flags[i] & 0x80) != 0x80) {
			CEntity *entity = &CPools::ms_pBuildingPool->entities[i];
			unsigned short model = CPools::ms_pBuildingPool->entities[i].modelIndex;
			if (model == MI_BRIDGEWEIGHT) {
				pWeight = entity;
			}
			if (model == MI_BRIDGELIFT) {
				pLiftPart = entity;
			}
			if (model == MI_BRIDGEROADSEGMENT) {
				pLiftRoad = entity;
			}
			if (model == MI_LODDGEWEIGHT) {
				pLodWeight = entity;
			}
			if (model == MI_LODDGELIFT) {
				pLodLiftPart = entity;
			}
		}
	}
}

bool ShouldCarStopForBridge(CVehicle *vehicle)
{
	if (CBridgeHack::State != 3) {
		// eastbound
		if (vehicle->GetX() > -670.0 && vehicle->GetX() < -660.0) {
			if (vehicle->GetY() > -670.0 && vehicle->GetY() < -631.5) {
				return true;
			}
		}
		// westbound
		if (vehicle->GetX() > -565.0 && vehicle->GetX() < -555.0) {
			if (vehicle->GetY() > -631.5 && vehicle->GetY() < -593.0) {
				return true;
			}
		}
	}
	return false;
}
