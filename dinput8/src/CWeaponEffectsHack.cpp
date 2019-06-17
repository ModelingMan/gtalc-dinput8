#include "CWeaponEffectsHack.h"
#include "Globals.h"
#include "SilentCall.h"
#include "vcversion.h"

static unsigned long initJumpEnd = vcversion::AdjustOffset(0x005D512D);

bool CWeaponEffectsHack::initialise()
{
	// auto-aim crosshair
	InjectHook(0x005D511C, &CWeaponEffectsHack::InitHackProxy, PATCH_JUMP);

	// transparent crosshair
	Patch<unsigned char>(0x005D4EEE, 9); // use 6 for no outline

	// sniper dot (aap's skygfx_vc)
	Patch<unsigned char>(0x00558024, 6);
	return true;
}

void __declspec(naked) CWeaponEffectsHack::InitHackProxy()
{
	__asm
	{
		call CWeaponEffectsHack::InitHack
		jmp initJumpEnd
	}
}

RwTexture *CWeaponEffectsHack::InitHack()
{
	RwTexture *addr = RwTextureRead("crosshair", "crosshairm");
	// use alternative target texture if it exists
	if (!GetPrivateProfileInt("Misc", "UseVCAutoAimTexture", 1, "./gta-lc.ini") && addr) {
		VCGlobals::strcpy(reinterpret_cast<char *>(vcversion::AdjustOffset(0x0069D818)), "crosshair");
		VCGlobals::strcpy(reinterpret_cast<char *>(vcversion::AdjustOffset(0x0069D80C)), "crosshairm");
		DWORD flOldProtect;
		void *address = reinterpret_cast<void *>(vcversion::AdjustOffset(0x005D4ECC));
		VirtualProtect(address, 0x23, PAGE_EXECUTE_READWRITE, &flOldProtect);
		Nop(0x005D4ECC, 11);
		Patch<unsigned char>(0x005D4EE3, 2);
		Patch<unsigned char>(0x005D4EEE, 2);
		VirtualProtect(address, 0x23, flOldProtect, &flOldProtect);
	} else {
		addr = RwTextureRead("target256", "target256m");
	}
	return addr;
}
