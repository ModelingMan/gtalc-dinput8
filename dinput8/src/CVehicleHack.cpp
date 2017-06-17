#include "CVehicleHack.h"
#include "vcversion.h"
#include "Globals.h"
#include "SilentCall.h"
#include "ModelIndices.h"
#include "CPlayerInfoHack.h"

// PreRenderHack
static unsigned long preRenderMatchAmbulan = vcversion::AdjustOffset(0x0058BE77);
static unsigned long preRenderMatchFbiranch = vcversion::AdjustOffset(0x0058C8F0);
static unsigned long preRenderNoMatch = vcversion::AdjustOffset(0x0058BE34);

// award money for explosion
static unsigned long awardExplosion1EndJump = vcversion::AdjustOffset(0x00598C6A);
static unsigned long awardExplosion2EndJump = vcversion::AdjustOffset(0x005B900A);

// award money for collision
static unsigned long awardCollision3EndJump = vcversion::AdjustOffset(0x0059C10C);
static unsigned long awardCollision1EndJump = vcversion::AdjustOffset(0x0059B576);

bool CVehicleHack::initialise()
{
	// FBI Rancher roof light
	InjectHook(0x0058BE2F, &CVehicleHack::AutomobilePreRenderHack, PATCH_JUMP); // CAutomobile::PreRender

	// open top car
	InjectHook(0x0059C7E0, &CVehicleHack::IsOpenTopCarHackProxy, PATCH_JUMP); // CAutomobile::IsOpenTopCar

	// taxi cash
	Patch<unsigned char>(0x005B8AB6, 25); // CVehicle::SetDriver

	// hydraulics
	Patch<unsigned int>(0x0058F53E, CAR_YARDIE);
	Patch<unsigned int>(0x0058FB0D, CAR_YARDIE);
	Patch<unsigned int>(0x0058FDD0, CAR_YARDIE);
	Patch<unsigned int>(0x005900A4, CAR_YARDIE);
	Patch<unsigned int>(0x00590D6D, CAR_YARDIE);
	Patch<unsigned int>(0x0059137D, CAR_YARDIE);
	Patch<unsigned int>(0x00594611, CAR_YARDIE);
	Patch<unsigned short>(0x00597985, CAR_YARDIE);
	Patch<unsigned short>(0x00597B5B, CAR_YARDIE);

	// monetary award for explosion based on Silent's code
	InjectHook(0x00598C62, &CVehicleHack::MoneyForExplosion_Inject1, PATCH_JUMP);
	InjectHook(0x005B9002, &CVehicleHack::MoneyForExplosion_Inject2, PATCH_JUMP);

	// monetary award for collision based on Silent's code
	InjectHook(0x0059B571, &CVehicleHack::MoneyForCollision_Inject1, PATCH_JUMP);
	InjectHook(0x0059BF18, vcversion::AdjustOffset(0x0059C0FF), PATCH_JUMP); // jump to set boolean flag
	Patch<unsigned char>(0x0059C0B1, 0x4D);                                  // jump to set boolean flag
	Patch<unsigned int>(0x0059C0FF, 0x182444C6);                             // mov byte ptr [esp+48h-30h], 1
	Patch<unsigned char>(0x0059C103, 1);
	InjectHook(0x0059C0EA, &CVehicleHack::MoneyForCollision_Inject2, PATCH_JUMP);
	InjectHook(0x0059C104, &CVehicleHack::MoneyForCollision_Inject3, PATCH_JUMP);

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
	return this->modelIndex == CAR_BANSHEE && this->componentA && this->componentB ||
		this->modelIndex == CAR_COMET && this->componentA && this->componentB ||
		this->modelIndex == CAR_STALLION && this->componentA && this->componentB ||
		this->modelIndex == CAR_STINGER && this->componentA && this->componentB;
}

void __declspec(naked) CVehicleHack::MoneyForExplosion_Inject1()
{
	__asm
	{
		mov ecx, CWorld::PlayerInFocus
		movzx ecx, byte ptr [ecx]
		push ebp
		imul ecx, 170h
		add ecx, CWorld::Players
		call CPlayerInfoHack::AwardMoneyForExplosion
		mov ecx, ebp
		mov eax, [ebp+5A4h]
		jmp awardExplosion1EndJump
	}
}

void __declspec(naked) CVehicleHack::MoneyForExplosion_Inject2()
{
	__asm
	{
		call VCGlobals::FindPlayerVehicle // get player vehicle
		cmp ebp, eax                      // test for player vehicle
		jz noAward
		call VCGlobals::FindPlayerPed     // get player ped
		cmp [ebp+224h], eax               // test for player ownership of explosion
		jnz noAward
		mov ecx, CWorld::PlayerInFocus
		movzx ecx, byte ptr [ecx]
		push ebp
		imul ecx, 170h
		add ecx, CWorld::Players
		call CPlayerInfoHack::AwardMoneyForExplosion
	noAward:
		mov ecx, ebp
		mov eax, [ebp+224h]
		jmp awardExplosion2EndJump
	}
}

void __declspec(naked) CVehicleHack::MoneyForCollision_Inject1()
{
	__asm
	{
		mov byte ptr [esp+48h-30h], 0 // init boolean flag
		mov ebx, ecx
		and ah, 44h
		jmp awardCollision1EndJump
	}
}

void __declspec(naked) CVehicleHack::MoneyForCollision_Inject2()
{
	__asm
	{
		mov [esp+48h-34h], eax
		mov ecx, ebx
		push 0
		push 4
		push 13h
		call CAutomobile::SetPanelDamage
		lea ecx, [ebx+2A0h]
		push 4
		call CDamageManager::GetPanelStatus
		cmp eax, [esp+48h-34h]
		jz dontSetFlag
		mov byte ptr [esp+48h-30h], 1 // set boolean flag
	dontSetFlag:
		jmp CVehicleHack::MoneyForCollision_Inject3
	}
}

void __declspec(naked) CVehicleHack::MoneyForCollision_Inject3()
{
	__asm
	{
		fld [esp+48h+4]
		movzx eax, byte ptr [esp+48h-30h] // get boolean flag
		push eax                          // flag
		push eax                          // damage value
		fstp [esp]
		mov ecx, ebx                      // vehicle pointer
		call CVehicleHack::AwardMoneyForCollision
		fld [esp+48h+4]
		fsub [esp+48h-3Ch]
		jmp awardCollision3EndJump
	}
}

void CVehicleHack::AwardMoneyForCollision(float fDamageValue, bool flag)
{
	if (this->collidingEntity && this->collidingEntity == VCGlobals::FindPlayerVehicle() && fDamageValue > 10.0) {
		unsigned int monetaryValue;
		if (flag) {
			monetaryValue = (unsigned int)(*(unsigned int *)(this->handlingData + 0xD4) * fDamageValue * 0.000002f);
		} else {
			monetaryValue = (unsigned int)(*(unsigned int *)(this->handlingData + 0xD4) * fDamageValue * 0.000001f);
		}
		if (monetaryValue > 40) {
			monetaryValue = 40;
		}
		if (monetaryValue > 2) {
			CWorld::Players[CWorld::PlayerInFocus].m_Money += monetaryValue;
		}
	}
}
