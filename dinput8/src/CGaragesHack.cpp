#include "CGaragesHack.h"
#include <cmath>
#include "Globals.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "ModelIndices.h"

#define SPRAY_SHOP_COST 1000
#define BOMB_SHOP_COST 1000

static const int carsToCollect[2][16] =
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

// UpdateType7HackProxy
static unsigned long updateType7EndJump = vcversion::AdjustOffset(0x00433FF0);
static unsigned long updateType7ProceedJump = vcversion::AdjustOffset(0x0043221E);
// UpdateType14HackProxy
static unsigned long updateType14EndJump = vcversion::AdjustOffset(0x00434010);
static unsigned long updateType14ProceedJump = vcversion::AdjustOffset(0x00432C8E);
// UpdateType5HackProxy
static unsigned long updateType5EndJump = vcversion::AdjustOffset(0x00430CF9);

// spray shop cost
static float sprayShopCost = SPRAY_SHOP_COST;
static unsigned int *playerMoney;
static unsigned long sprayShopCostEndJump = vcversion::AdjustOffset(0x00430D13);
static unsigned long sprayShopCost2EndJump = vcversion::AdjustOffset(0x0043159E);

bool CGaragesHack::initialise()
{
	InjectHook(0x0045AD84, &HasImportExportGarageCollectedThisCar);

	auto function1 = &CGarageHack::MarkThisCarAsCollectedForCraig;
	InjectHook(0x0043253C, (unsigned long &)function1);

	auto function2 = &CGarageHack::DoesCraigNeedThisCar;
	InjectHook(0x00432242, (unsigned long &)function2);
	InjectHook(0x004325F0, (unsigned long &)function2);
	InjectHook(0x004328C9, (unsigned long &)function2);

	auto function3 = &CGarageHack::HasCraigCollectedThisCar;
	InjectHook(0x004326DC, (unsigned long &)function3);

	// additional garage types
	InjectHook(0x00432217, &CGarageHack::UpdateType7HackProxy, PATCH_JUMP);
	InjectHook(0x00432C87, &CGarageHack::UpdateType14HackProxy, PATCH_JUMP);

	// bomb shop cost
	Patch<int>(0x004318BB, BOMB_SHOP_COST);
	Patch<int>(0x00431BC4, -BOMB_SHOP_COST);

	// respray reinit fix (SilentPatch)
	InjectHook(0x004349BB, &CGaragesHack::InitHack, PATCH_JUMP);

	// spray shop acceptable vehicles
	InjectHook(0x00430CC6, &CGarageHack::UpdateType5HackProxy, PATCH_JUMP);

	// spray shop cost (Silent)
	InjectHook(0x00430D0B, &CGarageHack::SprayShopCostHack, PATCH_JUMP);
	InjectHook(0x00431599, &CGarageHack::SprayShopCostHack2, PATCH_JUMP);
	Patch<void *>(0x004315AA, &sprayShopCost);
	playerMoney = &CWorld::Players->m_Money;
	return true;
}

bool CGaragesHack::HasImportExportGarageCollectedThisCar(short index, int slot)
{
	if (aGarages[index].type == 8) {
		return !!(CGaragesHack::CarTypesCollected[0] & (1 << slot));
	}
	if (aGarages[index].type == 9) {
		return !!(CGaragesHack::CarTypesCollected[1] & (1 << slot));
	}
	return false;
}

void CGaragesHack::InitHack()
{
	RespraysAreFree = 0;
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
			CGaragesHack::CarTypesCollected[list] |= (1 << i);
			if (CGaragesHack::CarTypesCollected[list] == 0xFFFF) {
				CWorld::Players[CWorld::PlayerInFocus].m_Money += 200000;
				CGarages::TriggerMessage("GA_14", -1, 5000, -1);
			} else {
				CWorld::Players[CWorld::PlayerInFocus].m_Money += 1000;
				CGarages::TriggerMessage("GA_13", -1, 5000, -1);
			}
			return;
		}
	}
}

bool CGarageHack::HasCraigCollectedThisCar(int model)
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
			return !!(CGaragesHack::CarTypesCollected[list] & (1 << i));
		}
	}
	return false;
}

bool CGarageHack::DoesCraigNeedThisCar(int model)
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
			return !(CGaragesHack::CarTypesCollected[list] & (1 << i));
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
		VCGlobals::FindPlayerCoors(&pos);
		if (abs(pos.x - (this->lowerX + this->upperX) / 2) > 25.0 ||
			abs(pos.y - (this->lowerY + this->upperY) / 2) > 25.0 ||
			pos.z > this->ceilingHeight) {
			this->state = 2; // closing
			this->targetVehicle = 0;
		}
	}

	// closing
	else if (this->state == 2) {
		speed = this->rotatingDoor ? 0.02f : 0.04f;
		this->doorCurrentHeight -= speed * CTimer::ms_fTimeStep;
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
					reward = 5000 - 500 * CGarages::BankVansCollected++;
				} else if (this->targetModel == CAR_POLICE) {
					reward = 5000 - 500 * CGarages::PoliceCarsCollected++;
				}
				if (!reward) {
					CGarages::TriggerMessage("GA_11", -1, 4000, -1);
				} else {
					CGarages::TriggerMessage("GA_10", static_cast<short>(reward), 4000, -1);
					CWorld::Players[CWorld::PlayerInFocus].m_Money += reward;
				}
			}
		}
		this->UpdateDoorsHeight();
	}

	// closed
	else if (this->state == 0) {
		if (vehicle && vehicle->modelIndex == this->targetModel) {
			if (this->CalcDistToGarageRectangleSquared(vehicle->GetX(), vehicle->GetY()) < 64.0) {
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
		this->doorCurrentHeight += speed * CTimer::ms_fTimeStep;
		if (this->doorCurrentHeight > this->doorMaximumHeight) {
			this->doorCurrentHeight = this->doorMaximumHeight;
			this->state = 1; // opened
			VCGlobals::DMAudio.PlayOneShot(cDMAudio::garageEntity, 0x4B, 1.0);
		}
		this->UpdateDoorsHeight();
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
	float speed;

	// opened
	if (this->state == 1) {
		CVector pos;
		VCGlobals::FindPlayerCoors(&pos);
		if ((abs(pos.x - (this->lowerX + this->upperX) / 2) > 30.0 ||
			abs(pos.y - (this->lowerY + this->upperY) / 2) > 30.0) &&
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
		this->doorCurrentHeight -= speed * CTimer::ms_fTimeStep;
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
		this->UpdateDoorsHeight();
	}

	// closed
	else if (this->state == 0) {
		if (this->targetVehicle && vehicle == this->targetVehicle) {
			if (this->CalcDistToGarageRectangleSquared(vehicle->GetX(), vehicle->GetY()) < 289.0) {
				this->state = 3; // opening
			}
		}
	}

	// opening
	else if (this->state == 3) {
		speed = this->rotatingDoor ? 0.015f : 0.035f;
		this->doorCurrentHeight += speed * CTimer::ms_fTimeStep;
		if (this->doorCurrentHeight > this->doorMaximumHeight) {
			this->doorCurrentHeight = this->doorMaximumHeight;
			this->state = 1; // opened
			VCGlobals::DMAudio.PlayOneShot(cDMAudio::garageEntity, 0x4B, 1.0);
		}
		this->UpdateDoorsHeight();
	}

	// closed and serviced
	else if (this->state == 5) {
		if (this->type == 14 && CTimer::m_snTimeInMilliseconds > this->gameTimeToOpen) {
			this->state = 3; // opening
		}
	}
}

float CGarageHack::CalcDistToGarageRectangleSquared(float x, float y)
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

void __declspec(naked) CGarageHack::UpdateType5HackProxy(void)
{
	__asm
	{
		push eax
		call CGarageHack::UpdateType5Hack
		add esp, 4
		jmp updateType5EndJump
	}
}

bool CGarageHack::UpdateType5Hack(int model)
{
	switch (model) {
	case CAR_AMBULAN:
	case CAR_BARRACKS:
	case CAR_BUS:
	case CAR_DODO:
	case CAR_ENFORCER:
	case CAR_FIRETRUK:
	case CAR_POLICE:
	case CAR_RHINO:
		return false;
	}
	return true;
}

void __declspec(naked) CGarageHack::SprayShopCostHack()
{
	__asm
	{
		mov ecx, playerMoney
		cmp dword ptr [eax*8+ecx], SPRAY_SHOP_COST
		jmp sprayShopCostEndJump
	}
}

void __declspec(naked) CGarageHack::SprayShopCostHack2()
{
	__asm
	{
		sub eax, SPRAY_SHOP_COST
		test eax, eax
		jmp sprayShopCost2EndJump
	}
}
