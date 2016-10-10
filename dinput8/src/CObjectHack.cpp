#include "CObjectHack.h"
#include "vcversion.h"
#include "SilentCall.h"

#define MI_BODYCAST 1395

short CObjectHack::nBodyCastHealth;

bool CObjectHack::initialise()
{
	auto function = &CObjectHack::ObjectDamageHack;
	InjectHook(0x004B24F6, (unsigned long &)function);
	InjectHook(0x004B3502, (unsigned long &)function);
	InjectHook(0x004B3637, (unsigned long &)function);
	InjectHook(0x004B3691, (unsigned long &)function);
	InjectHook(0x004B37CE, (unsigned long &)function);
	InjectHook(0x004B6D44, (unsigned long &)function);
	InjectHook(0x004D7E5A, (unsigned long &)function);
	InjectHook(0x004D8284, (unsigned long &)function);
	InjectHook(0x004E36A8, (unsigned long &)function);
	InjectHook(0x005C4552, (unsigned long &)function);
	InjectHook(0x005CFFD1, (unsigned long &)function);
	InjectHook(0x005D442F, (unsigned long &)function);

	InjectHook(0x004E4026, &CObjectHack::InitHackProxy, PATCH_JUMP);
	return true;
}

void __declspec(naked) CObjectHack::InitHackProxy()
{
	__asm
	{
		mov ecx, ebx
		call CObjectHack::InitHack
		pop ebx
		retn
	}
}

void CObjectHack::InitHack()
{
	if (this->modelIndex == MI_BODYCAST) {
		nBodyCastHealth = 1000;
	}
}

void CObjectHack::ObjectDamageHack(float damage)
{
	if (this->modelIndex == MI_BODYCAST) {
		if (damage > 50.0) {
			nBodyCastHealth = static_cast<unsigned short>(static_cast<float>(nBodyCastHealth) - damage / 2.0);
		}
		if (nBodyCastHealth < 0) {
			nBodyCastHealth = 0;
		}
		if (nBodyCastHealth > 200) {
			return;
		}
	}
	this->ObjectDamage(damage);
}
