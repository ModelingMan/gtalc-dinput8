#include "CPlayerInfoHack.h"

static int destroyedVehiclesCounter;
static unsigned int timeSinceLastExplosion;

void CPlayerInfoHack::AwardMoneyForExplosion(CVehicle *vehicle)
{
	unsigned int monetaryValue = (unsigned int)(*(unsigned int *)(vehicle->handlingData + 0xD4) * 0.002f);
	if (CTimer::m_snTimeInMilliseconds - timeSinceLastExplosion >= 6000) {
		destroyedVehiclesCounter = 1;
	} else {
		destroyedVehiclesCounter++;
	}
	timeSinceLastExplosion = CTimer::m_snTimeInMilliseconds;
	do {
		this->m_Money += monetaryValue;
	} while (--destroyedVehiclesCounter > 0);
}
