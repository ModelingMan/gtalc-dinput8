#include "CVehicleHack.h"
#include "vcversion.h"
#include "SilentCall.h"
#include "ModelIndices.h"

// PreRenderHack
static unsigned long preRenderMatchAmbulan = vcversion::AdjustOffset(0x0058BE77);
static unsigned long preRenderMatchFbiranch = vcversion::AdjustOffset(0x0058C8F0);
static unsigned long preRenderNoMatch = vcversion::AdjustOffset(0x0058BE34);

bool CVehicleHack::initialise()
{
	// FBI Rancher roof light
	InjectHook(0x0058BE2F, &CVehicleHack::AutomobilePreRenderHack, PATCH_JUMP); // CAutomobile::PreRender

	// open top car
	InjectHook(0x0059C7E0, &CVehicleHack::IsOpenTopCarHackProxy, PATCH_JUMP); // CAutomobile::IsOpenTopCar

	// taxi cash
	Patch<unsigned char>(0x005B8AB6, 25); // CVehicle::SetDriver

	return true;
}

void __declspec(naked) CVehicleHack::AutomobilePreRenderHack()
{
	__asm
	{
		sub ecx, 9 // ambulan
		jz matchAmbulan
		dec ecx    // fbiranch
		jz matchFbiranch
		inc ecx    // resume before change
		jmp preRenderNoMatch
	matchAmbulan:
		jmp preRenderMatchAmbulan
	matchFbiranch:
		jmp preRenderMatchFbiranch
	}
}

void __declspec(naked) CVehicleHack::IsOpenTopCarHackProxy()
{
	__asm
	{
		jmp CVehicleHack::IsOpenTopCarHack
	}
}

bool CVehicleHack::IsOpenTopCarHack()
{
	if (this->modelIndex == CAR_BANSHEE && this->componentA && this->componentB ||
		this->modelIndex == CAR_COMET && this->componentA && this->componentB ||
		this->modelIndex == CAR_STALLION && this->componentA && this->componentB ||
		this->modelIndex == CAR_STINGER && this->componentA && this->componentB) {
		return true;
	}
	return false;
}
