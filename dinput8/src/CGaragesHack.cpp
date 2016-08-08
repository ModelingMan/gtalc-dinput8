#include "CGaragesHack.h"
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "Vehicles.h"

#include <math.h>

const int carsToCollect[2][16] =
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

unsigned long updateType7EndJump = vcversion::AdjustOffset(0x00433FF0);
unsigned long updateType7ProceedJump = vcversion::AdjustOffset(0x0043221E);
unsigned long updateType14EndJump = vcversion::AdjustOffset(0x00434010);
unsigned long updateType14ProceedJump = vcversion::AdjustOffset(0x00432C8E);

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

	// additional garage types
	call(0x00432217, &CGarageHack::UpdateType7HackProxy, PATCH_JUMP);
	call(0x00432C87, &CGarageHack::UpdateType14HackProxy, PATCH_JUMP);

	// bomb shop reward
	*reinterpret_cast<unsigned int *>(vcversion::AdjustOffset(0x004318BB)) = 1000;
	*reinterpret_cast<int *>(vcversion::AdjustOffset(0x00431BC4)) = -1000;

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

void __declspec(naked) CGarageHack::UpdateType7HackProxy(void)
{
	__asm
	{
		movzx ecx, byte ptr [ebp]
		cmp ecx, 7
		jnz proceed
		mov ecx, ebp
		call CGarageHack::UpdateType7Hack
		jmp updateType7EndJump
	proceed:
		movzx eax, byte ptr [ebp+1]
		cmp eax, 3
		jmp updateType7ProceedJump
	}
}

void CGarageHack::UpdateType7Hack(void)
{
	CVehicle *vehicle = VCGlobals::FindPlayerVehicle();
	float multiplier = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00975424));
	float speed;

	// opened
	if (this->state == 1) {
		if (vehicle && vehicle->modelIndex == this->targetModel) {
			this->targetVehicle = vehicle;
			this->targetVehicle->RegisterReference((CEntity **)&this->targetVehicle);
		}
		if (this->targetVehicle &&
			this->IsEntityEntirelyInside3D(this->targetVehicle, 0.0) &&
			!this->IsAnyOtherCarTouchingGarage(this->targetVehicle) &&
			this->IsEntityEntirelyOutside(VCGlobals::FindPlayerPed(), 2.0)) {
			*(unsigned short *)(CPad::GetPad(0) + 0xF0) |= 4;
			VCGlobals::FindPlayerPed()->wanted->activity |= 1;
			this->state = 2; // closing
			return;
		}
		CVector pos;
		CVector *ppos = VCGlobals::FindPlayerCoors(&pos);
		if (abs(ppos->x - (this->lowerX + this->upperX) / 2) > 25.0 ||
			abs(ppos->y - (this->lowerY + this->upperY) / 2) > 25.0 ||
			ppos->z > this->ceilingHeight) {
			this->state = 2; // closing
			this->targetVehicle = 0;
		}
	}
	
	// closing
	else if (this->state == 2) {
		speed = this->rotatingDoor ? 0.02f : 0.04f;
		this->doorCurrentHeight -= speed * multiplier;
		if (this->doorCurrentHeight < 0.0) {
			this->doorCurrentHeight = 0.0;
			this->state = 0; // closed
			VCGlobals::DMAudio.PlayOneShot(cDMAudio::garageEntity, 0x4A, 1.0);
			if (this->targetVehicle) {
				auto DestroyVehicleAndDriverAndPassengers = (void(__cdecl *)(CVehicle *))vcversion::AdjustOffset(0x005B7E80);
				DestroyVehicleAndDriverAndPassengers(this->targetVehicle);
				this->targetVehicle = 0;
				*(unsigned short *)(CPad::GetPad(0) + 0xF0) &= 0xFFFB;
				VCGlobals::FindPlayerPed()->wanted->activity &= 0xFE;
				int reward = 2;
				if (this->targetModel == CAR_SECURICA) {
					reward = 5000 - 500 * CGarages::bankVansCollected++;
				} else if (this->targetModel == CAR_POLICE) {
					reward = 5000 - 500 * CGarages::policeCarsCollected++;
				}
				if (!reward) {
					CGarages::TriggerMessage("GA_11", -1, 4000, -1);
				} else {
					CGarages::TriggerMessage("GA_10", (short)reward, 4000, -1);
					CWorld::Players->m_Money += reward;
				}
			}
		}
		this->UpdateDoor();
	}
	
	// closed
	else if (this->state == 0) {
		if (vehicle && vehicle->modelIndex == this->targetModel) {
			if (this->ProximityToGarageArea(vehicle->x, vehicle->y) < 64.0) {
				this->state = 3; // opening
			}
		}
	}
	
	// opening
	else if (this->state == 3) {
		if (vehicle && vehicle->modelIndex == this->targetModel) {
			this->targetVehicle = vehicle;
			this->targetVehicle->RegisterReference((CEntity **)&this->targetVehicle);
		}
		speed = this->rotatingDoor ? 0.015f : 0.035f;
		this->doorCurrentHeight += speed * multiplier;
		if (this->doorCurrentHeight > this->doorMaximumHeight) {
			this->doorCurrentHeight = this->doorMaximumHeight;
			this->state = 1; // opened
			VCGlobals::DMAudio.PlayOneShot(cDMAudio::garageEntity, 0x4B, 1.0);
		}
		this->UpdateDoor();
	}
}

void __declspec(naked) CGarageHack::UpdateType14HackProxy(void)
{
	__asm
	{
		movzx ecx, byte ptr [ebp]
		cmp ecx, 14
		jnz proceed
		mov ecx, ebp
		call CGarageHack::UpdateType14Hack
		jmp updateType14EndJump
	proceed:
		movzx ecx, byte ptr [ebp+1]
		cmp ecx, 5
		jmp updateType14ProceedJump
	}
}

void CGarageHack::UpdateType14Hack(void)
{
	CVehicle *vehicle = VCGlobals::FindPlayerVehicle();
	float multiplier = *reinterpret_cast<float *>(vcversion::AdjustOffset(0x00975424));
	float speed;

	// opened
	if (this->state == 1) {
		CVector pos;
		CVector *ppos = VCGlobals::FindPlayerCoors(&pos);
		if ((abs(ppos->x - (this->lowerX + this->upperX) / 2) > 30.0 ||
			abs(ppos->y - (this->lowerY + this->upperY) / 2) > 30.0) &&
			!this->IsAnyOtherCarTouchingGarage(0)) {
			this->state = 2; // closing
			this->closedUnserviced = 1;
			return;
		}
		if (this->targetVehicle &&
			this->targetVehicle == vehicle &&
			this->IsStaticPlayerCarEntirelyInside() &&
			!this->IsAnyCarBlockingDoor()) {
			*(unsigned short *)(CPad::GetPad(0) + 0xF0) |= 4;
			VCGlobals::FindPlayerPed()->wanted->activity |= 1;
			this->state = 2; // closing
			this->closedUnserviced = 0;
		}
	}

	// closing
	else if (this->state == 2) {
		speed = this->rotatingDoor ? 0.02f : 0.04f;
		this->doorCurrentHeight -= speed * multiplier;
		if (this->doorCurrentHeight < 0.0) {
			this->doorCurrentHeight = 0.0;
			this->state = 0; // closed
			VCGlobals::DMAudio.PlayOneShot(cDMAudio::garageEntity, 0x4A, 1.0);
			if (!this->closedUnserviced) {
				if (this->targetVehicle) {
					this->state = 5; // closed and serviced
					this->gameTimeToOpen = CTimer::m_snTimeInMilliseconds + 2000;
					this->targetVehicle = 0;
				} else {
					this->state = 0; // closed
				}
				*(unsigned short *)(CPad::GetPad(0) + 0xF0) &= 0xFFFB;
				VCGlobals::FindPlayerPed()->wanted->activity &= 0xFE;
			} else {
				this->state = 0; // closed
			}
		}
		this->UpdateDoor();
	}

	// closed
	else if (this->state == 0) {
		if (this->targetVehicle && vehicle == this->targetVehicle) {
			if (this->ProximityToGarageArea(vehicle->x, vehicle->y) < 289.0) {
				this->state = 3; // opening
			}
		}
	}

	// opening
	else if (this->state == 3) {
		speed = this->rotatingDoor ? 0.015f : 0.035f;
		this->doorCurrentHeight += speed * multiplier;
		if (this->doorCurrentHeight > this->doorMaximumHeight) {
			this->doorCurrentHeight = this->doorMaximumHeight;
			this->state = 1; // opened
			VCGlobals::DMAudio.PlayOneShot(cDMAudio::garageEntity, 0x4B, 1.0);
		}
		this->UpdateDoor();
	}

	// closed and serviced
	else if (this->state == 5) {
		if (this->type == 14 && CTimer::m_snTimeInMilliseconds > this->gameTimeToOpen) {
			this->state = 3; // opening
		}
	}
}

float CGarageHack::ProximityToGarageArea(float x, float y)
{
	if (x < this->lowerX) {
		x -= lowerX;
	} else if (x > this->upperX) {
		x -= upperX;
	} else {
		x = 0;
	}
	if (y < this->lowerY) {
		y -= lowerY;
	} else if (y > this->upperY) {
		y -= upperY;
	} else {
		y = 0;
	}
	return x * x + y * y;
}
