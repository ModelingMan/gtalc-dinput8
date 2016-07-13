#include "CGaragesHack.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "Vehicles.h"

int carsToCollect[2][16] =
{
	{
		CAR_SECURICA,
		CAR_MOONBEAM,
		CAR_COACH,
		CAR_FLATBED,
		CAR_LINERUN,
		CAR_TRASH,
		CAR_PATRIOT,
		CAR_MRWHOOP,
		CAR_BLISTA,
		CAR_MULE,
		CAR_YANKEE,
		CAR_BOBCAT,
		CAR_DODO,
		CAR_BUS,
		CAR_RUMPO,
		CAR_PONY
	},
	{
		CAR_SENTINEL,
		CAR_CHEETAH,
		CAR_BANSHEE,
		CAR_IDAHO,
		CAR_INFERNUS,
		CAR_TAXI,
		CAR_KURUMA,
		CAR_STRETCH,
		CAR_PEREN,
		CAR_STINGER,
		CAR_MANANA,
		CAR_LANDSTAL,
		CAR_STALLION,
		CAR_BFINJECT,
		CAR_CABBIE,
		CAR_ESPERANT
	}
};

bool CGaragesHack::initialise()
{
	call(0x0045AD84, &HasImportExportGarageCollectedThisCar, PATCH_NOTHING);

	void(__thiscall CGarageHack::* function1)(int) = &CGarageHack::MarkThisCarAsCollectedForCraig;
	call(0x0043253C, (unsigned long &)function1, PATCH_NOTHING);

	bool(__thiscall CGarageHack::* function2)(int) = &CGarageHack::HasThisCarNotBeenCollected;
	call(0x00432242, (unsigned long &)function2, PATCH_NOTHING);
	call(0x004325F0, (unsigned long &)function2, PATCH_NOTHING);
	call(0x004328C9, (unsigned long &)function2, PATCH_NOTHING);

	bool(__thiscall CGarageHack::* function3)(int) = &CGarageHack::HasThisCarBeenCollected;
	call(0x004326DC, (unsigned long &)function3, PATCH_NOTHING);
	return true;
}

bool CGaragesHack::HasImportExportGarageCollectedThisCar(short index, int car)
{
	if (garages[index].type == 8) {
		return !!(CGaragesHack::carsCollected[0] & (1 << car));
	}
	if (garages[index].type == 9) {
		return !!(CGaragesHack::carsCollected[1] & (1 << car));
	}
	return false;
}

void CGarageHack::MarkThisCarAsCollectedForCraig(int model)
{
	if (type != 8 && type != 9) {
		return;
	}
	int list = type - 8;
	if (model == CAR_CORPSE) {
		model = CAR_MANANA;
	}
	if (model == CAR_VICECHEE) {
		model = CAR_CHEETAH;
	}
	for (int i = 0; i < 16; i++) {
		if (model == carsToCollect[list][i]) {
			CGaragesHack::carsCollected[list] |= (1 << i);
			if (CGaragesHack::carsCollected[list] == 0xFFFF) {
				CWorld::Players->m_Money += 200000;
				CGarages::TriggerMessage("GA_14", -1, 5000, -1);
			} else {
				CWorld::Players->m_Money += 1000;
				CGarages::TriggerMessage("GA_13", -1, 5000, -1);
			}
			break;
		}
	}
}

bool CGarageHack::HasThisCarBeenCollected(int model)
{
	if (type != 8 && type != 9) {
		return false;
	}
	int list = type - 8;
	if (model == CAR_CORPSE) {
		model = CAR_MANANA;
	}
	if (model == CAR_VICECHEE) {
		model = CAR_CHEETAH;
	}
	for (int i = 0; i < 16; i++) {
		if (model == carsToCollect[list][i]) {
			return !!(CGaragesHack::carsCollected[list] & (1 << i));
		}
	}
	return false;
}

bool CGarageHack::HasThisCarNotBeenCollected(int model)
{
	if (type != 8 && type != 9) {
		return false;
	}
	int list = type - 8;
	if (model == CAR_CORPSE) {
		model = CAR_MANANA;
	}
	if (model == CAR_VICECHEE) {
		model = CAR_CHEETAH;
	}
	for (int i = 0; i < 16; i++) {
		if (model == carsToCollect[list][i]) {
			return !(CGaragesHack::carsCollected[list] & (1 << i));
		}
	}
	return false;
}
