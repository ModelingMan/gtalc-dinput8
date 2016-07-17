#include "CGaragesHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "Vehicles.h"

#include <math.h>

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

unsigned long updateEndJump = vcversion::AdjustOffset(0x00433E62);

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

	// add type 7 garage
	*(unsigned long *)(vcversion::AdjustOffset(0x00687B54)) = (unsigned long)&CGarageHack::UpdateProxy;

	// partial fix to type 14 garage
	*(unsigned char *)(vcversion::AdjustOffset(0x00432D52)) = 0xEB;

	return true;
}

bool CGaragesHack::HasImportExportGarageCollectedThisCar(short index, int slot)
{
	if (garages[index].type == 8) {
		return !!(CGaragesHack::carsCollected[0] & (1 << slot));
	}
	if (garages[index].type == 9) {
		return !!(CGaragesHack::carsCollected[1] & (1 << slot));
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
			return;
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

void __declspec(naked) CGarageHack::UpdateProxy(void)
{
	__asm
	{
		mov ecx, ebp
		call Update
		jmp updateEndJump
	}
}

void CGarageHack::Update(void)
{
	CVehicle *vehicle = VCGlobals::FindPlayerVehicle();
	auto UpdateDoor = (void(__thiscall *)(CGarage *))vcversion::AdjustOffset(0x0042F030);
	float multiplier = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00975424));
	float speed;

	// opened
	if (this->doorState == 1) {
		if (vehicle && vehicle->model == this->modelToCollect) {
			this->targetVehicle = vehicle;
			this->targetVehicle->RegisterReference((CEntity **)&this->targetVehicle);
		}
		if (this->targetVehicle &&
			IsEntityEntirelyInside3D(this->targetVehicle, 0.0) &&
			!IsAnyOtherCarTouchingGarage(this->targetVehicle) &&
			IsEntityEntirelyOutside(VCGlobals::FindPlayerPed(), 2.0)) {
			*(unsigned short *)(CPad::GetPad(0) + 0xF0) |= 4;
			VCGlobals::FindPlayerPed()->wanted->activity |= 1;
			this->doorState = 2; // closing
			return;
		}
		CVector pos;
		auto FindPlayerCoors = (CVector *(__cdecl *)(CVector *))vcversion::AdjustOffset(0x004BC240);
		CVector *ppos = FindPlayerCoors(&pos);
		if (abs(ppos->x - (this->lowerX + this->upperX) / 2) > 25.0 ||
			abs(ppos->y - (this->lowerY + this->upperY) / 2) > 25.0 ||
			ppos->z > this->ceilingHeight) {
			this->doorState = 2; // closing
			this->targetVehicle = 0;
		}
	}
	
	// closing
	else if (this->doorState == 2) {
		speed = this->rotatingDoor ? 0.02f : 0.04f;
		this->doorCurrentHeight -= speed * multiplier;
		if (this->doorCurrentHeight < 0.0) {
			this->doorCurrentHeight = 0.0;
			this->doorState = 0; // closed
			VCGlobals::DMAudio.PlayOneShot(cDMAudio::garageEntity, 0x4A, 1.0);
			if (this->targetVehicle) {
				auto DestroyVehicleAndDriverAndPassengers = (void(__cdecl *)(CVehicle *))vcversion::AdjustOffset(0x005B7E80);
				DestroyVehicleAndDriverAndPassengers(this->targetVehicle);
				this->targetVehicle = 0;
				*(unsigned short *)(CPad::GetPad(0) + 0xF0) &= 0xFFFB;
				VCGlobals::FindPlayerPed()->wanted->activity &= 0xFE;
				int reward = 2;
				if (this->modelToCollect == CAR_SECURICA) {
					reward = 5000 - (500 * CGarages::bankVansCollected);
					CGarages::bankVansCollected++;
				} else if (this->modelToCollect == CAR_POLICE) {
					reward = 5000 - (500 * CGarages::policeCarsCollected);
					CGarages::policeCarsCollected++;
				}
				if (!reward) {
					CGarages::TriggerMessage("GA_11", -1, 4000, -1);
				} else {
					CGarages::TriggerMessage("GA_10", reward, 4000, -1);
					CWorld::Players->m_Money += reward;
				}
			}
		}
		UpdateDoor(this);
	}
	
	// closed
	else if (this->doorState == 0) {
		if (vehicle && vehicle->model == this->modelToCollect) {
			auto ProximityToDoor = (float(__thiscall *)(CGarage *, float, float))vcversion::AdjustOffset(0x0042E800);
			if (ProximityToDoor(this, vehicle->x, vehicle->y) < 64.0) {
				this->doorState = 3; // opening
			}
		}
	}
	
	// opening
	else if (this->doorState == 3) {
		if (vehicle && vehicle->model == this->modelToCollect) {
			this->targetVehicle = vehicle;
			this->targetVehicle->RegisterReference((CEntity **)&this->targetVehicle);
		}
		speed = this->rotatingDoor ? 0.015f : 0.035f;
		this->doorCurrentHeight += speed * multiplier;
		if (this->doorCurrentHeight > this->doorMaximumHeight) {
			this->doorCurrentHeight = this->doorMaximumHeight;
			this->doorState = 1; // opened
			VCGlobals::DMAudio.PlayOneShot(cDMAudio::garageEntity, 0x4B, 1.0);
		}
		UpdateDoor(this);
	}
}
