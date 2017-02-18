#include "CCarCtrlHack.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "Offset.h"

bool CCarCtrlHack::initialise()
{
	// reinit firetruck/ambulance timer (SilentPatch)
	InjectHook(0x004A489B, &CCarCtrlHack::ReInitHack);

	// CCarCtrl::MapCouldMoveInThisArea
	Patch<float>(0x00687028, -342.2 + OFFSETX);
	Patch<float>(0x0068702C, -219.2 + OFFSETX);

	return true;
}

void CCarCtrlHack::ReInitHack()
{
	ReInit();
	LastTimeFireTruckCreated = 0;
	LastTimeAmbulanceCreated = 0;
}
