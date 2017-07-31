#include "CWeaponHack.h"
#include "SilentCall.h"
#include "WeaponTypes.h"

bool CWeaponHack::initialise()
{
	auto function = &CWeaponHack::IsType2Handed;
	InjectHook(0x0050B86C, (unsigned long &)function);
	InjectHook(0x0052C69C, (unsigned long &)function);
	InjectHook(0x00533F52, (unsigned long &)function);
	return true;
}

bool CWeaponHack::IsType2Handed()
{
	return this->type == WEAPONTYPE_SHOTGUN ||
		this->type == WEAPONTYPE_SPAS12_SHOTGUN ||
		this->type == WEAPONTYPE_STUBBY_SHOTGUN ||
		this->type == WEAPONTYPE_M16 ||
		this->type == WEAPONTYPE_CHAINGUN ||
		this->type == WEAPONTYPE_SNIPERRIFLE ||
		this->type == WEAPONTYPE_LASERSCOPE ||
		this->type == WEAPONTYPE_FLAMETHROWER ||
		this->type == WEAPONTYPE_M60 ||
		this->type == WEAPONTYPE_HELICANNON;
}
